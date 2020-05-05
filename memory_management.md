```
execve("./a.out", ["./a.out"], 0x7ffeb9a09140 /* 62 vars */) = 0
brk(NULL)                               = 0x55ec2f5d0000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=108245, ...}) = 0
mmap(NULL, 108245, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fd6abbc5000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\200\221\t\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=1952584, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd6abbc3000
mmap(NULL, 4060608, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fd6ab5d9000
mprotect(0x7fd6ab7a9000, 2093056, PROT_NONE) = 0
mmap(0x7fd6ab9a8000, 57344, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1cf000) = 0x7fd6ab9a8000
mmap(0x7fd6ab9b6000, 9664, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fd6ab9b6000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fd6ab1e8000
mprotect(0x7fd6ab3cf000, 2097152, PROT_NONE) = 0
mmap(0x7fd6ab5cf000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fd6ab5cf000
mmap(0x7fd6ab5d5000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fd6ab5d5000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\200\272\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=1700792, ...}) = 0
mmap(NULL, 3789144, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fd6aae4a000
mprotect(0x7fd6aafe7000, 2093056, PROT_NONE) = 0
mmap(0x7fd6ab1e6000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19c000) = 0x7fd6ab1e6000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000+\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=96640, ...}) = 0
mmap(NULL, 2192464, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fd6aac32000
mprotect(0x7fd6aac48000, 2097152, PROT_NONE) = 0
mmap(0x7fd6aae48000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x16000) = 0x7fd6aae48000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd6abbc1000
arch_prctl(ARCH_SET_FS, 0x7fd6abbc1f00) = 0
mprotect(0x7fd6ab5cf000, 16384, PROT_READ) = 0
mprotect(0x7fd6aae48000, 4096, PROT_READ) = 0
mprotect(0x7fd6ab1e6000, 4096, PROT_READ) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fd6abbbf000
mprotect(0x7fd6ab9a8000, 45056, PROT_READ) = 0
mprotect(0x55ec2ea27000, 4096, PROT_READ) = 0
mprotect(0x7fd6abbe0000, 4096, PROT_READ) = 0
munmap(0x7fd6abbc5000, 108245)          = 0
brk(NULL)                               = 0x55ec2f5d0000
brk(0x55ec2f5f1000)                     = 0x55ec2f5f1000
getpid()                                = 107036
fstat(1, {st_mode=S_IFCHR|0600, st_rdev=makedev(136, 2), ...}) = 0
write(1, "107036\n", 7107036
)                 = 7
write(1, "stack: 7ffed25910bc\n", 20stack: 7ffed25910bc
)   = 20
write(1, "heap : 55ec2f5e1e70\n", 20heap : 55ec2f5e1e70
)   = 20
write(1, "Gi   : 55ec2ea28138\n", 20Gi   : 55ec2ea28138
)   = 20
write(1, "Gni  : 55ec2ea28134\n", 20Gni  : 55ec2ea28134
)   = 20
write(1, "stati: 55ec2ea2813c\n", 20stati: 55ec2ea2813c
)   = 20
write(1, "const: 7ffed25910b8\n", 20const: 7ffed25910b8
)   = 20
write(1, "Gc   : 55ec2e826e2c\n", 20Gc   : 55ec2e826e2c
)   = 20
nanosleep({tv_sec=50, tv_nsec=0}, 0x7ffed25910c0) = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

```
55ec2e826000-55ec2e827000 r-xp 00000000 08:01 399384                     /home/mx/Documents/playground/cpp/a.out
55ec2ea27000-55ec2ea28000 r--p 00001000 08:01 399384                     /home/mx/Documents/playground/cpp/a.out
55ec2ea28000-55ec2ea29000 rw-p 00002000 08:01 399384                     /home/mx/Documents/playground/cpp/a.out
55ec2f5d0000-55ec2f5f1000 rw-p 00000000 00:00 0                          [heap]
7fd6aac32000-7fd6aac48000 r-xp 00000000 08:01 405798                     /lib/x86_64-linux-gnu/libgcc_s.so.1
7fd6aac48000-7fd6aae48000 ---p 00016000 08:01 405798                     /lib/x86_64-linux-gnu/libgcc_s.so.1
7fd6aae48000-7fd6aae49000 r--p 00016000 08:01 405798                     /lib/x86_64-linux-gnu/libgcc_s.so.1
7fd6aae49000-7fd6aae4a000 rw-p 00017000 08:01 405798                     /lib/x86_64-linux-gnu/libgcc_s.so.1
7fd6aae4a000-7fd6aafe7000 r-xp 00000000 08:01 399572                     /lib/x86_64-linux-gnu/libm-2.27.so
7fd6aafe7000-7fd6ab1e6000 ---p 0019d000 08:01 399572                     /lib/x86_64-linux-gnu/libm-2.27.so
7fd6ab1e6000-7fd6ab1e7000 r--p 0019c000 08:01 399572                     /lib/x86_64-linux-gnu/libm-2.27.so
7fd6ab1e7000-7fd6ab1e8000 rw-p 0019d000 08:01 399572                     /lib/x86_64-linux-gnu/libm-2.27.so
7fd6ab1e8000-7fd6ab3cf000 r-xp 00000000 08:01 399509                     /lib/x86_64-linux-gnu/libc-2.27.so
7fd6ab3cf000-7fd6ab5cf000 ---p 001e7000 08:01 399509                     /lib/x86_64-linux-gnu/libc-2.27.so
7fd6ab5cf000-7fd6ab5d3000 r--p 001e7000 08:01 399509                     /lib/x86_64-linux-gnu/libc-2.27.so
7fd6ab5d3000-7fd6ab5d5000 rw-p 001eb000 08:01 399509                     /lib/x86_64-linux-gnu/libc-2.27.so
7fd6ab5d5000-7fd6ab5d9000 rw-p 00000000 00:00 0 
7fd6ab5d9000-7fd6ab7a9000 r-xp 00000000 08:01 809717                     /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fd6ab7a9000-7fd6ab9a8000 ---p 001d0000 08:01 809717                     /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fd6ab9a8000-7fd6ab9b3000 r--p 001cf000 08:01 809717                     /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fd6ab9b3000-7fd6ab9b6000 rw-p 001da000 08:01 809717                     /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28
7fd6ab9b6000-7fd6ab9b9000 rw-p 00000000 00:00 0 
7fd6ab9b9000-7fd6ab9e0000 r-xp 00000000 08:01 399483                     /lib/x86_64-linux-gnu/ld-2.27.so
7fd6abbbf000-7fd6abbc5000 rw-p 00000000 00:00 0 
7fd6abbe0000-7fd6abbe1000 r--p 00027000 08:01 399483                     /lib/x86_64-linux-gnu/ld-2.27.so
7fd6abbe1000-7fd6abbe2000 rw-p 00028000 08:01 399483                     /lib/x86_64-linux-gnu/ld-2.27.so
7fd6abbe2000-7fd6abbe3000 rw-p 00000000 00:00 0 
7ffed2572000-7ffed2593000 rw-p 00000000 00:00 0                          [stack]
7ffed25d1000-7ffed25d4000 r--p 00000000 00:00 0                          [vvar]
7ffed25d4000-7ffed25d5000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```
