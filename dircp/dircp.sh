#!/bin/sh

# Copyright (C) 2013, Grant Mather <hcaulfield57@gmail.com>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies. 
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

export SRC
export DST

if [ $# -lt 2 ]; then
	echo "usage: ${0} [-pv] source destination"
	exit 1
elif [ $# -eq 2 ]; then	# no arguments
	SRC=${1}
	DST=${2}
elif [ $# -eq 3 ]; then
	ARGS=${1}
	SRC=${2}
	DST=${3}
fi

if ! [ -z ${ARGS} ]; then
	case ${ARGS} in
		-*p*)
			PFLAG=0
			;;
		-*v*)
			VFLAG=0
			;;
		*)
			echo "usage: ${0} [-pv] source destination"
			exit 1
			;;
	esac
fi

if ! [ -d ${SRC} ]; then
	echo "${0}: ${SRC} does not exist"
	exit 1
fi

if ! [ -d ${DST} ]; then
	if [ ${PFLAG} ]; then
		if [ ${VFLAG} ]; then
			mkdir -pv ${DST}
		else
			mkdir -p ${DST}
		fi
	else
		echo "${0}: ${DST} does not exist"
		exit 1
	fi
fi

if [ ${VFLAG} ]; then
	(cd ${SRC} && tar -cvf - .) | (cd ${DST} && tar -xvf -)
else
	(cd ${SRC} && tar -cf - .) | (cd ${DST} && tar -xf -)
fi

exit 0
