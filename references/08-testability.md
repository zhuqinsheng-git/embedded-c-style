## 8. Testability

> **Summary**: Pure functions are testable; functions that touch hardware are not. Keep them apart.

### 8.1 Separate Logic from I/O

The rule: **a function that calls `read()` can't be tested without hardware. A function that only does math can.**

```c
/* untestable — reads sensor, parses data, all in one */
int read_temperature(sensor_t *s)
{
    uint8_t raw[2];
    i2c_read(s->bus, s->addr, raw, 2);       /* needs real sensor */
    return raw[0] << 8 | raw[1];             /* this is what you want to test */
}
```

Pull the pure part out:

```c
/* testable — takes bytes, returns value, no hardware */
int16_t sensor_raw_to_temp(uint8_t hi, uint8_t lo)
{
    return (int16_t)(hi << 8 | lo);
}
```

Now the tricky conversion logic can be tested with one line:

```c
assert(sensor_raw_to_temp(0x0A, 0xCD) == 0x0ACD);
assert(sensor_raw_to_temp(0x80, 0x00) == -32768);
```

No I2C bus, no sensor.

### 8.2 Inject Dependencies

Don't let functions fetch their own resources — hand them in.

```c
/* bad — path hardcoded, can only test with that exact file on disk */
int load_config(void)
{
    FILE *fp = fopen("/etc/app/config.json", "r");
}

/* good — caller provides the path, test can point to a temp file */
int load_config(const char *path)
{
    FILE *fp = fopen(path, "r");
}
```

### 8.3 Test File Convention

```
module.c        ← implementation
module_test.c   ← tests
```

Name tests after the function they test — `test_sensor_raw_to_temp`, `test_crc16`.

### 8.4 Testing Priority

| Priority | What | Why |
|----------|------|-----|
| **Must** | Protocol parsing, CRC, frame packing | Wrong here = corrupt data on the wire |
| **Must** | Error paths (NULL, short buffer, bad checksum) | These are never hit in normal use |
| **Should** | State machines, timeout logic | Hard to trigger manually |
| **Optional** | Full integration (real device) | Needs hardware, do sparingly |

Start with parsers and checksums. They're pure functions, zero dependencies, and if they're wrong nothing else matters.
