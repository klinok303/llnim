<table border="0">
<tr>
<td>
 
# LLNIM

LLNIM (Low-Level aNIMation engine) is a animation engine-framework based on [raylib](http://www.raylib.com/) that uses [dynamic load](https://en.wikipedia.org/wiki/Dynamic_loading).

</td>
</tr>
</table>

# Installation

| API     | Windows            | Linux              |
| ------- | ------------------ | ------------------ |
| C/C++   | :heavy_check_mark: | :heavy_check_mark: |
| Rust    | :heavy_check_mark: | :heavy_check_mark: |
| Fortran | :x:                | :x:                |

## Build Form Sources

Requires raylib, ffmpeg (for llnim rendering) and cmake.

Compile llnim form sources:
```shell
cmake .. "your-build-system"
```

# Future Goals

- Port api to Fortran.
- More examples.
- Bake sounds.
- More build-in easings.
- Async support.
- Build-In matrix type.
- Optimize with opencl.
