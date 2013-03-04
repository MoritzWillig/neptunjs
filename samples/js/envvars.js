ob.writeln("Mapped environment variables");
for (var e in system.env) {
	ob.writeln(e+"="+system.env[e]);
}
