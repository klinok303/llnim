import subprocess

def ffmpeg_start_rendering(width: int, height: int, fps: int) -> subprocess.Popen:
    cmd = [
        "ffmpeg",
        "-loglevel", "verbose",
        "-y",

        "-f", "rawvideo",
        "-pix_fmt", "rgba",
        "-s", f"{width}x{height}",
        "-r", str(fps),
        "-i", "-",

        "-c:v", "libx264",
        "-vb", "2500k",
        "-c:a", "aac",
        "-ab", "200k",
        "-pix_fmt", "yuv420p",
        "output.mp4"
    ]

    ffmpeg_process = subprocess.Popen(
        cmd, stdin=subprocess.PIPE
    )

    return ffmpeg_process

def ffmpeg_end_rendering(ffmpeg_process: subprocess.Popen):
    ffmpeg_process.stdin.close()
    ffmpeg_process.wait()

def ffmpeg_send_frame_flipped(ffmpeg_process: subprocess.Popen, data: bytes, width: int,
                              height: int):
    try:
        for y in range(height-1, -1, -1):
            ffmpeg_process.stdin.write(data[y * width:(y + 1) * width])
    except OSError as e:
        print(f'FFMPEG: Failed write to stdin: {e}')
        ffmpeg_process.kill()