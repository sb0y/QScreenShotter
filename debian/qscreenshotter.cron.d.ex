#
# Regular cron jobs for the qscreenshotter package
#
0 4	* * *	root	[ -x /usr/bin/qscreenshotter_maintenance ] && /usr/bin/qscreenshotter_maintenance
