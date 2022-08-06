const std = @import("std");

pub fn build(b: *std.build.Builder) void {
    const flags = [_][]const u8{
        "-std=c18",
        "-pedantic",
        "-Wall",
        "-Wextra",
        "-Wshadow",
        "-Wstrict-overflow",
        "-fno-strict-aliasing",
    };

    const exe = b.addExecutable("nbwmon-ng", null);

    const target = b.standardTargetOptions(.{});
    exe.setTarget(target);

    const mode = b.standardReleaseOptions();
    exe.setBuildMode(mode);

    exe.addCSourceFile("src/main.c", &flags);
    // exe.addCSourceFile("src/util.c", &flags);

    exe.linkLibC();
    // exe.linkSystemLibrary("libnl3");
    // exe.linkSystemLibrary("ncurses");
    exe.addIncludeDir("/usr/include/libnl3");
    exe.addLibPath("/usr/lib");
    exe.linkSystemLibraryName("nl-3");
    exe.linkSystemLibraryName("nl-route-3");

    exe.install();
}
