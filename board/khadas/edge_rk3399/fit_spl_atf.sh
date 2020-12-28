#!/bin/sh

## hyphop ##

CMP=lzo
CMP=none
UBOOT=u-boot-nodtb.bin
UBOOT_CMP=$UBOOT
[ "$CMP" = "none" ] || {
UBOOT_CMP=$UBOOT.$CMP
lzop -c9 $UBOOT > $UBOOT_CMP
}
echo "[i] $0 : $@ ($CMP)">&2
ls -l1 $UBOOT* 1>&2

cat << END
/dts-v1/;

/ {
	description = "FIT image for U-Boot with bl31 (TF-A)";
	#address-cells = <1>;

	images {

		uboot {
			description = "U-Boot (64-bit)";
			data = /incbin/("$UBOOT_CMP");
			type = "standalone";
			os = "U-Boot";
			arch = "arm64";
			compression = "$CMP";
			load = <0x00200000>;
		};
		/*
		atf_1 {
			description = "ARM Trusted Firmware";
			data = /incbin/("bl31_0x00040000.bin");
			type = "firmware";
			arch = "arm64";
			os = "arm-trusted-firmware";
			compression = "none";
			load = <0x00040000>;
			entry = <0x00040000>;
		};

		atf_2 {
			description = "ARM Trusted Firmware";
			data = /incbin/("bl31_0xff3b0000.bin");
			type = "firmware";
			arch = "arm64";
			os = "arm-trusted-firmware";
			compression = "none";
			load = <0xff3b0000>;
		};

		atf_3 {
			description = "ARM Trusted Firmware";
			data = /incbin/("bl31_0xff8c0000.bin");
			type = "firmware";
			arch = "arm64";
			os = "arm-trusted-firmware";
			compression = "none";
			load = <0xff8c0000>;
		};
		*/

		fdt_1 {
			description = "rk3399-khadas-edge-x.dtb";
			data = /incbin/("u-boot.dtb");
			type = "flat_dt";
			compression = "none";
		};

	};

	configurations {
		default = "config_1";
		config_1 {
			description = "rk3399-khadas-edge";
			//firmware = "atf_1";
			//loadables = "uboot","atf_2","atf_3";
			loadables = "uboot";
			fdt = "fdt_1";
		};

	};

};
