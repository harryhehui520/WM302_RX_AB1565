
Build/fft7p5ms/pisplit_lc3i_fft7p5ms_position_independent.splitload.lib:     file format elf32-xtensa-le


Disassembly of section .text:

00000000 <_init-0xa4>:
       0:	000000f0 00002064 000023ac 00000000     ....d ...#......
      10:	0000237c 00000000 00002394 0000244c     |#.......#..L$..
      20:	000023dc 00000168 000023ef 00000e6c     .#..h....#..l...
      30:	000023ff 00001234 0000240f 000013c8     .#..4....$......
      40:	0000241f 0000197c 0000242d 00001b0c     .$..|...-$......
      50:	0000243b 00001eb8 000023c0 0000272c     ;$.......#..,'..
      60:	006ed9eb 000001b4 478dde64 b0000001     ..n.....d..G....
      70:	79bc3854 9d839db0 00009d83 d18053ce     T8.y.........S..
      80:	000008a8 00000a40 5a82799a a57d8666     ....@....y.Zf.}.
      90:	0000a57d 00000570 00000370 00002384     }...p...p....#..
      a0:	000000bc                                ....

000000a4 <_init>:
      a4:	008136        	entry	a1, 64
      a7:	ffd681        	l32r	a8, 0 (f0 <frame_dummy>)
      aa:	f03d           	nop.n
      ac:	0008e0        	callx8	a8
      af:	ffd581        	l32r	a8, 4 (2064 <__do_global_ctors_aux>)
      b2:	f03d           	nop.n
      b4:	0008e0        	callx8	a8
      b7:	f01d           	retw.n

000000b9 <_init+0x15>:
      b9:	000000                                        ...

000000bc <__do_global_dtors_aux>:
      bc:	004136        	entry	a1, 32
      bf:	ffd221        	l32r	a2, 8 (23ac <__do_global_dtors_aux.completed>)
      c2:	000232        	l8ui	a3, a2, 0
      c5:	23ec           	bnez.n	a3, eb <__do_global_dtors_aux+0x2f>

000000c7 <__do_global_dtors_aux+0xb>:
      c7:	1248           	l32i.n	a4, a2, 4
      c9:	0438           	l32i.n	a3, a4, 0
      cb:	444b           	addi.n	a4, a4, 4
      cd:	738c           	beqz.n	a3, d8 <__do_global_dtors_aux+0x1c>
      cf:	1249           	s32i.n	a4, a2, 4
      d1:	0003e0        	callx8	a3
      d4:	fffbc6        	j	c7 <__do_global_dtors_aux+0xb>

000000d7 <__do_global_dtors_aux+0x1b>:
	...

000000d8 <__do_global_dtors_aux+0x1c>:
      d8:	ffcd31        	l32r	a3, c (0 <_text_start>)
      db:	ffcda1        	l32r	a10, 10 (237c <__FRAME_END__>)
      de:	438c           	beqz.n	a3, e6 <__do_global_dtors_aux+0x2a>
      e0:	ffcb81        	l32r	a8, c (0 <_text_start>)
      e3:	0008e0        	callx8	a8
      e6:	130c           	movi.n	a3, 1
      e8:	004232        	s8i	a3, a2, 0
      eb:	f01d           	retw.n

000000ed <__do_global_dtors_aux+0x31>:
      ed:	000000                                        ...

000000f0 <frame_dummy>:
      f0:	004136        	entry	a1, 32
      f3:	ffc821        	l32r	a2, 14 (0 <_text_start>)
      f6:	ffc6a1        	l32r	a10, 10 (237c <__FRAME_END__>)
      f9:	ffc7b1        	l32r	a11, 18 (2394 <frame_dummy.object>)
      fc:	428c           	beqz.n	a2, 104 <frame_dummy+0x14>
      fe:	ffc581        	l32r	a8, 14 (0 <_text_start>)
     101:	0008e0        	callx8	a8

00000104 <frame_dummy+0x14>:
     104:	f01d           	retw.n

00000106 <frame_dummy+0x16>:
	...

00000108 <_start>:
     108:	004136        	entry	a1, 32
     10b:	ffc431        	l32r	a3, 1c (244c <printf_ptr>)
     10e:	0228           	l32i.n	a2, a2, 0
     110:	ffc4a1        	l32r	a10, 20 (23dc <export_parameter_array+0x1c>)
     113:	ffc4b1        	l32r	a11, 24 (168 <fix_fft_Init>)
     116:	0329           	s32i.n	a2, a3, 0
     118:	0002e0        	callx8	a2
     11b:	0328           	l32i.n	a2, a3, 0
     11d:	ffc2a1        	l32r	a10, 28 (23ef <export_parameter_array+0x2f>)
     120:	ffc3b1        	l32r	a11, 2c (e6c <fix_fft15>)
     123:	0002e0        	callx8	a2
     126:	0328           	l32i.n	a2, a3, 0
     128:	ffc2a1        	l32r	a10, 30 (23ff <export_parameter_array+0x3f>)
     12b:	ffc2b1        	l32r	a11, 34 (1234 <fix_fft30>)
     12e:	0002e0        	callx8	a2
     131:	0328           	l32i.n	a2, a3, 0
     133:	ffc1a1        	l32r	a10, 38 (240f <export_parameter_array+0x4f>)
     136:	ffc1b1        	l32r	a11, 3c (13c8 <fix_fft40>)
     139:	0002e0        	callx8	a2
     13c:	0328           	l32i.n	a2, a3, 0
     13e:	ffc0a1        	l32r	a10, 40 (241f <export_parameter_array+0x5f>)
     141:	ffc0b1        	l32r	a11, 44 (197c <FFT4N>)
     144:	0002e0        	callx8	a2
     147:	0328           	l32i.n	a2, a3, 0
     149:	ffbfa1        	l32r	a10, 48 (242d <export_parameter_array+0x6d>)
     14c:	ffc0b1        	l32r	a11, 4c (1b0c <FFT8N>)
     14f:	0002e0        	callx8	a2
     152:	0328           	l32i.n	a2, a3, 0
     154:	ffbfa1        	l32r	a10, 50 (243b <export_parameter_array+0x7b>)
     157:	ffbfb1        	l32r	a11, 54 (1eb8 <FFT12N>)
     15a:	0002e0        	callx8	a2
     15d:	ffbe21        	l32r	a2, 58 (23c0 <export_parameter_array>)
     160:	f01d           	retw.n

00000162 <_start+0x5a>:
     162:	00000000                                 ......

00000168 <fix_fft_Init>:
     168:	004136        	entry	a1, 32
     16b:	59a432        	movi	a3, 0x459
     16e:	ffbb41        	l32r	a4, 5c (272c <RotVector_40_32>)
     171:	1133c0        	slli	a3, a3, 4
     174:	223a           	add.n	a2, a2, a3
     176:	0429           	s32i.n	a2, a4, 0
     178:	f01d           	retw.n

0000017a <fix_fft_Init+0x12>:
	...

0000017c <fix_fft2_stage>:
     17c:	004136        	entry	a1, 32
     17f:	170c           	movi.n	a7, 1
     181:	117720        	slli	a7, a7, 14
     184:	0b0c           	movi.n	a11, 0
     186:	300774        	ae_cvtp24a16x2.ll	aep0, a7, a7
     189:	5d96b4        	ae_lp24x2f.xu	aep1, a6, a11
     18c:	f0068008df 	{ movi	a13, 8; ae_mulzaafp24s.hh.ll	aeq0, aep1, aep0 }
     191:	f5043f0cef 	{ ae_trunca32q48	a12, aeq0; ae_mulzasfp24s.hh.ll	aeq2, aep1, aep0 }
     196:	02c9           	s32i.n	a12, a2, 0
     198:	5df6d4        	ae_lp24x2f.xu	aep7, a6, a13
     19b:	f01eff2eef 	{ ae_trunca32q48	a14, aeq2; ae_mulzaafp24s.hh.ll	aeq1, aep7, aep0 }
     1a0:	f51c5403ef 	{ s32i.n	a14, a3, 0; ae_mulzasfp24s.hh.ll	aeq3, aep7, aep0 }
     1a5:	369604        	ae_trunca32q48	a6, aeq1
     1a8:	36bf04        	ae_trunca32q48	a15, aeq3
     1ab:	0469           	s32i.n	a6, a4, 0
     1ad:	05f9           	s32i.n	a15, a5, 0
     1af:	f01d           	retw.n

000001b1 <fix_fft2_stage+0x35>:
     1b1:	000000                                        ...

000001b4 <fix_fft5_stage>:
     1b4:	010136        	entry	a1, 128
     1b7:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
     1ba:	20c452        	addi	a5, a4, 32
     1bd:	601424        	ae_lq32f.iu	aeq0, a4, 8
     1c0:	605504        	ae_lq32f.iu	aeq1, a5, 0
     1c3:	590084017e 	{ addi	a7, a1, 64; ae_mulzasq32sp16s.ll	aeq2, aeq0, aep0, aeq1, aep0 }
     1c8:	2800bd742f 	{ ae_lq32f.iu	aeq3, a4, 8; ae_mulzaaq32sp16s.ll	aeq0, aeq0, aep0, aeq1, aep0 }
     1cd:	6055e4        	ae_lq32f.iu	aeq1, a5, -8
     1d0:	ba7c           	movi.n	a10, -5
     1d2:	8ea0c2        	movi	a12, 142
     1d5:	5b01b9a70f 	{ ae_sq32f.i	aeq2, a7, 0; ae_mulzasq32sp16s.ll	aeq2, aeq3, aep0, aeq1, aep0 }
     1da:	2b01fd34cf 	{ ae_lq32f.iu	aeq1, a4, -16; ae_mulzaaq32sp16s.ll	aeq3, aeq3, aep0, aeq1, aep0 }
     1df:	f8a179a71f 	{ ae_sq32f.i	aeq2, a7, 4; ae_mulq32sp16s.l	aeq1, aeq1, aep0 }
     1e4:	11aa40        	slli	a10, a10, 12
     1e7:	47dcc2        	addmi	a12, a12, 0x4700
     1ea:	fae6189caf 	{ ae_cvtp24a16x2.ll	aep1, a12, a10; ae_addq56	aeq2, aeq0, aeq3 }
     1ef:	f8ea3a013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_addq56	aeq0, aeq1, aeq2 }
     1f4:	d7e60084df 	{ movi	a13, 132; ae_mulfq32sp16s.l	aeq2, aeq2, aep1 }
     1f9:	bca0e2        	movi	a14, 188
     1fc:	632124        	ae_sq56s.i	aeq2, a1, 16
     1ff:	618134        	ae_lq56.i	aeq2, a1, 24
     202:	3b26fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulzasfq32sp16s.hh	aeq3, aeq2, aep1, aeq3, aep1 }
     207:	9dddd2        	addmi	a13, a13, 0xffff9d00
     20a:	79dee2        	addmi	a14, a14, 0x7900
     20d:	302ed4        	ae_cvtp24a16x2.ll	aep2, a14, a13
     210:	02dd           	mov.n	a13, a2
     212:	35a054        	ae_slliq56	aeq2, aeq2, 1
     215:	1021c2        	l32i	a12, a1, 64
     218:	f8e239cd0f 	{ ae_sq32f.iu	aeq0, a13, 0; ae_addq56	aeq0, aeq0, aeq2 }
     21d:	faa6fecc7f 	{ ae_cvtq48a32s	aeq1, a12; ae_subq56	aeq2, aeq0, aeq3 }
     222:	f8e63111ae 	{ l32i	a10, a1, 68; ae_addq56	aeq0, aeq0, aeq3 }
     227:	632124        	ae_sq56s.i	aeq2, a1, 16
     22a:	368a34        	ae_cvtq48a32s	aeq2, a10
     22d:	d4eb3a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_mulfq32sp16s.l	aeq0, aeq1, aep2 }
     232:	084b7de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_mulzaafq32sp16s.hh	aeq1, aeq1, aep2, aeq2, aep2 }
     237:	350054        	ae_slliq56	aeq0, aeq0, 1
     23a:	f86639b76f 	{ ae_sq32f.i	aeq3, a7, 24; ae_addq56	aeq0, aeq0, aeq1 }
     23f:	61c154        	ae_lq56.i	aeq3, a1, 40
     242:	623774        	ae_sq32f.i	aeq3, a7, 28
     245:	60d534        	ae_lq32f.iu	aeq3, a5, 12
     248:	620704        	ae_sq32f.i	aeq0, a7, 0
     24b:	6015e4        	ae_lq32f.iu	aeq0, a5, -8
     24e:	632134        	ae_sq56s.i	aeq2, a1, 24
     251:	609434        	ae_lq32f.iu	aeq2, a4, 12
     254:	5a02ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulzasq32sp16s.ll	aeq0, aeq2, aep0, aeq3, aep0 }
     259:	2b028fa35f 	{ movi	a5, -93; ae_mulzaaq32sp16s.ll	aeq2, aeq2, aep0, aeq3, aep0 }
     25e:	630154        	ae_sq56s.i	aeq0, a1, 40
     261:	61c154        	ae_lq56.i	aeq3, a1, 40
     264:	623724        	ae_sq32f.i	aeq3, a7, 8
     267:	601424        	ae_lq32f.iu	aeq0, a4, 8
     26a:	61c124        	ae_lq56.i	aeq3, a1, 16
     26d:	5902ba214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulzasq32sp16s.ll	aeq2, aeq0, aep0, aeq3, aep0 }
     272:	115590        	slli	a5, a5, 7
     275:	2802ba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulzaaq32sp16s.ll	aeq0, aeq0, aep0, aeq3, aep0 }
     27a:	303554        	ae_cvtp24a16x2.ll	aep3, a5, a5
     27d:	618134        	ae_lq56.i	aeq2, a1, 24
     280:	f68ed3b33f 	{ or	a11, a3, a3; ae_mulafq32sp16s.l	aeq1, aeq2, aep3 }
     285:	618154        	ae_lq56.i	aeq2, a1, 40
     288:	622744        	ae_sq32f.i	aeq2, a7, 16
     28b:	6094c4        	ae_lq32f.iu	aeq2, a4, -16
     28e:	632134        	ae_sq56s.i	aeq2, a1, 24
     291:	618144        	ae_lq56.i	aeq2, a1, 32
     294:	3b2471414e 	{ l32i	a4, a1, 80; ae_mulzasfq32sp16s.hh	aeq3, aeq2, aep1, aeq0, aep1 }
     299:	fa7231215e 	{ l32i	a5, a1, 72; ae_addq56	aeq2, aeq2, aeq0 }
     29e:	d6e63a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_mulfq32sp16s.l	aeq0, aeq2, aep1 }
     2a3:	61c134        	ae_lq56.i	aeq3, a1, 24
     2a6:	fba17a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_mulq32sp16s.l	aeq3, aeq3, aep0 }
     2ab:	360534        	ae_cvtq48a32s	aeq0, a5
     2ae:	fbfa3ec4bf 	{ ae_cvtq48a32s	aeq2, a4; ae_addq56	aeq3, aeq3, aeq2 }
     2b3:	632134        	ae_sq56s.i	aeq2, a1, 24
     2b6:	618144        	ae_lq56.i	aeq2, a1, 32
     2b9:	35a054        	ae_slliq56	aeq2, aeq2, 1
     2bc:	d5ea3a214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulfq32sp16s.l	aeq2, aeq0, aep2 }
     2c1:	621714        	ae_sq32f.i	aeq1, a7, 4
     2c4:	632164        	ae_sq56s.i	aeq2, a1, 48
     2c7:	618134        	ae_lq56.i	aeq2, a1, 24
     2ca:	094a3da14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulzaafq32sp16s.hh	aeq2, aeq0, aep2, aeq2, aep2 }
     2cf:	f87e3a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_addq56	aeq0, aeq3, aeq1 }
     2d4:	61c124        	ae_lq56.i	aeq3, a1, 16
     2d7:	f9a6f1619e 	{ l32i	a9, a1, 88; ae_subq56	aeq1, aeq0, aeq3 }
     2dc:	f8e63de16f 	{ ae_lq56.i	aeq3, a1, 48; ae_addq56	aeq0, aeq0, aeq3 }
     2e1:	630174        	ae_sq56s.i	aeq0, a1, 56
     2e4:	353054        	ae_slliq56	aeq0, aeq3, 1
     2e7:	f8e23ec9ff 	{ ae_cvtq48a32s	aeq3, a9; ae_addq56	aeq0, aeq0, aeq2 }
     2ec:	630124        	ae_sq56s.i	aeq0, a1, 16
     2ef:	610124        	ae_lq56.i	aeq0, a1, 16
     2f2:	f83afa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_subq56	aeq0, aeq3, aeq0 }
     2f7:	614134        	ae_lq56.i	aeq1, a1, 24
     2fa:	f58fba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulafq32sp16s.l	aeq2, aeq1, aep3 }
     2ff:	610124        	ae_lq56.i	aeq0, a1, 16
     302:	f87a31718e 	{ l32i	a8, a1, 92; ae_addq56	aeq0, aeq3, aeq0 }
     307:	fae7fde17f 	{ ae_lq56.i	aeq3, a1, 56; ae_roundsp24q48sym	aep5, aeq0 }
     30c:	364834        	ae_cvtq48a32s	aeq1, a8
     30f:	fbea39b75f 	{ ae_sq32f.i	aeq3, a7, 20; ae_addq56	aeq3, aeq1, aeq2 }
     314:	faaafda13f 	{ ae_lq56.i	aeq1, a1, 24; ae_subq56	aeq2, aeq1, aeq2 }
     319:	fbffb111de 	{ l32i	a13, a1, 68; ae_roundsp24q48sym	aep6, aeq3 }
     31e:	faefb151ee 	{ l32i	a14, a1, 84; ae_roundsp24q48sym	aep4, aeq1 }
     323:	fbf7fde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_roundsp24q48sym	aep7, aeq2 }
     328:	dcb0b9b73f 	{ ae_sq32f.i	aeq3, a7, 12; ae_selp24.hl	aep0, aep4, aep5 }
     32d:	ddf8becd3f 	{ ae_cvtq48a32s	aeq0, a13; ae_selp24.hl	aep2, aep6, aep7 }
     332:	364e34        	ae_cvtq48a32s	aeq1, a14
     335:	fb2af131fe 	{ l32i	a15, a1, 76; ae_subq56	aeq3, aeq1, aeq0 }
     33a:	f86a3101ce 	{ l32i	a12, a1, 64; ae_addq56	aeq0, aeq1, aeq0 }
     33f:	faffbde15f 	{ ae_lq56.i	aeq3, a1, 40; ae_roundsp24q48sym	aep4, aeq3 }
     344:	fae7fecc7f 	{ ae_cvtq48a32s	aeq1, a12; ae_roundsp24q48sym	aep5, aeq0 }
     349:	dc88fecfbf 	{ ae_cvtq48a32s	aeq2, a15; ae_selp24.hl	aep1, aep2, aep4 }
     34e:	fb7639fb0f 	{ ae_sq32f.iu	aeq3, a11, 0; ae_addq56	aeq3, aeq2, aeq1 }
     353:	fa36fe25bf 	{ ae_selp24.ll	aep2, aep2, aep5; ae_subq56	aeq2, aeq2, aeq1 }
     358:	fbffb6121f 	{ ae_sp24x2f.i	aep1, a2, 8; ae_roundsp24q48sym	aep6, aeq3 }
     35d:	fbf7fe06df 	{ ae_selp24.hl	aep3, aep0, aep6; ae_roundsp24q48sym	aep7, aeq2 }
     362:	dce236224f 	{ ae_sp24x2f.i	aep2, a2, 32; ae_selp24.ll	aep0, aep0, aep7 }
     367:	5e3224        	ae_sp24x2f.i	aep3, a2, 16
     36a:	5e0234        	ae_sp24x2f.i	aep0, a2, 24
     36d:	f01d           	retw.n

0000036f <fix_fft5_stage+0x1bb>:
	...

00000370 <fix_fft6>:
     370:	00a136        	entry	a1, 80
     373:	1184c0        	slli	a8, a4, 4
     376:	928a           	add.n	a9, a2, a8
     378:	838a           	add.n	a8, a3, a8
     37a:	b0d420        	addx8	a13, a4, a2
     37d:	0998           	l32i.n	a9, a9, 0
     37f:	a189           	s32i.n	a8, a1, 40
     381:	0d88           	l32i.n	a8, a13, 0
     383:	905440        	addx2	a5, a4, a4
     386:	a06440        	addx4	a6, a4, a4
     389:	1155e0        	slli	a5, a5, 2
     38c:	1166e0        	slli	a6, a6, 2
     38f:	219490        	srai	a9, a9, 4
     392:	218480        	srai	a8, a8, 4
     395:	e25a           	add.n	a14, a2, a5
     397:	f26a           	add.n	a15, a2, a6
     399:	360934        	ae_cvtq48a32s	aeq0, a9
     39c:	0e98           	l32i.n	a9, a14, 0
     39e:	364834        	ae_cvtq48a32s	aeq1, a8
     3a1:	fa6a300f8e 	{ l32i	a8, a15, 0; ae_addq56	aeq2, aeq1, aeq0 }
     3a6:	f826d0e36f 	{ add	a14, a3, a6; ae_subq56	aeq0, aeq0, aeq1 }
     3ab:	219490        	srai	a9, a9, 4
     3ae:	218480        	srai	a8, a8, 4
     3b1:	630134        	ae_sq56s.i	aeq0, a1, 24
     3b4:	364834        	ae_cvtq48a32s	aeq1, a8
     3b7:	360934        	ae_cvtq48a32s	aeq0, a9
     3ba:	fb6610889f 	{ add	a8, a8, a9; ae_addq56	aeq3, aeq0, aeq1 }
     3bf:	a09420        	addx4	a9, a4, a2
     3c2:	0968           	l32i.n	a6, a9, 0
     3c4:	02a8           	l32i.n	a10, a2, 0
     3c6:	f35a           	add.n	a15, a3, a5
     3c8:	215180        	srai	a5, a8, 1
     3cb:	216460        	srai	a6, a6, 4
     3ce:	f82ad5565f 	{ sub	a5, a6, a5; ae_subq56	aeq0, aeq1, aeq0 }
     3d3:	b159           	s32i.n	a5, a1, 44
     3d5:	2154a0        	srai	a5, a10, 4
     3d8:	364634        	ae_cvtq48a32s	aeq1, a6
     3db:	f9ee3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq1, aeq1, aeq3 }
     3e0:	360534        	ae_cvtq48a32s	aeq0, a5
     3e3:	fbe23b209f 	{ ae_sraiq56	aeq2, aeq2, 1; ae_addq56	aeq3, aeq0, aeq2 }
     3e8:	fa7e3a214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_addq56	aeq2, aeq3, aeq1 }
     3ed:	f93ec000bf 	{ movi	a11, 0; ae_subq56	aeq1, aeq3, aeq1 }
     3f2:	61c144        	ae_lq56.i	aeq3, a1, 32
     3f5:	f8a6f862bf 	{ ae_sq32f.x	aeq2, a2, a11; ae_subq56	aeq0, aeq0, aeq3 }
     3fa:	8b1c           	movi.n	a11, 24
     3fc:	870c           	movi.n	a7, 8
     3fe:	082c           	movi.n	a8, 32
     400:	091c           	movi.n	a9, 16
     402:	8a2c           	movi.n	a10, 40
     404:	6292b4        	ae_sq32f.x	aeq1, a2, a11
     407:	628274        	ae_sq32f.x	aeq0, a2, a7
     40a:	628294        	ae_sq32f.x	aeq0, a2, a9
     40d:	628284        	ae_sq32f.x	aeq0, a2, a8
     410:	b0d430        	addx8	a13, a4, a3
     413:	a0c430        	addx4	a12, a4, a3
     416:	6282a4        	ae_sq32f.x	aeq0, a2, a10
     419:	ff1141        	l32r	a4, 60 (6ed9eb <_end+0x6eb297>)
     41c:	398444        	ae_movpa24x2	aep0, a4, a4
     41f:	0f48           	l32i.n	a4, a15, 0
     421:	0ef8           	l32i.n	a15, a14, 0
     423:	618124        	ae_lq56.i	aeq2, a1, 16
     426:	fa8030a1be 	{ l32i	a11, a1, 40; ae_mulfq32sp24s.l	aeq0, aeq2, aep0 }
     42b:	61c134        	ae_lq56.i	aeq3, a1, 24
     42e:	2154f0        	srai	a5, a15, 4
     431:	fa813f0eef 	{ ae_trunca32q48	a14, aeq0; ae_mulfq32sp24s.l	aeq0, aeq3, aep0 }
     436:	36c534        	ae_cvtq48a32s	aeq3, a5
     439:	0b58           	l32i.n	a5, a11, 0
     43b:	0d68           	l32i.n	a6, a13, 0
     43d:	214440        	srai	a4, a4, 4
     440:	215450        	srai	a5, a5, 4
     443:	364434        	ae_cvtq48a32s	aeq1, a4
     446:	368534        	ae_cvtq48a32s	aeq2, a5
     449:	03b8           	l32i.n	a11, a3, 0
     44b:	fc0c7f0fef 	{ ae_trunca32q48	a15, aeq0; ae_movq56	aeq0, aeq1 }
     450:	f9ee3a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_addq56	aeq1, aeq1, aeq3 }
     455:	214460        	srai	a4, a6, 4
     458:	0cc8           	l32i.n	a12, a12, 0
     45a:	f8a6fec4bf 	{ ae_cvtq48a32s	aeq2, a4; ae_subq56	aeq0, aeq0, aeq3 }
     45f:	631134        	ae_sq56s.i	aeq1, a1, 24
     462:	614124        	ae_lq56.i	aeq1, a1, 16
     465:	f8763a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_addq56	aeq0, aeq2, aeq1 }
     46a:	f936d0454f 	{ add	a4, a5, a4; ae_subq56	aeq1, aeq2, aeq1 }
     46f:	21d4b0        	srai	a13, a11, 4
     472:	631124        	ae_sq56s.i	aeq1, a1, 16
     475:	364d34        	ae_cvtq48a32s	aeq1, a13
     478:	2164c0        	srai	a6, a12, 4
     47b:	f96a3d813f 	{ ae_lq56.i	aeq0, a1, 24; ae_addq56	aeq1, aeq1, aeq0 }
     480:	214140        	srai	a4, a4, 1
     483:	36c634        	ae_cvtq48a32s	aeq3, a6
     486:	358074        	ae_sraiq56	aeq2, aeq0, 1
     489:	fabad54d4f 	{ sub	a4, a13, a4; ae_subq56	aeq2, aeq3, aeq2 }
     48e:	fb7a3f25ef 	{ ae_trunca32q48	a5, aeq2; ae_addq56	aeq3, aeq3, aeq0 }
     493:	faee1064ff 	{ add	a6, a4, a15; ae_addq56	aeq2, aeq1, aeq3 }
     498:	fbaed5b4ff 	{ sub	a11, a4, a15; ae_subq56	aeq3, aeq1, aeq3 }
     49d:	614124        	ae_lq56.i	aeq1, a1, 16
     4a0:	0f0c           	movi.n	a15, 0
     4a2:	8c1c           	movi.n	a12, 24
     4a4:	f8813863ff 	{ ae_sq32f.x	aeq2, a3, a15; ae_mulfq32sp24s.l	aeq0, aeq1, aep0 }
     4a9:	618144        	ae_lq56.i	aeq2, a1, 32
     4ac:	fa807873cf 	{ ae_sq32f.x	aeq3, a3, a12; ae_mulfq32sp24s.l	aeq1, aeq2, aep0 }
     4b1:	60a274        	ae_lq32f.x	aeq2, a2, a7
     4b4:	fa7210d5ef 	{ add	a13, a5, a14; ae_addq56	aeq2, aeq2, aeq0 }
     4b9:	62a274        	ae_sq32f.x	aeq2, a2, a7
     4bc:	60e294        	ae_lq32f.x	aeq3, a2, a9
     4bf:	fa3aff14ef 	{ ae_trunca32q48	a4, aeq1; ae_subq56	aeq2, aeq3, aeq0 }
     4c4:	62a294        	ae_sq32f.x	aeq2, a2, a9
     4c7:	60a284        	ae_lq32f.x	aeq2, a2, a8
     4ca:	fa723ecd7f 	{ ae_cvtq48a32s	aeq1, a13; ae_addq56	aeq2, aeq2, aeq0 }
     4cf:	b1d8           	l32i.n	a13, a1, 44
     4d1:	62a284        	ae_sq32f.x	aeq2, a2, a8
     4d4:	60a2a4        	ae_lq32f.x	aeq2, a2, a10
     4d7:	f832d0f4df 	{ add	a15, a4, a13; ae_subq56	aeq0, aeq2, aeq0 }
     4dc:	f9813ecfff 	{ ae_cvtq48a32s	aeq3, a15; ae_mulfq32sp24s.l	aeq2, aeq1, aep0 }
     4e1:	6282a4        	ae_sq32f.x	aeq0, a2, a10
     4e4:	fb817b301f 	{ ae_sraiq56	aeq0, aeq3, 1; ae_mulfq32sp24s.l	aeq3, aeq3, aep0 }
     4e9:	fae23b927f 	{ ae_lq32f.x	aeq0, a2, a7; ae_addq56	aeq2, aeq0, aeq2 }
     4ee:	f8e23b105f 	{ ae_sraiq56	aeq1, aeq1, 1; ae_addq56	aeq0, aeq0, aeq2 }
     4f3:	fc147a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_movq56	aeq0, aeq2 }
     4f8:	f9aefec6bf 	{ ae_cvtq48a32s	aeq2, a6; ae_subq56	aeq1, aeq1, aeq3 }
     4fd:	fa763a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_addq56	aeq2, aeq2, aeq1 }
     502:	61c124        	ae_lq56.i	aeq3, a1, 16
     505:	62b274        	ae_sq32f.x	aeq3, a2, a7
     508:	62a374        	ae_sq32f.x	aeq2, a3, a7
     50b:	60a284        	ae_lq32f.x	aeq2, a2, a8
     50e:	f832fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_subq56	aeq0, aeq2, aeq0 }
     513:	f936d54d4f 	{ sub	a4, a13, a4; ae_subq56	aeq1, aeq2, aeq1 }
     518:	630124        	ae_sq56s.i	aeq0, a1, 16
     51b:	c055e0        	sub	a5, a5, a14
     51e:	618124        	ae_lq56.i	aeq2, a1, 16
     521:	360434        	ae_cvtq48a32s	aeq0, a4
     524:	f98038628f 	{ ae_sq32f.x	aeq2, a2, a8; ae_mulfq32sp24s.l	aeq2, aeq0, aep0 }
     529:	36c534        	ae_cvtq48a32s	aeq3, a5
     52c:	631134        	ae_sq56s.i	aeq1, a1, 24
     52f:	fb817b305f 	{ ae_sraiq56	aeq1, aeq3, 1; ae_mulfq32sp24s.l	aeq3, aeq3, aep0 }
     534:	f9763dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq1, aeq2, aeq1 }
     539:	fd14bb001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_negq56	aeq1, aeq1 }
     53e:	f83af8638f 	{ ae_sq32f.x	aeq2, a3, a8; ae_subq56	aeq0, aeq3, aeq0 }
     543:	60e294        	ae_lq32f.x	aeq3, a2, a9
     546:	fb7a3ecbbf 	{ ae_cvtq48a32s	aeq2, a11; ae_addq56	aeq3, aeq3, aeq0 }
     54b:	fb763a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_addq56	aeq3, aeq2, aeq1 }
     550:	f936fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq1, aeq2, aeq1 }
     555:	61c124        	ae_lq56.i	aeq3, a1, 16
     558:	62b294        	ae_sq32f.x	aeq3, a2, a9
     55b:	61c134        	ae_lq56.i	aeq3, a1, 24
     55e:	62b394        	ae_sq32f.x	aeq3, a3, a9
     561:	60e2a4        	ae_lq32f.x	aeq3, a2, a10
     564:	013cc4        	ae_subq56	aeq0, aeq3, aeq0
     567:	6282a4        	ae_sq32f.x	aeq0, a2, a10
     56a:	6293a4        	ae_sq32f.x	aeq1, a3, a10
     56d:	f01d           	retw.n

0000056f <fix_fft6+0x1ff>:
	...

00000570 <fix_fft12>:
     570:	01e136        	entry	a1, 240
     573:	140c           	movi.n	a4, 1
     575:	114430        	slli	a4, a4, 13
     578:	20c232        	addi	a3, a2, 32
     57b:	300444        	ae_cvtp24a16x2.ll	aep0, a4, a4
     57e:	40c242        	addi	a4, a2, 64
     581:	600304        	ae_lq32f.i	aeq0, a3, 0
     584:	d4e23d240f 	{ ae_lq32f.i	aeq1, a4, 0; ae_mulfq32sp16s.l	aeq0, aeq0, aep0 }
     589:	d4e37d431f 	{ ae_lq32f.i	aeq2, a3, 4; ae_mulfq32sp16s.l	aeq1, aeq1, aep0 }
     58e:	170c           	movi.n	a7, 1
     590:	fb660781de 	{ addi	a13, a1, 120; ae_addq56	aeq3, aeq0, aeq1 }
     595:	f826c0266f 	{ movi	a6, 38; ae_subq56	aeq0, aeq0, aeq1 }
     59a:	d6e27a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16s.l	aeq1, aeq2, aep0 }
     59f:	600414        	ae_lq32f.i	aeq0, a4, 4
     5a2:	d4e200018f 	{ movi	a8, 1; ae_mulfq32sp16s.l	aeq0, aeq0, aep0 }
     5a7:	117720        	slli	a7, a7, 14
     5aa:	fa6a18977f 	{ ae_cvtp24a16x2.ll	aep1, a7, a7; ae_addq56	aeq2, aeq1, aeq0 }
     5af:	f82afa213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_subq56	aeq0, aeq1, aeq0 }
     5b4:	fb66fd532f 	{ ae_lq32f.iu	aeq2, a3, 8; ae_movp48	aep7, aep1 }
     5b9:	d7e23a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_mulfq32sp16s.l	aeq2, aeq2, aep0 }
     5be:	601424        	ae_lq32f.iu	aeq0, a4, 8
     5c1:	030214        	ae_mulfq32sp16s.l	aeq0, aeq0, aep0
     5c4:	91d662        	addmi	a6, a6, 0xffff9100
     5c7:	f97218a66f 	{ ae_cvtp24a16x2.ll	aep2, a6, a6; ae_addq56	aeq1, aeq2, aeq0 }
     5cc:	f832fd431f 	{ ae_lq32f.i	aeq2, a3, 4; ae_subq56	aeq0, aeq2, aeq0 }
     5d1:	d7e23a117f 	{ ae_sq56s.i	aeq1, a1, 56; ae_mulfq32sp16s.l	aeq2, aeq2, aep0 }
     5d6:	604414        	ae_lq32f.i	aeq1, a4, 4
     5d9:	d4e33a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_mulfq32sp16s.l	aeq0, aeq1, aep0 }
     5de:	118840        	slli	a8, a8, 12
     5e1:	f97218b88f 	{ ae_cvtp24a16x2.ll	aep3, a8, a8; ae_addq56	aeq1, aeq2, aeq0 }
     5e6:	f832fd420f 	{ ae_lq32f.i	aeq2, a2, 0; ae_subq56	aeq0, aeq2, aeq0 }
     5eb:	fc1c7a016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_movq56	aeq0, aeq3 }
     5f0:	d7e206c15e 	{ addi	a5, a1, 108; ae_mulfq32sp16s.l	aeq2, aeq2, aep0 }
     5f5:	d7e740da9f 	{ movi	a9, 218; ae_mulfq32sp16s.l	aeq3, aeq3, aep1 }
     5fa:	f8720002ef 	{ movi	a14, 2; ae_addq56	aeq0, aeq2, aeq0 }
     5ff:	fbb6fd421f 	{ ae_lq32f.i	aeq2, a2, 4; ae_subq56	aeq3, aeq2, aeq3 }
     604:	d6e23a0dbf 	{ ae_sq56s.i	aeq0, a13, -40; ae_mulfq32sp16s.l	aeq0, aeq2, aep0 }
     609:	633de4        	ae_sq56s.i	aeq3, a13, -16
     60c:	61c134        	ae_lq56.i	aeq3, a1, 24
     60f:	d7e700026f 	{ movi	a6, 2; ae_mulfq32sp16s.l	aeq2, aeq3, aep1 }
     614:	01cbc4        	ae_addq56	aeq3, aeq0, aeq3
     617:	f8a2fa3daf 	{ ae_sq56s.i	aeq3, a13, -48; ae_subq56	aeq0, aeq0, aeq2 }
     61c:	60c384        	ae_lq32f.i	aeq3, a3, -32
     61f:	d6e33a0dcf 	{ ae_sq56s.i	aeq0, a13, -32; ae_mulfq32sp16s.l	aeq0, aeq3, aep0 }
     624:	61c174        	ae_lq56.i	aeq3, a1, 56
     627:	0392d4        	ae_mulfq32sp16s.l	aeq2, aeq3, aep1
     62a:	01cbc4        	ae_addq56	aeq3, aeq0, aeq3
     62d:	f8a2fd439f 	{ ae_lq32f.i	aeq2, a3, -28; ae_subq56	aeq0, aeq0, aeq2 }
     632:	d6e23a013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16s.l	aeq0, aeq2, aep0 }
     637:	d5e77a317f 	{ ae_sq56s.i	aeq3, a1, 56; ae_mulfq32sp16s.l	aeq3, aeq1, aep1 }
     63c:	f9663dcdbf 	{ ae_lq56.i	aeq2, a13, -40; ae_addq56	aeq1, aeq0, aeq1 }
     641:	f8a6fde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_subq56	aeq0, aeq0, aeq3 }
     646:	d7ee3a1ddf 	{ ae_sq56s.i	aeq1, a13, -24; ae_mulfq32sp16s.l	aeq2, aeq2, aep3 }
     64b:	d7eb7da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulfq32sp16s.l	aeq3, aeq3, aep2 }
     650:	d4eb3a0d9f 	{ ae_sq56s.i	aeq0, a13, -56; ae_mulfq32sp16s.l	aeq0, aeq1, aep2 }
     655:	614da4        	ae_lq56.i	aeq1, a13, -48
     658:	d4ef79e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16s.l	aeq1, aeq1, aep3 }
     65d:	d7ef3dedef 	{ ae_lq56.i	aeq3, a13, -16; ae_mulfq32sp16s.l	aeq2, aeq3, aep3 }
     662:	d4ee3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_mulfq32sp16s.l	aeq0, aeq0, aep3 }
     667:	d7ef7dadcf 	{ ae_lq56.i	aeq1, a13, -32; ae_mulfq32sp16s.l	aeq3, aeq3, aep3 }
     66c:	d4ef3a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_mulfq32sp16s.l	aeq0, aeq1, aep3 }
     671:	614124        	ae_lq56.i	aeq1, a1, 16
     674:	f9baf9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_subq56	aeq1, aeq3, aeq2 }
     679:	fafa39d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_addq56	aeq2, aeq3, aeq2 }
     67e:	614144        	ae_lq56.i	aeq1, a1, 32
     681:	01c9c4        	ae_addq56	aeq3, aeq0, aeq1
     684:	f826f9f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_subq56	aeq0, aeq0, aeq1 }
     689:	61c154        	ae_lq56.i	aeq3, a1, 40
     68c:	d6eb79e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16s.l	aeq1, aeq3, aep2 }
     691:	618174        	ae_lq56.i	aeq2, a1, 56
     694:	d7ee3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_mulfq32sp16s.l	aeq2, aeq2, aep3 }
     699:	614dd4        	ae_lq56.i	aeq1, a13, -24
     69c:	d4ef79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16s.l	aeq1, aeq1, aep3 }
     6a1:	61c164        	ae_lq56.i	aeq3, a1, 48
     6a4:	d7eb79e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16s.l	aeq3, aeq3, aep2 }
     6a9:	618124        	ae_lq56.i	aeq2, a1, 16
     6ac:	6ed992        	addmi	a9, a9, 0x6e00
     6af:	d6ee3dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_mulfq32sp16s.l	aeq0, aeq2, aep3 }
     6b4:	d7ee39d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16s.l	aeq2, aeq2, aep3 }
     6b9:	d7ef7dad9f 	{ ae_lq56.i	aeq1, a13, -56; ae_mulfq32sp16s.l	aeq3, aeq3, aep3 }
     6be:	d4ef58c99f 	{ ae_cvtp24a16x2.ll	aep4, a9, a9; ae_mulfq32sp16s.l	aeq1, aeq1, aep3 }
     6c3:	0944d4        	ae_movp48	aep5, aep4
     6c6:	d68e76        	loop	a14, 7a0 <fix_fft12+0x230>
     6c9:	f9b6fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq1, aeq2, aeq3 }
     6ce:	f9f63a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_addq56	aeq1, aeq2, aeq3 }
     6d3:	fb72bde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_movp48	aep6, aep4 }
     6d8:	fb7a3dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_addq56	aeq3, aeq3, aeq0 }
     6dd:	12bf7a113f 	{ ae_sq56s.i	aeq1, a1, 24; ae_mulzaafq32sp16s.ll	aeq1, aeq3, aep7, aeq2, aep5 }
     6e2:	43f77dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulzasfq32sp16s.ll	aeq3, aeq3, aep5, aeq2, aep7 }
     6e7:	f832fa115f 	{ ae_sq56s.i	aeq1, a1, 40; ae_subq56	aeq0, aeq2, aeq0 }
     6ec:	fa66fda15f 	{ ae_lq56.i	aeq1, a1, 40; ae_movp48	aep5, aep1 }
     6f1:	625514        	ae_sq32f.iu	aeq1, a5, 4
     6f4:	627514        	ae_sq32f.iu	aeq3, a5, 4
     6f7:	041666        	bnei	a6, 1, 6ff <fix_fft12+0x18f>
     6fa:	fe387f78bf 	{ ae_movp48	aep6, aep7; ae_negsp24s	aep5, aep1 }

000006ff <fix_fft12+0x18f>:
     6ff:	fb7afdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_movp48	aep7, aep6 }
     704:	10ba47819e 	{ addi	a9, a1, 120; ae_mulzaafq32sp16s.ll	aeq1, aeq0, aep6, aeq2, aep5 }
     709:	41d67d542f 	{ ae_lq32f.iu	aeq2, a4, 8; ae_mulzasfq32sp16s.ll	aeq3, aeq0, aep5, aeq2, aep6 }
     70e:	631144        	ae_sq56s.i	aeq1, a1, 32
     711:	605324        	ae_lq32f.iu	aeq1, a3, 8
     714:	d4e37a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_mulfq32sp16s.l	aeq1, aeq1, aep0 }
     719:	60c314        	ae_lq32f.i	aeq3, a3, 4
     71c:	d7e37a113f 	{ ae_sq56s.i	aeq1, a1, 24; ae_mulfq32sp16s.l	aeq3, aeq3, aep0 }
     721:	d6e27d813f 	{ ae_lq56.i	aeq0, a1, 24; ae_mulfq32sp16s.l	aeq1, aeq2, aep0 }
     726:	633164        	ae_sq56s.i	aeq3, a1, 48
     729:	fa663d641f 	{ ae_lq32f.i	aeq3, a4, 4; ae_addq56	aeq2, aeq0, aeq1 }
     72e:	d7e37a215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16s.l	aeq3, aeq3, aep0 }
     733:	f826fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_subq56	aeq0, aeq0, aeq1 }
     738:	f8f63a013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_addq56	aeq0, aeq2, aeq3 }
     73d:	fbb6fd238f 	{ ae_lq32f.i	aeq1, a3, -32; ae_subq56	aeq3, aeq2, aeq3 }
     742:	d5e37a316f 	{ ae_sq56s.i	aeq3, a1, 48; ae_mulfq32sp16s.l	aeq3, aeq1, aep0 }
     747:	614154        	ae_lq56.i	aeq1, a1, 40
     74a:	d5e70ff66e 	{ addi	a6, a6, -1; ae_mulfq32sp16s.l	aeq2, aeq1, aep1 }
     74f:	0179c4        	ae_addq56	aeq1, aeq3, aeq1
     752:	fbbafd439f 	{ ae_lq32f.i	aeq2, a3, -28; ae_subq56	aeq3, aeq3, aeq2 }
     757:	d6e27a117f 	{ ae_sq56s.i	aeq1, a1, 56; ae_mulfq32sp16s.l	aeq1, aeq2, aep0 }
     75c:	d5e63a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_mulfq32sp16s.l	aeq2, aeq0, aep1 }
     761:	f86a3de14f 	{ ae_lq56.i	aeq3, a1, 32; ae_addq56	aeq0, aeq1, aeq0 }
     766:	fbaaf9f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_subq56	aeq3, aeq1, aeq2 }
     76b:	614134        	ae_lq56.i	aeq1, a1, 24
     76e:	618174        	ae_lq56.i	aeq2, a1, 56
     771:	d4eb3a099f 	{ ae_sq56s.i	aeq0, a9, -56; ae_mulfq32sp16s.l	aeq0, aeq1, aep2 }
     776:	d7ee3da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulfq32sp16s.l	aeq2, aeq2, aep3 }
     77b:	d4ee39d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16s.l	aeq0, aeq0, aep3 }
     780:	614994        	ae_lq56.i	aeq1, a9, -56
     783:	d4ef7a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_mulfq32sp16s.l	aeq1, aeq1, aep3 }
     788:	61c164        	ae_lq56.i	aeq3, a1, 48
     78b:	d7eb79e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16s.l	aeq3, aeq3, aep2 }
     790:	618154        	ae_lq56.i	aeq2, a1, 40
     793:	d7ee39d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16s.l	aeq2, aeq2, aep3 }
     798:	d7ef7da14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulfq32sp16s.l	aeq3, aeq3, aep3 }
     79d:	033a54        	ae_mulfq32sp16s.l	aeq1, aeq1, aep3

000007a0 <fix_fft12+0x230>:
     7a0:	630124        	ae_sq56s.i	aeq0, a1, 16
     7a3:	610124        	ae_lq56.i	aeq0, a1, 16
     7a6:	f86a00037f 	{ movi	a7, 3; ae_addq56	aeq0, aeq1, aeq0 }
     7ab:	f8baf9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_subq56	aeq0, aeq3, aeq2 }
     7b0:	fbf639c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_addq56	aeq3, aeq2, aeq3 }
     7b5:	fc94bde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_negq56	aeq0, aeq3 }
     7ba:	01d142        	addmi	a4, a1, 0x100
     7bd:	fb3ef9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_subq56	aeq3, aeq3, aeq1 }
     7c2:	f8c262        	addi	a6, a2, -8
     7c5:	68c132        	addi	a3, a1, 104
     7c8:	98c442        	addi	a4, a4, -104
     7cb:	28c222        	addi	a2, a2, 40
     7ce:	627514        	ae_sq32f.iu	aeq3, a5, 4
     7d1:	ce8776        	loop	a7, 8a3 <fix_fft12+0x333>
     7d4:	601324        	ae_lq32f.iu	aeq0, a3, 8
     7d7:	604364        	ae_lq32f.i	aeq1, a3, 24
     7da:	60d424        	ae_lq32f.iu	aeq3, a4, 8
     7dd:	630124        	ae_sq56s.i	aeq0, a1, 16
     7e0:	631144        	ae_sq56s.i	aeq1, a1, 32
     7e3:	600414        	ae_lq32f.i	aeq0, a4, 4
     7e6:	604314        	ae_lq32f.i	aeq1, a3, 4
     7e9:	f96a3d437f 	{ ae_lq32f.i	aeq2, a3, 28; ae_addq56	aeq1, aeq1, aeq0 }
     7ee:	630134        	ae_sq56s.i	aeq0, a1, 24
     7f1:	600404        	ae_lq32f.i	aeq0, a4, 0
     7f4:	632154        	ae_sq56s.i	aeq2, a1, 40
     7f7:	618124        	ae_lq56.i	aeq2, a1, 16
     7fa:	faf63d647f 	{ ae_lq32f.i	aeq3, a4, 28; ae_addq56	aeq2, aeq2, aeq3 }
     7ff:	631124        	ae_sq56s.i	aeq1, a1, 16
     802:	614154        	ae_lq56.i	aeq1, a1, 40
     805:	f9ee3a801f 	{ ae_slliq56	aeq0, aeq0, 1; ae_addq56	aeq1, aeq1, aeq3 }
     80a:	633164        	ae_sq56s.i	aeq3, a1, 48
     80d:	630154        	ae_sq56s.i	aeq0, a1, 40
     810:	60c464        	ae_lq32f.i	aeq3, a4, 24
     813:	610144        	ae_lq56.i	aeq0, a1, 32
     816:	f8e63ab0df 	{ ae_slliq56	aeq3, aeq3, 1; ae_addq56	aeq0, aeq0, aeq3 }
     81b:	633144        	ae_sq56s.i	aeq3, a1, 32
     81e:	61c154        	ae_lq56.i	aeq3, a1, 40
     821:	fbb6c781ae 	{ addi	a10, a1, 120; ae_subq56	aeq3, aeq2, aeq3 }
     826:	633154        	ae_sq56s.i	aeq3, a1, 40
     829:	61c164        	ae_lq56.i	aeq3, a1, 48
     82c:	35f054        	ae_slliq56	aeq3, aeq3, 1
     82f:	633164        	ae_sq56s.i	aeq3, a1, 48
     832:	61c144        	ae_lq56.i	aeq3, a1, 32
     835:	01cfc4        	ae_subq56	aeq3, aeq0, aeq3
     838:	633144        	ae_sq56s.i	aeq3, a1, 32
     83b:	61c134        	ae_lq56.i	aeq3, a1, 24
     83e:	35f054        	ae_slliq56	aeq3, aeq3, 1
     841:	fb723a3a9f 	{ ae_sq56s.i	aeq3, a10, -56; ae_addq56	aeq3, aeq2, aeq0 }
     846:	f832fa317f 	{ ae_sq56s.i	aeq3, a1, 56; ae_subq56	aeq0, aeq2, aeq0 }
     84b:	630134        	ae_sq56s.i	aeq0, a1, 24
     84e:	618174        	ae_lq56.i	aeq2, a1, 56
     851:	610124        	ae_lq56.i	aeq0, a1, 16
     854:	61ca94        	ae_lq56.i	aeq3, a10, -56
     857:	faa6f9e62f 	{ ae_sq32f.iu	aeq2, a6, 8; ae_subq56	aeq2, aeq0, aeq3 }
     85c:	61c164        	ae_lq56.i	aeq3, a1, 48
     85f:	faaefa217f 	{ ae_sq56s.i	aeq2, a1, 56; ae_subq56	aeq2, aeq1, aeq3 }
     864:	61c134        	ae_lq56.i	aeq3, a1, 24
     867:	fb6639f22f 	{ ae_sq32f.iu	aeq3, a2, 8; ae_addq56	aeq3, aeq0, aeq1 }
     86c:	fb26fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq3, aeq0, aeq1 }
     871:	614134        	ae_lq56.i	aeq1, a1, 24
     874:	610154        	ae_lq56.i	aeq0, a1, 40
     877:	621614        	ae_sq32f.i	aeq1, a6, 4
     87a:	fae23a216f 	{ ae_sq56s.i	aeq2, a1, 48; ae_addq56	aeq2, aeq0, aeq2 }
     87f:	623214        	ae_sq32f.i	aeq3, a2, 4
     882:	614144        	ae_lq56.i	aeq1, a1, 32
     885:	61c174        	ae_lq56.i	aeq3, a1, 56
     888:	fa3ef9a66f 	{ ae_sq32f.i	aeq2, a6, 24; ae_subq56	aeq2, aeq3, aeq1 }
     88d:	f97e3a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_addq56	aeq1, aeq3, aeq1 }
     892:	618164        	ae_lq56.i	aeq2, a1, 48
     895:	f8a2fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     89a:	622674        	ae_sq32f.i	aeq2, a6, 28
     89d:	620264        	ae_sq32f.i	aeq0, a2, 24
     8a0:	621274        	ae_sq32f.i	aeq1, a2, 28
     8a3:	f01d           	retw.n

000008a5 <fix_fft12+0x335>:
     8a5:	000000                                        ...

000008a8 <fix_fft15_stage>:
     8a8:	006136        	entry	a1, 48
     8ab:	067d           	mov.n	a7, a6
     8ad:	fded61        	l32r	a6, 64 (1b4 <fix_fft5_stage>)
     8b0:	50c4f2        	addi	a15, a4, 80
     8b3:	b44b           	addi.n	a11, a4, 4
     8b5:	04ad           	mov.n	a10, a4
     8b7:	04cd           	mov.n	a12, a4
     8b9:	07dd           	mov.n	a13, a7
     8bb:	28c432        	addi	a3, a4, 40
     8be:	21f9           	s32i.n	a15, a1, 8
     8c0:	0006e0        	callx8	a6
     8c3:	2cc4b2        	addi	a11, a4, 44
     8c6:	03ad           	mov.n	a10, a3
     8c8:	03cd           	mov.n	a12, a3
     8ca:	07dd           	mov.n	a13, a7
     8cc:	3139           	s32i.n	a3, a1, 12
     8ce:	0006e0        	callx8	a6
     8d1:	21a8           	l32i.n	a10, a1, 8
     8d3:	54c4b2        	addi	a11, a4, 84
     8d6:	07dd           	mov.n	a13, a7
     8d8:	0acd           	mov.n	a12, a10
     8da:	0a3d           	mov.n	a3, a10
     8dc:	0006e0        	callx8	a6
     8df:	672c           	movi.n	a7, 38
     8e1:	91d772        	addmi	a7, a7, 0xffff9100
     8e4:	5c0454        	ae_lp24x2f.i	aep0, a4, 40
     8e7:	5c1304        	ae_lp24x2f.i	aep1, a3, 0
     8ea:	d9212f340f 	{ ae_lp24x2f.i	aep3, a4, 0; ae_addsp24s	aep2, aep0, aep1 }
     8ef:	dc22d8877f 	{ ae_cvtp24a16x2.ll	aep0, a7, a7; ae_subsp24s	aep1, aep0, aep1 }
     8f4:	ea058000ef 	{ movi	a14, 0; ae_mulfp24s.ll	aeq0, aep1, aep0 }
     8f9:	ea04c02cff 	{ movi	a15, 44; ae_mulfp24s.hl	aeq1, aep1, aep0 }
     8fe:	da4d11755f 	{ addx2	a7, a5, a5; ae_addsp24s	aep4, aep3, aep2 }
     903:	cd08a942ef 	{ ae_sp24x2f.x	aep4, a2, a14; ae_sraip24	aep2, aep2, 1 }
     908:	1b8d74        	ae_roundsp24q48asym	aep7, aeq0
     90b:	1b9d54        	ae_roundsp24q48asym	aep5, aeq1
     90e:	dd4ebe755f 	{ ae_selp24.hl	aep1, aep7, aep5; ae_subsp24s	aep2, aep3, aep2 }
     913:	a09550        	addx4	a9, a5, a5
     916:	07a134        	ae_addsp24s	aep3, aep2, aep1
     919:	07a194        	ae_subsp24s	aep1, aep2, aep1
     91c:	1169e0        	slli	a6, a9, 2
     91f:	dc64fe319f 	{ ae_selp24.hl	aep2, aep3, aep1; ae_selp24.hl	aep1, aep1, aep3 }
     924:	1199d0        	slli	a9, a9, 3
     927:	5f2264        	ae_sp24x2f.x	aep2, a2, a6
     92a:	5f1294        	ae_sp24x2f.x	aep1, a2, a9
     92d:	5c1464        	ae_lp24x2f.i	aep1, a4, 48
     930:	5c2314        	ae_lp24x2f.i	aep2, a3, 8
     933:	da452f541f 	{ ae_lp24x2f.i	aep5, a4, 8; ae_addsp24s	aep4, aep1, aep2 }
     938:	079294        	ae_subsp24s	aep1, aep1, aep2
     93b:	019054        	ae_mulfp24s.hl	aeq2, aep1, aep0
     93e:	019874        	ae_mulfp24s.ll	aeq3, aep1, aep0
     941:	0f40b4        	ae_sraip24	aep3, aep4, 1
     944:	1bbd64        	ae_roundsp24q48asym	aep6, aeq3
     947:	1bad74        	ae_roundsp24q48asym	aep7, aeq2
     94a:	dd76be6f9f 	{ ae_selp24.hl	aep6, aep6, aep7; ae_subsp24s	aep2, aep5, aep3 }
     94f:	07d414        	ae_addsp24s	aep1, aep5, aep4
     952:	07a644        	ae_addsp24s	aep4, aep2, aep6
     955:	07a6a4        	ae_subsp24s	aep2, aep2, aep6
     958:	d165f0        	mul16s	a6, a5, a15
     95b:	11d7d0        	slli	a13, a7, 3
     95e:	dd88be4adf 	{ ae_selp24.hl	aep7, aep4, aep2; ae_selp24.hl	aep2, aep2, aep4 }
     963:	11a5e0        	slli	a10, a5, 2
     966:	5f12d4        	ae_sp24x2f.x	aep1, a2, a13
     969:	5f7264        	ae_sp24x2f.x	aep7, a2, a6
     96c:	5f22a4        	ae_sp24x2f.x	aep2, a2, a10
     96f:	5c1474        	ae_lp24x2f.i	aep1, a4, 56
     972:	5c3324        	ae_lp24x2f.i	aep3, a3, 16
     975:	da652f542f 	{ ae_lp24x2f.i	aep5, a4, 16; ae_addsp24s	aep4, aep1, aep3 }
     97a:	dc66c034af 	{ movi	a10, 52; ae_subsp24s	aep1, aep1, aep3 }
     97f:	019054        	ae_mulfp24s.hl	aeq2, aep1, aep0
     982:	019874        	ae_mulfp24s.ll	aeq3, aep1, aep0
     985:	0f40b4        	ae_sraip24	aep3, aep4, 1
     988:	1bbd64        	ae_roundsp24q48asym	aep6, aeq3
     98b:	1bad74        	ae_roundsp24q48asym	aep7, aeq2
     98e:	11e7c0        	slli	a14, a7, 4
     991:	d8957e6f9f 	{ ae_selp24.hl	aep6, aep6, aep7; ae_addsp24s	aep1, aep5, aep4 }
     996:	dd76a912ef 	{ ae_sp24x2f.x	aep1, a2, a14; ae_subsp24s	aep2, aep5, aep3 }
     99b:	f08550        	subx8	a8, a5, a5
     99e:	dac93031ee 	{ l32i	a14, a1, 12; ae_addsp24s	aep4, aep2, aep6 }
     9a3:	07a6a4        	ae_subsp24s	aep2, aep2, aep6
     9a6:	dd88be4adf 	{ ae_selp24.hl	aep7, aep4, aep2; ae_selp24.hl	aep2, aep2, aep4 }
     9ab:	11c5d0        	slli	a12, a5, 3
     9ae:	11f8e0        	slli	a15, a8, 2
     9b1:	5f72c4        	ae_sp24x2f.x	aep7, a2, a12
     9b4:	5f22f4        	ae_sp24x2f.x	aep2, a2, a15
     9b7:	5c1e34        	ae_lp24x2f.i	aep1, a14, 24
     9ba:	5c3334        	ae_lp24x2f.i	aep3, a3, 24
     9bd:	da652f543f 	{ ae_lp24x2f.i	aep5, a4, 24; ae_addsp24s	aep4, aep1, aep3 }
     9c2:	079394        	ae_subsp24s	aep1, aep1, aep3
     9c5:	019054        	ae_mulfp24s.hl	aeq2, aep1, aep0
     9c8:	019874        	ae_mulfp24s.ll	aeq3, aep1, aep0
     9cb:	0f40b4        	ae_sraip24	aep3, aep4, 1
     9ce:	1bbd64        	ae_roundsp24q48asym	aep6, aeq3
     9d1:	1bad74        	ae_roundsp24q48asym	aep7, aeq2
     9d4:	dd76be6f9f 	{ ae_selp24.hl	aep6, aep6, aep7; ae_subsp24s	aep2, aep5, aep3 }
     9d9:	07d414        	ae_addsp24s	aep1, aep5, aep4
     9dc:	07a644        	ae_addsp24s	aep4, aep2, aep6
     9df:	07a6a4        	ae_subsp24s	aep2, aep2, aep6
     9e2:	d195a0        	mul16s	a9, a5, a10
     9e5:	1177e0        	slli	a7, a7, 2
     9e8:	11b5b0        	slli	a11, a5, 5
     9eb:	dd88fe4adf 	{ ae_selp24.hl	aep7, aep4, aep2; ae_selp24.hl	aep3, aep2, aep4 }
     9f0:	5f1274        	ae_sp24x2f.x	aep1, a2, a7
     9f3:	5f72b4        	ae_sp24x2f.x	aep7, a2, a11
     9f6:	5f3294        	ae_sp24x2f.x	aep3, a2, a9
     9f9:	5c1e44        	ae_lp24x2f.i	aep1, a14, 32
     9fc:	5c4344        	ae_lp24x2f.i	aep4, a3, 32
     9ff:	da856f644f 	{ ae_lp24x2f.i	aep6, a4, 32; ae_addsp24s	aep5, aep1, aep4 }
     a04:	079494        	ae_subsp24s	aep1, aep1, aep4
     a07:	019874        	ae_mulfp24s.ll	aeq3, aep1, aep0
     a0a:	019054        	ae_mulfp24s.hl	aeq2, aep1, aep0
     a0d:	0f50b4        	ae_sraip24	aep3, aep5, 1
     a10:	07e574        	ae_addsp24s	aep7, aep6, aep5
     a13:	1bbd44        	ae_roundsp24q48asym	aep4, aeq3
     a16:	1bad54        	ae_roundsp24q48asym	aep5, aeq2
     a19:	b0c550        	addx8	a12, a5, a5
     a1c:	dc7afe4d9f 	{ ae_selp24.hl	aep6, aep4, aep5; ae_subsp24s	aep1, aep6, aep3 }
     a21:	116ce0        	slli	a6, a12, 2
     a24:	d9c569726f 	{ ae_sp24x2f.x	aep7, a2, a6; ae_addsp24s	aep3, aep1, aep6 }
     a29:	079694        	ae_subsp24s	aep1, aep1, aep6
     a2c:	dc64fe39df 	{ ae_selp24.hl	aep7, aep3, aep1; ae_selp24.hl	aep1, aep1, aep3 }
     a31:	11f8d0        	slli	a15, a8, 3
     a34:	11d5c0        	slli	a13, a5, 4
     a37:	5f72f4        	ae_sp24x2f.x	aep7, a2, a15
     a3a:	5f12d4        	ae_sp24x2f.x	aep1, a2, a13
     a3d:	f01d           	retw.n

00000a3f <fix_fft15_stage+0x197>:
	...

00000a40 <fix_fft5_8K>:
     a40:	016136        	entry	a1, 176
     a43:	600204        	ae_lq32f.i	aeq0, a2, 0
     a46:	608244        	ae_lq32f.i	aeq2, a2, 16
     a49:	60c264        	ae_lq32f.i	aeq3, a2, 24
     a4c:	70c152        	addi	a5, a1, 112
     a4f:	350134        	ae_sraiq56	aeq0, aeq0, 4
     a52:	20c272        	addi	a7, a2, 32
     a55:	604224        	ae_lq32f.i	aeq1, a2, 8
     a58:	35a134        	ae_sraiq56	aeq2, aeq2, 4
     a5b:	35f134        	ae_sraiq56	aeq3, aeq3, 4
     a5e:	620504        	ae_sq32f.i	aeq0, a5, 0
     a61:	600704        	ae_lq32f.i	aeq0, a7, 0
     a64:	355134        	ae_sraiq56	aeq1, aeq1, 4
     a67:	350134        	ae_sraiq56	aeq0, aeq0, 4
     a6a:	622524        	ae_sq32f.i	aeq2, a5, 8
     a6d:	623534        	ae_sq32f.i	aeq3, a5, 12
     a70:	621514        	ae_sq32f.i	aeq1, a5, 4
     a73:	620544        	ae_sq32f.i	aeq0, a5, 16
     a76:	600524        	ae_lq32f.i	aeq0, a5, 8
     a79:	604534        	ae_lq32f.i	aeq1, a5, 12
     a7c:	fa26fd651f 	{ ae_lq32f.i	aeq3, a5, 4; ae_subq56	aeq2, aeq0, aeq1 }
     a81:	f8663d254f 	{ ae_lq32f.i	aeq1, a5, 16; ae_addq56	aeq0, aeq0, aeq1 }
     a86:	630134        	ae_sq56s.i	aeq0, a1, 24
     a89:	fa7e39a5bf 	{ ae_sq32f.i	aeq2, a5, -20; ae_addq56	aeq2, aeq3, aeq1 }
     a8e:	fb3efda13f 	{ ae_lq56.i	aeq1, a1, 24; ae_subq56	aeq3, aeq3, aeq1 }
     a93:	f9763d050f 	{ ae_lq32f.i	aeq0, a5, 0; ae_addq56	aeq1, aeq2, aeq1 }
     a98:	f86639b5af 	{ ae_sq32f.i	aeq3, a5, -24; ae_addq56	aeq0, aeq0, aeq1 }
     a9d:	ff0c79820f 	{ ae_sq32f.i	aeq0, a2, 0; ae_movq56	aeq3, aeq1 }
     aa2:	630164        	ae_sq56s.i	aeq0, a1, 48
     aa5:	600324        	ae_lq32f.i	aeq0, a3, 8
     aa8:	354134        	ae_sraiq56	aeq1, aeq0, 4
     aab:	600344        	ae_lq32f.i	aeq0, a3, 16
     aae:	8da082        	movi	a8, 141
     ab1:	621514        	ae_sq32f.i	aeq1, a5, 4
     ab4:	354134        	ae_sraiq56	aeq1, aeq0, 4
     ab7:	600364        	ae_lq32f.i	aeq0, a3, 24
     aba:	621524        	ae_sq32f.i	aeq1, a5, 8
     abd:	354134        	ae_sraiq56	aeq1, aeq0, 4
     ac0:	610134        	ae_lq56.i	aeq0, a1, 24
     ac3:	fd69f1        	l32r	a15, 68 (478dde64 <_end+0x478db710>)
     ac6:	47d882        	addmi	a8, a8, 0x4700
     ac9:	fa32c00baf 	{ movi	a10, 11; ae_subq56	aeq2, aeq2, aeq0 }
     ace:	3048f4        	ae_cvtp24a16x2.ll	aep4, a8, a15
     ad1:	d6f281a3df 	{ movi	a13, 0x1a3; ae_mulfq32sp16u.l	aeq0, aeq2, aep4 }
     ad6:	d77239953f 	{ ae_sq32f.i	aeq1, a5, 12; ae_mulfq32sp16s.h	aeq2, aeq2, aep4 }
     adb:	fd6491        	l32r	a9, 6c (b0000001 <_end+0xafffd8ad>)
     ade:	11aa40        	slli	a10, a10, 12
     ae1:	302a94        	ae_cvtp24a16x2.ll	aep2, a10, a9
     ae4:	11ad90        	slli	a10, a13, 7
     ae7:	fd65f1        	l32r	a15, 7c (d18053ce <_end+0xd1802c7a>)
     aea:	300af4        	ae_cvtp24a16x2.ll	aep0, a10, a15
     aed:	1721f2        	l32i	a15, a1, 92
     af0:	d7ebba214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq2, aeq3, aep2 }
     af5:	d76b7ecf7f 	{ ae_cvtq48a32s	aeq1, a15; ae_mulfq32sp16s.h	aeq3, aeq3, aep2 }
     afa:	d5e3ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq1, aep0 }
     aff:	350434        	ae_sraiq56	aeq0, aeq0, 16
     b02:	632124        	ae_sq56s.i	aeq2, a1, 16
     b05:	618144        	ae_lq56.i	aeq2, a1, 32
     b08:	f8723a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_addq56	aeq0, aeq2, aeq0 }
     b0d:	618134        	ae_lq56.i	aeq2, a1, 24
     b10:	61c124        	ae_lq56.i	aeq3, a1, 16
     b13:	630144        	ae_sq56s.i	aeq0, a1, 32
     b16:	352434        	ae_sraiq56	aeq0, aeq2, 16
     b19:	35b434        	ae_sraiq56	aeq2, aeq3, 16
     b1c:	d5633a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulfq32sp16s.h	aeq2, aeq1, aep0 }
     b21:	61c154        	ae_lq56.i	aeq3, a1, 40
     b24:	fd5481        	l32r	a8, 74 (9d839db0 <_end+0x9d83765c>)
     b27:	fd54e1        	l32r	a14, 78 (9d83 <_end+0x762f>)
     b2a:	f87a189e8f 	{ ae_cvtp24a16x2.ll	aep1, a14, a8; ae_addq56	aeq0, aeq3, aeq0 }
     b2f:	61c134        	ae_lq56.i	aeq3, a1, 24
     b32:	faf60203ee 	{ addi	a14, a3, 32; ae_addq56	aeq2, aeq2, aeq3 }
     b37:	1621a2        	l32i	a10, a1, 88
     b3a:	bca0c2        	movi	a12, 188
     b3d:	630124        	ae_sq56s.i	aeq0, a1, 16
     b40:	360a34        	ae_cvtq48a32s	aeq0, a10
     b43:	f9663d6e0f 	{ ae_lq32f.i	aeq3, a14, 0; ae_addq56	aeq1, aeq0, aeq1 }
     b48:	632134        	ae_sq56s.i	aeq2, a1, 24
     b4b:	d5e6fb318f 	{ ae_sraiq56	aeq2, aeq3, 4; ae_mulfq32sp16u.l	aeq3, aeq0, aep1 }
     b50:	d46639a54f 	{ ae_sq32f.i	aeq2, a5, 16; ae_mulfq32sp16s.h	aeq0, aeq0, aep1 }
     b55:	fd46b1        	l32r	a11, 70 (79bc3854 <_end+0x79bc1100>)
     b58:	79dcc2        	addmi	a12, a12, 0x7900
     b5b:	303cb4        	ae_cvtp24a16x2.ll	aep3, a12, a11
     b5e:	d4efba015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_mulfq32sp16u.l	aeq0, aeq1, aep3 }
     b63:	35f434        	ae_sraiq56	aeq3, aeq3, 16
     b66:	630174        	ae_sq56s.i	aeq0, a1, 56
     b69:	610154        	ae_lq56.i	aeq0, a1, 40
     b6c:	fbe63dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_addq56	aeq3, aeq0, aeq3 }
     b71:	fe747a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_truncq32	aeq2, aeq2 }
     b76:	d56f7da17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16s.h	aeq3, aeq1, aep3 }
     b7b:	351434        	ae_sraiq56	aeq0, aeq1, 16
     b7e:	f87a3aa09f 	{ ae_slliq56	aeq2, aeq2, 1; ae_addq56	aeq0, aeq3, aeq0 }
     b83:	614164        	ae_lq56.i	aeq1, a1, 48
     b86:	f9ea3d451f 	{ ae_lq32f.i	aeq2, a5, 4; ae_addq56	aeq1, aeq1, aeq2 }
     b8b:	60c544        	ae_lq32f.i	aeq3, a5, 16
     b8e:	f9f63a115f 	{ ae_sq56s.i	aeq1, a1, 40; ae_addq56	aeq1, aeq2, aeq3 }
     b93:	fab6fa016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_subq56	aeq2, aeq2, aeq3 }
     b98:	6325a4        	ae_sq56s.i	aeq2, a5, -48
     b9b:	600524        	ae_lq32f.i	aeq0, a5, 8
     b9e:	608534        	ae_lq32f.i	aeq2, a5, 12
     ba1:	f9a2fa117f 	{ ae_sq56s.i	aeq1, a1, 56; ae_subq56	aeq1, aeq0, aeq2 }
     ba6:	60c304        	ae_lq32f.i	aeq3, a3, 0
     ba9:	f9e23a15bf 	{ ae_sq56s.i	aeq1, a5, -40; ae_addq56	aeq1, aeq0, aeq2 }
     bae:	35b134        	ae_sraiq56	aeq2, aeq3, 4
     bb1:	61c144        	ae_lq56.i	aeq3, a1, 32
     bb4:	ff7c7d815f 	{ ae_lq56.i	aeq0, a1, 40; ae_truncq32	aeq3, aeq3 }
     bb9:	faa6f9a50f 	{ ae_sq32f.i	aeq2, a5, 0; ae_subq56	aeq2, aeq0, aeq3 }
     bbe:	f8e63de5af 	{ ae_lq56.i	aeq3, a5, -48; ae_addq56	aeq0, aeq0, aeq3 }
     bc3:	623584        	ae_sq32f.i	aeq3, a5, -32
     bc6:	632144        	ae_sq56s.i	aeq2, a1, 32
     bc9:	618124        	ae_lq56.i	aeq2, a1, 16
     bcc:	fe747de5bf 	{ ae_lq56.i	aeq3, a5, -40; ae_truncq32	aeq2, aeq2 }
     bd1:	623594        	ae_sq32f.i	aeq3, a5, -28
     bd4:	54c182        	addi	a8, a1, 84
     bd7:	61c174        	ae_lq56.i	aeq3, a1, 56
     bda:	f83efa015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_subq56	aeq0, aeq3, aeq1 }
     bdf:	fb7e3aa09f 	{ ae_slliq56	aeq2, aeq2, 1; ae_addq56	aeq3, aeq3, aeq1 }
     be4:	614164        	ae_lq56.i	aeq1, a1, 48
     be7:	fe6c7a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_truncq32	aeq2, aeq1 }
     bec:	614144        	ae_lq56.i	aeq1, a1, 32
     bef:	6215e4        	ae_sq32f.i	aeq1, a5, -8
     bf2:	614124        	ae_lq56.i	aeq1, a1, 16
     bf5:	f9ea31419e 	{ l32i	a9, a1, 80; ae_addq56	aeq1, aeq1, aeq2 }
     bfa:	631144        	ae_sq56s.i	aeq1, a1, 32
     bfd:	614134        	ae_lq56.i	aeq1, a1, 24
     c00:	015ac4        	ae_addq56	aeq1, aeq1, aeq2
     c03:	d5f2ba116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_mulfq32sp16u.l	aeq2, aeq0, aep4 }
     c08:	d4723d250f 	{ ae_lq32f.i	aeq1, a5, 0; ae_mulfq32sp16s.h	aeq0, aeq0, aep4 }
     c0d:	f9ee3b248f 	{ ae_sraiq56	aeq2, aeq2, 16; ae_addq56	aeq1, aeq1, aeq3 }
     c12:	d6ebfa113f 	{ ae_sq56s.i	aeq1, a1, 24; ae_mulfq32sp16u.l	aeq1, aeq3, aep2 }
     c17:	d76b7a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16s.h	aeq3, aeq3, aep2 }
     c1c:	610154        	ae_lq56.i	aeq0, a1, 40
     c1f:	355434        	ae_sraiq56	aeq1, aeq1, 16
     c22:	f97e3985ff 	{ ae_sq32f.i	aeq0, a5, -4; ae_addq56	aeq1, aeq3, aeq1 }
     c27:	fd6c7d812f 	{ ae_lq56.i	aeq0, a1, 16; ae_truncq32	aeq1, aeq1 }
     c2c:	f8e23ec9ff 	{ ae_cvtq48a32s	aeq3, a9; ae_addq56	aeq0, aeq0, aeq2 }
     c31:	d7e7ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16u.l	aeq2, aeq3, aep1 }
     c36:	610144        	ae_lq56.i	aeq0, a1, 32
     c39:	d6673985af 	{ ae_sq32f.i	aeq0, a5, -24; ae_mulfq32sp16s.h	aeq0, aeq3, aep1 }
     c3e:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     c41:	f8e23dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_addq56	aeq0, aeq0, aeq2 }
     c46:	630144        	ae_sq56s.i	aeq0, a1, 32
     c49:	fd747a901f 	{ ae_slliq56	aeq0, aeq1, 1; ae_truncq32	aeq1, aeq2 }
     c4e:	618164        	ae_lq56.i	aeq2, a1, 48
     c51:	6225b4        	ae_sq32f.i	aeq2, a5, -20
     c54:	618134        	ae_lq56.i	aeq2, a1, 24
     c57:	f8723151be 	{ l32i	a11, a1, 84; ae_addq56	aeq0, aeq2, aeq0 }
     c5c:	fa26f1b14e 	{ l32i	a4, a1, 108; ae_subq56	aeq2, aeq0, aeq1 }
     c61:	f8663ecb7f 	{ ae_cvtq48a32s	aeq1, a11; ae_addq56	aeq0, aeq0, aeq1 }
     c66:	fb7e39a5cf 	{ ae_sq32f.i	aeq2, a5, -16; ae_addq56	aeq3, aeq3, aeq1 }
     c6b:	d5e3b985df 	{ ae_sq32f.i	aeq0, a5, -12; ae_mulfq32sp16u.l	aeq2, aeq1, aep0 }
     c70:	d6efb1a15e 	{ l32i	a5, a1, 104; ae_mulfq32sp16u.l	aeq0, aeq3, aep3 }
     c75:	d4637b248f 	{ ae_sraiq56	aeq2, aeq2, 16; ae_mulfq32sp16s.h	aeq1, aeq1, aep0 }
     c7a:	d76f7b040f 	{ ae_sraiq56	aeq0, aeq0, 16; ae_mulfq32sp16s.h	aeq3, aeq3, aep3 }
     c7f:	faea31716e 	{ l32i	a6, a1, 92; ae_addq56	aeq2, aeq1, aeq2 }
     c84:	f97a3de14f 	{ ae_lq56.i	aeq3, a1, 32; ae_addq56	aeq1, aeq3, aeq0 }
     c89:	fc7c7161de 	{ l32i	a13, a1, 88; ae_truncq32	aeq0, aeq3 }
     c8e:	fe747a801f 	{ ae_slliq56	aeq0, aeq0, 1; ae_truncq32	aeq2, aeq2 }
     c93:	fd6c7181ee 	{ l32i	a14, a1, 96; ae_truncq32	aeq1, aeq1 }
     c98:	f8663191be 	{ l32i	a11, a1, 100; ae_addq56	aeq0, aeq0, aeq1 }
     c9d:	f9763988ff 	{ ae_sq32f.i	aeq0, a8, -4; ae_addq56	aeq1, aeq2, aeq1 }
     ca2:	621804        	ae_sq32f.i	aeq1, a8, 0
     ca5:	1521a2        	l32i	a10, a1, 84
     ca8:	1421f2        	l32i	a15, a1, 80
     cab:	61c134        	ae_lq56.i	aeq3, a1, 24
     cae:	cdea           	add.n	a12, a13, a14
     cb0:	c08ed0        	sub	a8, a14, a13
     cb3:	c0db60        	sub	a13, a11, a6
     cb6:	c0e5f0        	sub	a14, a5, a15
     cb9:	5f5a           	add.n	a5, a15, a5
     cbb:	fa4a           	add.n	a15, a10, a4
     cbd:	66ba           	add.n	a6, a6, a11
     cbf:	c044a0        	sub	a4, a4, a10
     cc2:	623304        	ae_sq32f.i	aeq3, a3, 0
     cc5:	22f9           	s32i.n	a15, a2, 8
     cc7:	42e9           	s32i.n	a14, a2, 16
     cc9:	6259           	s32i.n	a5, a2, 24
     ccb:	8249           	s32i.n	a4, a2, 32
     ccd:	23d9           	s32i.n	a13, a3, 8
     ccf:	43c9           	s32i.n	a12, a3, 16
     cd1:	6389           	s32i.n	a8, a3, 24
     cd3:	8369           	s32i.n	a6, a3, 32
     cd5:	f01d           	retw.n

00000cd7 <fix_fft5_8K+0x297>:
	...

00000cd8 <fix_fft10>:
     cd8:	014136        	entry	a1, 160
     cdb:	0b0c           	movi.n	a11, 0
     cdd:	026d           	mov.n	a6, a2
     cdf:	90f440        	addx2	a15, a4, a4
     ce2:	50c172        	addi	a7, a1, 80
     ce5:	045d           	mov.n	a5, a4
     ce7:	1184c0        	slli	a8, a4, 4
     cea:	5d86b4        	ae_lp24x2f.xu	aep0, a6, a11
     ced:	114fd0        	slli	a4, a15, 3
     cf0:	079d           	mov.n	a9, a7
     cf2:	7139           	s32i.n	a3, a1, 28
     cf4:	603080        	neg	a3, a8
     cf7:	5dc644        	ae_lp24x2f.xu	aep4, a6, a4
     cfa:	5dd634        	ae_lp24x2f.xu	aep5, a6, a3
     cfd:	5f89b4        	ae_sp24x2f.xu	aep0, a9, a11
     d00:	8a0c           	movi.n	a10, 8
     d02:	5fc9a4        	ae_sp24x2f.xu	aep4, a9, a10
     d05:	5de644        	ae_lp24x2f.xu	aep6, a6, a4
     d08:	5fd9a4        	ae_sp24x2f.xu	aep5, a9, a10
     d0b:	5df634        	ae_lp24x2f.xu	aep7, a6, a3
     d0e:	5fe9a4        	ae_sp24x2f.xu	aep6, a9, a10
     d11:	1d0c           	movi.n	a13, 1
     d13:	20c162        	addi	a6, a1, 32
     d16:	fcd381        	l32r	a8, 64 (1b4 <fix_fft5_stage>)
     d19:	5ff9a4        	ae_sp24x2f.xu	aep7, a9, a10
     d1c:	24c1b2        	addi	a11, a1, 36
     d1f:	11dd50        	slli	a13, a13, 11
     d22:	07cd           	mov.n	a12, a7
     d24:	06ad           	mov.n	a10, a6
     d26:	0008e0        	callx8	a8
     d29:	a05550        	addx4	a5, a5, a5
     d2c:	1155e0        	slli	a5, a5, 2
     d2f:	028d           	mov.n	a8, a2
     d31:	5d8854        	ae_lp24x2f.xu	aep0, a8, a5
     d34:	090c           	movi.n	a9, 0
     d36:	075d           	mov.n	a5, a7
     d38:	5dc834        	ae_lp24x2f.xu	aep4, a8, a3
     d3b:	5f8794        	ae_sp24x2f.xu	aep0, a7, a9
     d3e:	8f0c           	movi.n	a15, 8
     d40:	5dd844        	ae_lp24x2f.xu	aep5, a8, a4
     d43:	5fc7f4        	ae_sp24x2f.xu	aep4, a7, a15
     d46:	5de834        	ae_lp24x2f.xu	aep6, a8, a3
     d49:	5fd7f4        	ae_sp24x2f.xu	aep5, a7, a15
     d4c:	1d0c           	movi.n	a13, 1
     d4e:	fcc531        	l32r	a3, 64 (1b4 <fix_fft5_stage>)
     d51:	54c1b2        	addi	a11, a1, 84
     d54:	5fe7f4        	ae_sp24x2f.xu	aep6, a7, a15
     d57:	5df844        	ae_lp24x2f.xu	aep7, a8, a4
     d5a:	05ad           	mov.n	a10, a5
     d5c:	05cd           	mov.n	a12, a5
     d5e:	11dd50        	slli	a13, a13, 11
     d61:	5ff7f4        	ae_sp24x2f.xu	aep7, a7, a15
     d64:	0003e0        	callx8	a3
     d67:	605604        	ae_lq32f.iu	aeq1, a6, 0
     d6a:	60d504        	ae_lq32f.iu	aeq3, a5, 0
     d6d:	faee3d161f 	{ ae_lq32f.iu	aeq0, a6, 4; ae_addq56	aeq2, aeq1, aeq3 }
     d72:	f9aefa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_subq56	aeq1, aeq1, aeq3 }
     d77:	609514        	ae_lq32f.iu	aeq2, a5, 4
     d7a:	f9e23f14ef 	{ ae_trunca32q48	a4, aeq1; ae_addq56	aeq1, aeq0, aeq2 }
     d7f:	61c124        	ae_lq56.i	aeq3, a1, 16
     d82:	fd047a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_movq56	aeq1, aeq0 }
     d87:	faaaff33ef 	{ ae_trunca32q48	a3, aeq3; ae_subq56	aeq2, aeq1, aeq2 }
     d8c:	614124        	ae_lq56.i	aeq1, a1, 16
     d8f:	60d614        	ae_lq32f.iu	aeq3, a6, 4
     d92:	601514        	ae_lq32f.iu	aeq0, a5, 4
     d95:	f97a3f18ef 	{ ae_trunca32q48	a8, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
     d9a:	f83aff29ef 	{ ae_trunca32q48	a9, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
     d9f:	631124        	ae_sq56s.i	aeq1, a1, 16
     da2:	609614        	ae_lq32f.iu	aeq2, a6, 4
     da5:	605514        	ae_lq32f.iu	aeq1, a5, 4
     da8:	61c124        	ae_lq56.i	aeq3, a1, 16
     dab:	f8763f0bef 	{ ae_trunca32q48	a11, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
     db0:	f936ff3aef 	{ ae_trunca32q48	a10, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
     db5:	630124        	ae_sq56s.i	aeq0, a1, 16
     db8:	60d614        	ae_lq32f.iu	aeq3, a6, 4
     dbb:	601514        	ae_lq32f.iu	aeq0, a5, 4
     dbe:	618124        	ae_lq56.i	aeq2, a1, 16
     dc1:	f97a3f1def 	{ ae_trunca32q48	a13, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
     dc6:	f83aff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
     dcb:	631124        	ae_sq56s.i	aeq1, a1, 16
     dce:	7178           	l32i.n	a7, a1, 28
     dd0:	609614        	ae_lq32f.iu	aeq2, a6, 4
     dd3:	605514        	ae_lq32f.iu	aeq1, a5, 4
     dd6:	61c124        	ae_lq56.i	aeq3, a1, 16
     dd9:	f8763f0fef 	{ ae_trunca32q48	a15, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
     dde:	f936ff3eef 	{ ae_trunca32q48	a14, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
     de3:	630124        	ae_sq56s.i	aeq0, a1, 16
     de6:	60d614        	ae_lq32f.iu	aeq3, a6, 4
     de9:	601514        	ae_lq32f.iu	aeq0, a5, 4
     dec:	0239           	s32i.n	a3, a2, 0
     dee:	a249           	s32i.n	a4, a2, 40
     df0:	0789           	s32i.n	a8, a7, 0
     df2:	f97a3f18ef 	{ ae_trunca32q48	a8, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
     df7:	f83afdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq3, aeq0 }
     dfc:	631124        	ae_sq56s.i	aeq1, a1, 16
     dff:	36a404        	ae_trunca32q48	a4, aeq2
     e02:	609614        	ae_lq32f.iu	aeq2, a6, 4
     e05:	61c124        	ae_lq56.i	aeq3, a1, 16
     e08:	a799           	s32i.n	a9, a7, 40
     e0a:	36b904        	ae_trunca32q48	a9, aeq3
     e0d:	60d614        	ae_lq32f.iu	aeq3, a6, 4
     e10:	42a9           	s32i.n	a10, a2, 16
     e12:	fc147f0aef 	{ ae_trunca32q48	a10, aeq0; ae_movq56	aeq0, aeq2 }
     e17:	605514        	ae_lq32f.iu	aeq1, a5, 4
     e1a:	fb763a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_addq56	aeq3, aeq2, aeq1 }
     e1f:	f926fd551f 	{ ae_lq32f.iu	aeq2, a5, 4; ae_subq56	aeq1, aeq0, aeq1 }
     e24:	610124        	ae_lq56.i	aeq0, a1, 16
     e27:	e2b9           	s32i.n	a11, a2, 56
     e29:	47c9           	s32i.n	a12, a7, 16
     e2b:	36bb04        	ae_trunca32q48	a11, aeq3
     e2e:	f9e23f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq1, aeq0, aeq2 }
     e33:	f8a2fd761f 	{ ae_lq32f.iu	aeq3, a6, 4; ae_subq56	aeq0, aeq0, aeq2 }
     e38:	369604        	ae_trunca32q48	a6, aeq1
     e3b:	605514        	ae_lq32f.iu	aeq1, a5, 4
     e3e:	fa7e14e7df 	{ s32i.n	a13, a7, 56; ae_addq56	aeq2, aeq3, aeq1 }
     e43:	82e9           	s32i.n	a14, a2, 32
     e45:	1262f2        	s32i	a15, a2, 72
     e48:	f93eff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq1, aeq3, aeq1 }
     e4d:	36ae04        	ae_trunca32q48	a14, aeq2
     e50:	369f04        	ae_trunca32q48	a15, aeq1
     e53:	8749           	s32i.n	a4, a7, 32
     e55:	126782        	s32i	a8, a7, 72
     e58:	c299           	s32i.n	a9, a2, 48
     e5a:	22a9           	s32i.n	a10, a2, 8
     e5c:	c7b9           	s32i.n	a11, a7, 48
     e5e:	27c9           	s32i.n	a12, a7, 8
     e60:	106262        	s32i	a6, a2, 64
     e63:	62d9           	s32i.n	a13, a2, 24
     e65:	1067e2        	s32i	a14, a7, 64
     e68:	67f9           	s32i.n	a15, a7, 24
     e6a:	f01d           	retw.n

00000e6c <fix_fft15>:
     e6c:	016136        	entry	a1, 176
     e6f:	608264        	ae_lq32f.i	aeq2, a2, 24
     e72:	60c364        	ae_lq32f.i	aeq3, a3, 24
     e75:	20c262        	addi	a6, a2, 32
     e78:	20c352        	addi	a5, a3, 32
     e7b:	622164        	ae_sq32f.i	aeq2, a1, 24
     e7e:	623174        	ae_sq32f.i	aeq3, a1, 28
     e81:	10c1c2        	addi	a12, a1, 16
     e84:	608644        	ae_lq32f.i	aeq2, a6, 16
     e87:	60c544        	ae_lq32f.i	aeq3, a5, 16
     e8a:	40c2a2        	addi	a10, a2, 64
     e8d:	40c3b2        	addi	a11, a3, 64
     e90:	622c44        	ae_sq32f.i	aeq2, a12, 16
     e93:	608a24        	ae_lq32f.i	aeq2, a10, 8
     e96:	623c54        	ae_sq32f.i	aeq3, a12, 20
     e99:	60cb24        	ae_lq32f.i	aeq3, a11, 8
     e9c:	60c272        	addi	a7, a2, 96
     e9f:	60c382        	addi	a8, a3, 96
     ea2:	600204        	ae_lq32f.i	aeq0, a2, 0
     ea5:	604304        	ae_lq32f.i	aeq1, a3, 0
     ea8:	622c64        	ae_sq32f.i	aeq2, a12, 24
     eab:	623c74        	ae_sq32f.i	aeq3, a12, 28
     eae:	30c192        	addi	a9, a1, 48
     eb1:	608704        	ae_lq32f.i	aeq2, a7, 0
     eb4:	60c804        	ae_lq32f.i	aeq3, a8, 0
     eb7:	620c04        	ae_sq32f.i	aeq0, a12, 0
     eba:	621c14        	ae_sq32f.i	aeq1, a12, 4
     ebd:	622904        	ae_sq32f.i	aeq2, a9, 0
     ec0:	623914        	ae_sq32f.i	aeq3, a9, 4
     ec3:	608624        	ae_lq32f.i	aeq2, a6, 8
     ec6:	60c524        	ae_lq32f.i	aeq3, a5, 8
     ec9:	622924        	ae_sq32f.i	aeq2, a9, 8
     ecc:	608a04        	ae_lq32f.i	aeq2, a10, 0
     ecf:	623934        	ae_sq32f.i	aeq3, a9, 12
     ed2:	60cb04        	ae_lq32f.i	aeq3, a11, 0
     ed5:	622944        	ae_sq32f.i	aeq2, a9, 16
     ed8:	608a64        	ae_lq32f.i	aeq2, a10, 24
     edb:	623954        	ae_sq32f.i	aeq3, a9, 20
     ede:	60cb64        	ae_lq32f.i	aeq3, a11, 24
     ee1:	622964        	ae_sq32f.i	aeq2, a9, 24
     ee4:	608744        	ae_lq32f.i	aeq2, a7, 16
     ee7:	623974        	ae_sq32f.i	aeq3, a9, 28
     eea:	38c1d2        	addi	a13, a1, 56
     eed:	60c844        	ae_lq32f.i	aeq3, a8, 16
     ef0:	622d64        	ae_sq32f.i	aeq2, a13, 24
     ef3:	623d74        	ae_sq32f.i	aeq3, a13, 28
     ef6:	60ca44        	ae_lq32f.i	aeq3, a10, 16
     ef9:	58c1f2        	addi	a15, a1, 88
     efc:	608344        	ae_lq32f.i	aeq2, a3, 16
     eff:	622f14        	ae_sq32f.i	aeq2, a15, 4
     f02:	604244        	ae_lq32f.i	aeq1, a2, 16
     f05:	623f24        	ae_sq32f.i	aeq3, a15, 8
     f08:	608b44        	ae_lq32f.i	aeq2, a11, 16
     f0b:	60c724        	ae_lq32f.i	aeq3, a7, 8
     f0e:	621f04        	ae_sq32f.i	aeq1, a15, 0
     f11:	622f34        	ae_sq32f.i	aeq2, a15, 12
     f14:	623f44        	ae_sq32f.i	aeq3, a15, 16
     f17:	60c324        	ae_lq32f.i	aeq3, a3, 8
     f1a:	608824        	ae_lq32f.i	aeq2, a8, 8
     f1d:	600224        	ae_lq32f.i	aeq0, a2, 8
     f20:	622f54        	ae_sq32f.i	aeq2, a15, 20
     f23:	608604        	ae_lq32f.i	aeq2, a6, 0
     f26:	623f74        	ae_sq32f.i	aeq3, a15, 28
     f29:	60c1e2        	addi	a14, a1, 96
     f2c:	60c504        	ae_lq32f.i	aeq3, a5, 0
     f2f:	01d1f2        	addmi	a15, a1, 0x100
     f32:	622e64        	ae_sq32f.i	aeq2, a14, 24
     f35:	623e74        	ae_sq32f.i	aeq3, a14, 28
     f38:	620e44        	ae_sq32f.i	aeq0, a14, 16
     f3b:	1e0c           	movi.n	a14, 1
     f3d:	fc5031        	l32r	a3, 80 (8a8 <fix_fft15_stage>)
     f40:	80cf92        	addi	a9, a15, -128
     f43:	608664        	ae_lq32f.i	aeq2, a6, 24
     f46:	60c564        	ae_lq32f.i	aeq3, a5, 24
     f49:	11ee50        	slli	a14, a14, 11
     f4c:	02ad           	mov.n	a10, a2
     f4e:	04dd           	mov.n	a13, a4
     f50:	622904        	ae_sq32f.i	aeq2, a9, 0
     f53:	623914        	ae_sq32f.i	aeq3, a9, 4
     f56:	0003e0        	callx8	a3
     f59:	f01d           	retw.n

00000f5b <fix_fft15+0xef>:
	...

00000f5c <fix_fft20>:
     f5c:	030136        	entry	a1, 0x180
     f5f:	04ad           	mov.n	a10, a4
     f61:	070c           	movi.n	a7, 0
     f63:	025d           	mov.n	a5, a2
     f65:	1194a0        	slli	a9, a4, 6
     f68:	5d8574        	ae_lp24x2f.xu	aep0, a5, a7
     f6b:	1164c0        	slli	a6, a4, 4
     f6e:	01d1f2        	addmi	a15, a1, 0x100
     f71:	266162        	s32i	a6, a1, 152
     f74:	606060        	neg	a6, a6
     f77:	5dc594        	ae_lp24x2f.xu	aep4, a5, a9
     f7a:	30cf42        	addi	a4, a15, 48
     f7d:	5dd564        	ae_lp24x2f.xu	aep5, a5, a6
     f80:	048d           	mov.n	a8, a4
     f82:	5de564        	ae_lp24x2f.xu	aep6, a5, a6
     f85:	5df564        	ae_lp24x2f.xu	aep7, a5, a6
     f88:	5f8874        	ae_sp24x2f.xu	aep0, a8, a7
     f8b:	830c           	movi.n	a3, 8
     f8d:	5fc834        	ae_sp24x2f.xu	aep4, a8, a3
     f90:	115ae0        	slli	a5, a10, 2
     f93:	5fd834        	ae_sp24x2f.xu	aep5, a8, a3
     f96:	01d1b2        	addmi	a11, a1, 0x100
     f99:	1d0c           	movi.n	a13, 1
     f9b:	276152        	s32i	a5, a1, 156
     f9e:	fc3151        	l32r	a5, 64 (1b4 <fix_fft5_stage>)
     fa1:	5fe834        	ae_sp24x2f.xu	aep6, a8, a3
     fa4:	bb4b           	addi.n	a11, a11, 4
     fa6:	0a7d           	mov.n	a7, a10
     fa8:	1f61a2        	s32i	a10, a1, 124
     fab:	01d1a2        	addmi	a10, a1, 0x100
     fae:	11dd50        	slli	a13, a13, 11
     fb1:	04cd           	mov.n	a12, a4
     fb3:	1e6192        	s32i	a9, a1, 120
     fb6:	5ff834        	ae_sp24x2f.xu	aep7, a8, a3
     fb9:	2261a2        	s32i	a10, a1, 136
     fbc:	0005e0        	callx8	a5
     fbf:	a05770        	addx4	a5, a7, a7
     fc2:	1195e0        	slli	a9, a5, 2
     fc5:	028d           	mov.n	a8, a2
     fc7:	1e2172        	l32i	a7, a1, 120
     fca:	5d8894        	ae_lp24x2f.xu	aep0, a8, a9
     fcd:	5dc864        	ae_lp24x2f.xu	aep4, a8, a6
     fd0:	5dd874        	ae_lp24x2f.xu	aep5, a8, a7
     fd3:	04ed           	mov.n	a14, a4
     fd5:	0f0c           	movi.n	a15, 0
     fd7:	5f8ef4        	ae_sp24x2f.xu	aep0, a14, a15
     fda:	5de864        	ae_lp24x2f.xu	aep6, a8, a6
     fdd:	5fce34        	ae_sp24x2f.xu	aep4, a14, a3
     fe0:	5df864        	ae_lp24x2f.xu	aep7, a8, a6
     fe3:	5fde34        	ae_sp24x2f.xu	aep5, a14, a3
     fe6:	01d1b2        	addmi	a11, a1, 0x100
     fe9:	01d1a2        	addmi	a10, a1, 0x100
     fec:	1d0c           	movi.n	a13, 1
     fee:	fc1d81        	l32r	a8, 64 (1b4 <fix_fft5_stage>)
     ff1:	5fee34        	ae_sp24x2f.xu	aep6, a14, a3
     ff4:	d0caa2        	addi	a10, a10, -48
     ff7:	d4cbb2        	addi	a11, a11, -44
     ffa:	04cd           	mov.n	a12, a4
     ffc:	11dd50        	slli	a13, a13, 11
     fff:	256192        	s32i	a9, a1, 148
    1002:	5ffe34        	ae_sp24x2f.xu	aep7, a14, a3
    1005:	2061a2        	s32i	a10, a1, 128
    1008:	0008e0        	callx8	a8
    100b:	1185d0        	slli	a8, a5, 3
    100e:	02ed           	mov.n	a14, a2
    1010:	5d8e84        	ae_lp24x2f.xu	aep0, a14, a8
    1013:	04fd           	mov.n	a15, a4
    1015:	090c           	movi.n	a9, 0
    1017:	5dce64        	ae_lp24x2f.xu	aep4, a14, a6
    101a:	5f8f94        	ae_sp24x2f.xu	aep0, a15, a9
    101d:	5dde64        	ae_lp24x2f.xu	aep5, a14, a6
    1020:	5fcf34        	ae_sp24x2f.xu	aep4, a15, a3
    1023:	01d152        	addmi	a5, a1, 0x100
    1026:	5dee74        	ae_lp24x2f.xu	aep6, a14, a7
    1029:	5fdf34        	ae_sp24x2f.xu	aep5, a15, a3
    102c:	01d1b2        	addmi	a11, a1, 0x100
    102f:	1d0c           	movi.n	a13, 1
    1031:	a0c552        	addi	a5, a5, -96
    1034:	fc0c71        	l32r	a7, 64 (1b4 <fix_fft5_stage>)
    1037:	5fef34        	ae_sp24x2f.xu	aep6, a15, a3
    103a:	5dfe64        	ae_lp24x2f.xu	aep7, a14, a6
    103d:	a4cbb2        	addi	a11, a11, -92
    1040:	04cd           	mov.n	a12, a4
    1042:	11dd50        	slli	a13, a13, 11
    1045:	05ad           	mov.n	a10, a5
    1047:	246182        	s32i	a8, a1, 144
    104a:	5fff34        	ae_sp24x2f.xu	aep7, a15, a3
    104d:	0007e0        	callx8	a7
    1050:	1f21b2        	l32i	a11, a1, 124
    1053:	c83c           	movi.n	a8, 60
    1055:	07ed           	mov.n	a14, a7
    1057:	d17b80        	mul16s	a7, a11, a8
    105a:	02cd           	mov.n	a12, a2
    105c:	5d8c74        	ae_lp24x2f.xu	aep0, a12, a7
    105f:	5dcc64        	ae_lp24x2f.xu	aep4, a12, a6
    1062:	049d           	mov.n	a9, a4
    1064:	0d0c           	movi.n	a13, 0
    1066:	1e21f2        	l32i	a15, a1, 120
    1069:	5f89d4        	ae_sp24x2f.xu	aep0, a9, a13
    106c:	5ddc64        	ae_lp24x2f.xu	aep5, a12, a6
    106f:	5fc934        	ae_sp24x2f.xu	aep4, a9, a3
    1072:	5dec64        	ae_lp24x2f.xu	aep6, a12, a6
    1075:	5fd934        	ae_sp24x2f.xu	aep5, a9, a3
    1078:	01d1b2        	addmi	a11, a1, 0x100
    107b:	5dfcf4        	ae_lp24x2f.xu	aep7, a12, a15
    107e:	1d0c           	movi.n	a13, 1
    1080:	5fe934        	ae_sp24x2f.xu	aep6, a9, a3
    1083:	34cbb2        	addi	a11, a11, 52
    1086:	04ad           	mov.n	a10, a4
    1088:	04cd           	mov.n	a12, a4
    108a:	11dd50        	slli	a13, a13, 11
    108d:	236172        	s32i	a7, a1, 140
    1090:	5ff934        	ae_sp24x2f.xu	aep7, a9, a3
    1093:	000ee0        	callx8	a14
    1096:	222172        	l32i	a7, a1, 136
    1099:	202132        	l32i	a3, a1, 128
    109c:	1f21f2        	l32i	a15, a1, 124
    109f:	5c2704        	ae_lp24x2f.i	aep2, a7, 0
    10a2:	5c5504        	ae_lp24x2f.i	aep5, a5, 0
    10a5:	dba9004c6f 	{ movi	a6, 76; ae_addsp24s	aep6, aep2, aep5 }
    10aa:	ddaaaf330f 	{ ae_lp24x2f.i	aep3, a3, 0; ae_subsp24s	aep2, aep2, aep5 }
    10af:	5c4404        	ae_lp24x2f.i	aep4, a4, 0
    10b2:	db8d37613f 	{ ae_sp24x2s.i	aep6, a1, 24; ae_addsp24s	aep6, aep3, aep4 }
    10b7:	de8e8781ce 	{ addi	a12, a1, 120; ae_subsp24s	aep4, aep3, aep4 }
    10bc:	d16f60        	mul16s	a6, a15, a6
    10bf:	b08ff0        	addx8	a8, a15, a15
    10c2:	5c0714        	ae_lp24x2f.i	aep0, a7, 8
    10c5:	5c1514        	ae_lp24x2f.i	aep1, a5, 8
    10c8:	5c7314        	ae_lp24x2f.i	aep7, a3, 8
    10cb:	5c5414        	ae_lp24x2f.i	aep5, a4, 8
    10ce:	db2137612f 	{ ae_sp24x2s.i	aep6, a1, 16; ae_addsp24s	aep6, aep0, aep1 }
    10d3:	216162        	s32i	a6, a1, 132
    10d6:	d9bd774cdf 	{ ae_sp24x2s.i	aep4, a12, -24; ae_addsp24s	aep3, aep7, aep5 }
    10db:	debeb72cff 	{ ae_sp24x2s.i	aep2, a12, -8; ae_subsp24s	aep4, aep7, aep5 }
    10e0:	dc22b76caf 	{ ae_sp24x2s.i	aep6, a12, -48; ae_subsp24s	aep0, aep0, aep1 }
    10e5:	1168e0        	slli	a6, a8, 2
    10e8:	560cb4        	ae_sp24x2s.i	aep0, a12, -40
    10eb:	5c0724        	ae_lp24x2f.i	aep0, a7, 16
    10ee:	5c5524        	ae_lp24x2f.i	aep5, a5, 16
    10f1:	dba177314f 	{ ae_sp24x2s.i	aep3, a1, 32; ae_addsp24s	aep7, aep0, aep5 }
    10f6:	dca2b7416f 	{ ae_sp24x2s.i	aep4, a1, 48; ae_subsp24s	aep0, aep0, aep5 }
    10fb:	5c6324        	ae_lp24x2f.i	aep6, a3, 16
    10fe:	3169           	s32i.n	a6, a1, 12
    1100:	5c3424        	ae_lp24x2f.i	aep3, a4, 16
    1103:	dc7ab70ccf 	{ ae_sp24x2s.i	aep0, a12, -32; ae_subsp24s	aep0, aep6, aep3 }
    1108:	5c4734        	ae_lp24x2f.i	aep4, a7, 24
    110b:	5c5534        	ae_lp24x2f.i	aep5, a5, 24
    110e:	db79777c9f 	{ ae_sp24x2s.i	aep7, a12, -56; ae_addsp24s	aep7, aep6, aep3 }
    1113:	dcb2b7017f 	{ ae_sp24x2s.i	aep0, a1, 56; ae_subsp24s	aep0, aep4, aep5 }
    1118:	dbb12f233f 	{ ae_lp24x2f.i	aep2, a3, 24; ae_addsp24s	aep6, aep4, aep5 }
    111d:	5c3434        	ae_lp24x2f.i	aep3, a4, 24
    1120:	dc6ab70cef 	{ ae_sp24x2s.i	aep0, a12, -16; ae_subsp24s	aep0, aep2, aep3 }
    1125:	da692f174f 	{ ae_lp24x2f.i	aep1, a7, 32; ae_addsp24s	aep4, aep2, aep3 }
    112a:	542134        	ae_lp24x2.i	aep2, a1, 24
    112d:	543124        	ae_lp24x2.i	aep3, a1, 16
    1130:	da6972417e 	{ l32i	a7, a1, 144; ae_addsp24s	aep5, aep2, aep3 }
    1135:	060c           	movi.n	a6, 0
    1137:	dd6ab7015f 	{ ae_sp24x2s.i	aep0, a1, 40; ae_subsp24s	aep2, aep2, aep3 }
    113c:	5f5264        	ae_sp24x2f.x	aep5, a2, a6
    113f:	5c0544        	ae_lp24x2f.i	aep0, a5, 32
    1142:	da0570316e 	{ l32i	a6, a1, 12; ae_addsp24s	aep5, aep1, aep0 }
    1147:	dc06a9227f 	{ ae_sp24x2f.x	aep2, a2, a7; ae_subsp24s	aep0, aep1, aep0 }
    114c:	543cd4        	ae_lp24x2.i	aep3, a12, -24
    114f:	fe7877512f 	{ ae_sp24x2s.i	aep5, a1, 16; ae_negsp24s	aep5, aep3 }
    1154:	dc75f2315e 	{ l32i	a5, a1, 140; ae_selp24.lh	aep1, aep5, aep3 }
    1159:	560134        	ae_sp24x2s.i	aep0, a1, 24
    115c:	540cf4        	ae_lp24x2.i	aep0, a12, -8
    115f:	da216f334f 	{ ae_lp24x2f.i	aep3, a3, 32; ae_addsp24s	aep5, aep0, aep1 }
    1164:	dc22b2513e 	{ l32i	a3, a1, 148; ae_subsp24s	aep0, aep0, aep1 }
    1169:	5c2444        	ae_lp24x2f.i	aep2, a4, 32
    116c:	da4d69525f 	{ ae_sp24x2f.x	aep5, a2, a5; ae_addsp24s	aep5, aep3, aep2 }
    1171:	dc4ef2615e 	{ l32i	a5, a1, 152; ae_subsp24s	aep1, aep3, aep2 }
    1176:	4e3c           	movi.n	a14, 52
    1178:	f0aff0        	subx8	a10, a15, a15
    117b:	542ca4        	ae_lp24x2.i	aep2, a12, -48
    117e:	543144        	ae_lp24x2.i	aep3, a1, 32
    1181:	d1bfe0        	mul16s	a11, a15, a14
    1184:	d86929023f 	{ ae_sp24x2f.x	aep0, a2, a3; ae_addsp24s	aep0, aep2, aep3 }
    1189:	dd6ab0316f 	{ ae_lp24x2.i	aep3, a1, 48; ae_subsp24s	aep2, aep2, aep3 }
    118e:	11ead0        	slli	a14, a10, 3
    1191:	fc7829025f 	{ ae_sp24x2f.x	aep0, a2, a5; ae_negsp24s	aep0, aep3 }
    1196:	dc61a922ef 	{ ae_sp24x2f.x	aep2, a2, a14; ae_selp24.lh	aep0, aep0, aep3 }
    119b:	2121e2        	l32i	a14, a1, 132
    119e:	543cb4        	ae_lp24x2.i	aep3, a12, -40
    11a1:	d90d07817e 	{ addi	a7, a1, 120; ae_addsp24s	aep2, aep3, aep0 }
    11a6:	dc0eb03c9f 	{ ae_lp24x2.i	aep3, a12, -56; ae_subsp24s	aep0, aep3, aep0 }
    11ab:	d9ed2922ef 	{ ae_sp24x2f.x	aep2, a2, a14; ae_addsp24s	aep2, aep3, aep7 }
    11b0:	11cfb0        	slli	a12, a15, 5
    11b3:	dfeee9026f 	{ ae_sp24x2f.x	aep0, a2, a6; ae_subsp24s	aep7, aep3, aep7 }
    11b8:	d8992922cf 	{ ae_sp24x2f.x	aep2, a2, a12; ae_addsp24s	aep0, aep6, aep4 }
    11bd:	de9ab0217f 	{ ae_lp24x2.i	aep2, a1, 56; ae_subsp24s	aep4, aep6, aep4 }
    11c2:	1198d0        	slli	a9, a8, 3
    11c5:	ff58118fff 	{ addx2	a8, a15, a15; ae_negsp24s	aep6, aep2 }
    11ca:	dd59a9729f 	{ ae_sp24x2f.x	aep7, a2, a9; ae_selp24.lh	aep2, aep6, aep2 }
    11cf:	fd387067cf 	{ ae_lp24x2.i	aep6, a7, -32; ae_negsp24s	aep3, aep1 }
    11d4:	119ae0        	slli	a9, a10, 2
    11d7:	db5971e1ae 	{ l32i	a10, a1, 120; ae_addsp24s	aep7, aep6, aep2 }
    11dc:	11d8e0        	slli	a13, a8, 2
    11df:	dd5ab0615f 	{ ae_lp24x2.i	aep6, a1, 40; ae_subsp24s	aep2, aep6, aep2 }
    11e4:	ffd86972df 	{ ae_sp24x2f.x	aep7, a2, a13; ae_negsp24s	aep7, aep6 }
    11e9:	cc2c           	movi.n	a12, 44
    11eb:	114fd0        	slli	a4, a15, 3
    11ee:	1168c0        	slli	a6, a8, 4
    11f1:	dfdda922bf 	{ ae_sp24x2f.x	aep2, a2, a11; ae_selp24.lh	aep6, aep7, aep6 }
    11f6:	dc2da9026f 	{ ae_sp24x2f.x	aep0, a2, a6; ae_selp24.lh	aep0, aep3, aep1 }
    11fb:	5f4244        	ae_sp24x2f.x	aep4, a2, a4
    11fe:	5447e4        	ae_lp24x2.i	aep4, a7, -16
    1201:	a0bfa0        	addx4	a11, a15, a10
    1204:	d1efc0        	mul16s	a14, a15, a12
    1207:	dbd17271fe 	{ l32i	a15, a1, 156; ae_addsp24s	aep7, aep4, aep6 }
    120c:	ddd2b0312f 	{ ae_lp24x2.i	aep3, a1, 16; ae_subsp24s	aep2, aep4, aep6 }
    1211:	daad30613f 	{ ae_lp24x2.i	aep6, a1, 24; ae_addsp24s	aep4, aep3, aep5 }
    1216:	db1969729f 	{ ae_sp24x2f.x	aep7, a2, a9; ae_addsp24s	aep7, aep6, aep0 }
    121b:	ddaea922bf 	{ ae_sp24x2f.x	aep2, a2, a11; ae_subsp24s	aep2, aep3, aep5 }
    1220:	11d8d0        	slli	a13, a8, 3
    1223:	dc1aa942af 	{ ae_sp24x2f.x	aep4, a2, a10; ae_subsp24s	aep0, aep6, aep0 }
    1228:	5f22d4        	ae_sp24x2f.x	aep2, a2, a13
    122b:	5f72e4        	ae_sp24x2f.x	aep7, a2, a14
    122e:	5f02f4        	ae_sp24x2f.x	aep0, a2, a15
    1231:	f01d           	retw.n

00001233 <fix_fft20+0x2d7>:
	...

00001234 <fix_fft30>:
    1234:	02a136        	entry	a1, 0x150
    1237:	047d           	mov.n	a7, a4
    1239:	01d1e2        	addmi	a14, a1, 0x100
    123c:	b0ce42        	addi	a4, a14, -80
    123f:	b09770        	addx8	a9, a7, a7
    1242:	d0af52        	movi	a5, -48
    1245:	0a0c           	movi.n	a10, 0
    1247:	02fd           	mov.n	a15, a2
    1249:	d1c750        	mul16s	a12, a7, a5
    124c:	1199d0        	slli	a9, a9, 3
    124f:	5d8fa4        	ae_lp24x2f.xu	aep0, a15, a10
    1252:	048d           	mov.n	a8, a4
    1254:	5d9f94        	ae_lp24x2f.xu	aep1, a15, a9
    1257:	860c           	movi.n	a6, 8
    1259:	5f88a4        	ae_sp24x2f.xu	aep0, a8, a10
    125c:	5dafc4        	ae_lp24x2f.xu	aep2, a15, a12
    125f:	5f9864        	ae_sp24x2f.xu	aep1, a8, a6
    1262:	5dbf94        	ae_lp24x2f.xu	aep3, a15, a9
    1265:	5fa864        	ae_sp24x2f.xu	aep2, a8, a6
    1268:	11b7b0        	slli	a11, a7, 5
    126b:	5dcfc4        	ae_lp24x2f.xu	aep4, a15, a12
    126e:	5fb864        	ae_sp24x2f.xu	aep3, a8, a6
    1271:	5ddfb4        	ae_lp24x2f.xu	aep5, a15, a11
    1274:	5fc864        	ae_sp24x2f.xu	aep4, a8, a6
    1277:	5defc4        	ae_lp24x2f.xu	aep6, a15, a12
    127a:	5fd864        	ae_sp24x2f.xu	aep5, a8, a6
    127d:	5dff94        	ae_lp24x2f.xu	aep7, a15, a9
    1280:	5fe864        	ae_sp24x2f.xu	aep6, a8, a6
    1283:	5d9fc4        	ae_lp24x2f.xu	aep1, a15, a12
    1286:	5ff864        	ae_sp24x2f.xu	aep7, a8, a6
    1289:	5dafc4        	ae_lp24x2f.xu	aep2, a15, a12
    128c:	5f9864        	ae_sp24x2f.xu	aep1, a8, a6
    128f:	5dbfb4        	ae_lp24x2f.xu	aep3, a15, a11
    1292:	5fa864        	ae_sp24x2f.xu	aep2, a8, a6
    1295:	5dcf94        	ae_lp24x2f.xu	aep4, a15, a9
    1298:	5fb864        	ae_sp24x2f.xu	aep3, a8, a6
    129b:	5ddfc4        	ae_lp24x2f.xu	aep5, a15, a12
    129e:	5fc864        	ae_sp24x2f.xu	aep4, a8, a6
    12a1:	5defc4        	ae_lp24x2f.xu	aep6, a15, a12
    12a4:	5fd864        	ae_sp24x2f.xu	aep5, a8, a6
    12a7:	5fe864        	ae_sp24x2f.xu	aep6, a8, a6
    12aa:	5dff94        	ae_lp24x2f.xu	aep7, a15, a9
    12ad:	5ff864        	ae_sp24x2f.xu	aep7, a8, a6
    12b0:	1e0c           	movi.n	a14, 1
    12b2:	30c152        	addi	a5, a1, 48
    12b5:	fb7281        	l32r	a8, 80 (8a8 <fix_fft15_stage>)
    12b8:	a1c9           	s32i.n	a12, a1, 40
    12ba:	11ee50        	slli	a14, a14, 11
    12bd:	05ad           	mov.n	a10, a5
    12bf:	04cd           	mov.n	a12, a4
    12c1:	07dd           	mov.n	a13, a7
    12c3:	b1b9           	s32i.n	a11, a1, 44
    12c5:	9199           	s32i.n	a9, a1, 36
    12c7:	0008e0        	callx8	a8
    12ca:	c93c           	movi.n	a9, 60
    12cc:	07ad           	mov.n	a10, a7
    12ce:	d17790        	mul16s	a7, a7, a9
    12d1:	029d           	mov.n	a9, a2
    12d3:	04ed           	mov.n	a14, a4
    12d5:	5d8974        	ae_lp24x2f.xu	aep0, a9, a7
    12d8:	0b0c           	movi.n	a11, 0
    12da:	5f8eb4        	ae_sp24x2f.xu	aep0, a14, a11
    12dd:	a1b8           	l32i.n	a11, a1, 40
    12df:	91c8           	l32i.n	a12, a1, 36
    12e1:	a8af82        	movi	a8, -88
    12e4:	5d99b4        	ae_lp24x2f.xu	aep1, a9, a11
    12e7:	5da9c4        	ae_lp24x2f.xu	aep2, a9, a12
    12ea:	5f9e64        	ae_sp24x2f.xu	aep1, a14, a6
    12ed:	5db9b4        	ae_lp24x2f.xu	aep3, a9, a11
    12f0:	5fae64        	ae_sp24x2f.xu	aep2, a14, a6
    12f3:	d18a80        	mul16s	a8, a10, a8
    12f6:	5dc9c4        	ae_lp24x2f.xu	aep4, a9, a12
    12f9:	5fbe64        	ae_sp24x2f.xu	aep3, a14, a6
    12fc:	5dd984        	ae_lp24x2f.xu	aep5, a9, a8
    12ff:	5fce64        	ae_sp24x2f.xu	aep4, a14, a6
    1302:	5de9c4        	ae_lp24x2f.xu	aep6, a9, a12
    1305:	5fde64        	ae_sp24x2f.xu	aep5, a14, a6
    1308:	5df9b4        	ae_lp24x2f.xu	aep7, a9, a11
    130b:	5fee64        	ae_sp24x2f.xu	aep6, a14, a6
    130e:	b1f8           	l32i.n	a15, a1, 44
    1310:	5d99c4        	ae_lp24x2f.xu	aep1, a9, a12
    1313:	5ffe64        	ae_sp24x2f.xu	aep7, a14, a6
    1316:	5da9b4        	ae_lp24x2f.xu	aep2, a9, a11
    1319:	5f9e64        	ae_sp24x2f.xu	aep1, a14, a6
    131c:	5db9f4        	ae_lp24x2f.xu	aep3, a9, a15
    131f:	5fae64        	ae_sp24x2f.xu	aep2, a14, a6
    1322:	5dc9b4        	ae_lp24x2f.xu	aep4, a9, a11
    1325:	5fbe64        	ae_sp24x2f.xu	aep3, a14, a6
    1328:	5dd9b4        	ae_lp24x2f.xu	aep5, a9, a11
    132b:	5fce64        	ae_sp24x2f.xu	aep4, a14, a6
    132e:	5de9c4        	ae_lp24x2f.xu	aep6, a9, a12
    1331:	5fde64        	ae_sp24x2f.xu	aep5, a14, a6
    1334:	5fee64        	ae_sp24x2f.xu	aep6, a14, a6
    1337:	5df9b4        	ae_lp24x2f.xu	aep7, a9, a11
    133a:	5ffe64        	ae_sp24x2f.xu	aep7, a14, a6
    133d:	1e0c           	movi.n	a14, 1
    133f:	fb5081        	l32r	a8, 80 (8a8 <fix_fft15_stage>)
    1342:	0add           	mov.n	a13, a10
    1344:	81a9           	s32i.n	a10, a1, 32
    1346:	04ad           	mov.n	a10, a4
    1348:	04cd           	mov.n	a12, a4
    134a:	11ee50        	slli	a14, a14, 11
    134d:	0008e0        	callx8	a8
    1350:	8188           	l32i.n	a8, a1, 32
    1352:	1a0c           	movi.n	a10, 1
    1354:	11aa20        	slli	a10, a10, 14
    1357:	fb0c           	movi.n	a11, 15
    1359:	300aa4        	ae_cvtp24a16x2.ll	aep0, a10, a10
    135c:	1188e0        	slli	a8, a8, 2
    135f:	190c           	movi.n	a9, 1
    1361:	0a4c           	movi.n	a10, 64
    1363:	5e8b76        	loop	a11, 13c5 <fix_fft30+0x191>
    1366:	05c8           	l32i.n	a12, a5, 0
    1368:	04d8           	l32i.n	a13, a4, 0
    136a:	15e8           	l32i.n	a14, a5, 4
    136c:	14f8           	l32i.n	a15, a4, 4
    136e:	41c9           	s32i.n	a12, a1, 16
    1370:	51d9           	s32i.n	a13, a1, 20
    1372:	61e9           	s32i.n	a14, a1, 24
    1374:	71f9           	s32i.n	a15, a1, 28
    1376:	10c1d2        	addi	a13, a1, 16
    1379:	0f0c           	movi.n	a15, 0
    137b:	5d9df4        	ae_lp24x2f.xu	aep1, a13, a15
    137e:	f0069efd6f 	{ ae_lp24x2f.xu	aep7, a13, a6; ae_mulzaafp24s.hh.ll	aeq0, aep1, aep0 }
    1383:	04c090        	extui	a12, a9, 0, 1
    1386:	f40450b27f 	{ add	a11, a2, a7; ae_mulzasfp24s.hh.ll	aeq1, aep1, aep0 }
    138b:	02ed           	mov.n	a14, a2
    138d:	93ebc0        	movnez	a14, a11, a12
    1390:	93b2c0        	movnez	a11, a2, a12
    1393:	f51c7f0fef 	{ ae_trunca32q48	a15, aeq0; ae_mulzasfp24s.hh.ll	aeq3, aep7, aep0 }
    1398:	0bf9           	s32i.n	a15, a11, 0
    139a:	f11ebf1def 	{ ae_trunca32q48	a13, aeq1; ae_mulzaafp24s.hh.ll	aeq2, aep7, aep0 }
    139f:	b37a           	add.n	a11, a3, a7
    13a1:	03fd           	mov.n	a15, a3
    13a3:	0ed9           	s32i.n	a13, a14, 0
    13a5:	93fbc0        	movnez	a15, a11, a12
    13a8:	93b3c0        	movnez	a11, a3, a12
    13ab:	36ad04        	ae_trunca32q48	a13, aeq2
    13ae:	36be04        	ae_trunca32q48	a14, aeq3
    13b1:	0bd9           	s32i.n	a13, a11, 0
    13b3:	0fe9           	s32i.n	a14, a15, 0
    13b5:	c8aff2        	movi	a15, -56
    13b8:	93fac0        	movnez	a15, a10, a12
    13bb:	55fa           	add.n	a5, a5, a15
    13bd:	44fa           	add.n	a4, a4, a15
    13bf:	991b           	addi.n	a9, a9, 1
    13c1:	338a           	add.n	a3, a3, a8
    13c3:	228a           	add.n	a2, a2, a8

000013c5 <fix_fft30+0x191>:
    13c5:	f01d           	retw.n

000013c7 <fix_fft30+0x193>:
	...

000013c8 <fix_fft40>:
    13c8:	034136        	entry	a1, 0x1a0
    13cb:	fb24d1        	l32r	a13, 5c (272c <RotVector_40_32>)
    13ce:	02bd           	mov.n	a11, a2
    13d0:	11e4e0        	slli	a14, a4, 2
    13d3:	0d78           	l32i.n	a7, a13, 0
    13d5:	8f0c           	movi.n	a15, 8
    13d7:	560c           	movi.n	a6, 5
    13d9:	2d61e2        	s32i	a14, a1, 180
    13dc:	1184b0        	slli	a8, a4, 5
    13df:	059d           	mov.n	a9, a5
    13e1:	03ad           	mov.n	a10, a3
    13e3:	266122        	s32i	a2, a1, 152

000013e6 <fix_fft40+0x1e>:
    13e6:	092d           	mov.n	a2, a9
    13e8:	0acd           	mov.n	a12, a10
    13ea:	20dbb0        	or	a13, a11, a11
    13ed:	0d8676        	loop	a6, 13fe <fix_fft40+0x36>
    13f0:	0de8           	l32i.n	a14, a13, 0
    13f2:	02e9           	s32i.n	a14, a2, 0
    13f4:	0ce8           	l32i.n	a14, a12, 0
    13f6:	12e9           	s32i.n	a14, a2, 4
    13f8:	dd8a           	add.n	a13, a13, a8
    13fa:	cc8a           	add.n	a12, a12, a8
    13fc:	228b           	addi.n	a2, a2, 8

000013fe <fix_fft40+0x36>:
    13fe:	2d2122        	l32i	a2, a1, 180
    1401:	ff0b           	addi.n	a15, a15, -1
    1403:	28c992        	addi	a9, a9, 40
    1406:	bb2a           	add.n	a11, a11, a2
    1408:	aa2a           	add.n	a10, a10, a2
    140a:	fd8f56        	bnez	a15, 13e6 <fix_fft40+0x1e>
    140d:	fb1d21        	l32r	a2, 84 (a40 <fix_fft5_8K>)
    1410:	276132        	s32i	a3, a1, 156
    1413:	830c           	movi.n	a3, 8
    1415:	056d           	mov.n	a6, a5

00001417 <fix_fft40+0x4f>:
    1417:	b64b           	addi.n	a11, a6, 4
    1419:	0c0c           	movi.n	a12, 0
    141b:	06ad           	mov.n	a10, a6
    141d:	0002e0        	callx8	a2
    1420:	330b           	addi.n	a3, a3, -1
    1422:	28c662        	addi	a6, a6, 40
    1425:	fee356        	bnez	a3, 1417 <fix_fft40+0x4f>
    1428:	a09440        	addx4	a9, a4, a4
    142b:	28c542        	addi	a4, a5, 40
    142e:	895d           	ae_sext16	a5, a9
    1430:	262192        	l32i	a9, a1, 152
    1433:	2721f2        	l32i	a15, a1, 156
    1436:	82a032        	movi	a3, 130
    1439:	fb1461        	l32r	a6, 8c (a57d8666 <_end+0xa57d5f12>)
    143c:	fb1581        	l32r	a8, 90 (a57d <_end+0x7e29>)
    143f:	301864        	ae_cvtp24a16x2.ll	aep1, a8, a6
    1442:	b0a590        	addx8	a10, a5, a9
    1445:	fb1021        	l32r	a2, 88 (5a82799a <_end+0x5a825246>)
    1448:	5ad332        	addmi	a3, a3, 0x5a00
    144b:	1165c0        	slli	a6, a5, 4
    144e:	90b550        	addx2	a11, a5, a5
    1451:	f0e550        	subx8	a14, a5, a5
    1454:	f8c7c2        	addi	a12, a7, -8
    1457:	300324        	ae_cvtp24a16x2.ll	aep0, a3, a2
    145a:	a075f0        	addx4	a7, a5, a15
    145d:	a08550        	addx4	a8, a5, a5
    1460:	b0d5f0        	addx8	a13, a5, a15
    1463:	3261a2        	s32i	a10, a1, 200
    1466:	a05590        	addx4	a5, a5, a9
    1469:	af6a           	add.n	a10, a15, a6
    146b:	112bd0        	slli	a2, a11, 3
    146e:	11bbe0        	slli	a11, a11, 2
    1471:	2a6152        	s32i	a5, a1, 168
    1474:	3161a2        	s32i	a10, a1, 196
    1477:	afba           	add.n	a10, a15, a11
    1479:	59ba           	add.n	a5, a9, a11
    147b:	bf2a           	add.n	a11, a15, a2
    147d:	1138e0        	slli	a3, a8, 2
    1480:	11eee0        	slli	a14, a14, 2
    1483:	336172        	s32i	a7, a1, 204
    1486:	796a           	add.n	a7, a9, a6
    1488:	8fea           	add.n	a8, a15, a14
    148a:	69ea           	add.n	a6, a9, a14
    148c:	ef3a           	add.n	a14, a15, a3
    148e:	2c61b2        	s32i	a11, a1, 176
    1491:	b92a           	add.n	a11, a9, a2
    1493:	393a           	add.n	a3, a9, a3
    1495:	01d192        	addmi	a9, a1, 0x100
    1498:	2e61a2        	s32i	a10, a1, 184
    149b:	286132        	s32i	a3, a1, 160
    149e:	60c932        	addi	a3, a9, 96
    14a1:	01d1a2        	addmi	a10, a1, 0x100
    14a4:	2b61e2        	s32i	a14, a1, 172
    14a7:	396132        	s32i	a3, a1, 228
    14aa:	20ca32        	addi	a3, a10, 32
    14ad:	01d1e2        	addmi	a14, a1, 0x100
    14b0:	306182        	s32i	a8, a1, 192
    14b3:	2f6162        	s32i	a6, a1, 188
    14b6:	296152        	s32i	a5, a1, 164
    14b9:	54c152        	addi	a5, a1, 84
    14bc:	58c162        	addi	a6, a1, 88
    14bf:	70c182        	addi	a8, a1, 112
    14c2:	386132        	s32i	a3, a1, 224
    14c5:	30ce32        	addi	a3, a14, 48
    14c8:	042d           	mov.n	a2, a4
    14ca:	346162        	s32i	a6, a1, 208
    14cd:	376182        	s32i	a8, a1, 220
    14d0:	356152        	s32i	a5, a1, 212
    14d3:	366132        	s32i	a3, a1, 216
    14d6:	540c           	movi.n	a4, 5
    14d8:	862c           	movi.n	a6, 40
    14da:	082c           	movi.n	a8, 32
    14dc:	011486        	j	1932 <fix_fft40+0x56a>

000014df <fix_fft40+0x117>:
	...

000014e0 <fix_fft40+0x118>:
    14e0:	0c3d           	mov.n	a3, a12
    14e2:	352152        	l32i	a5, a1, 212
    14e5:	44a304        	ae_lp16x2f.iu	aep2, a3, 0
    14e8:	7e0c           	movi.n	a14, 7
    14ea:	600204        	ae_lq32f.i	aeq0, a2, 0
    14ed:	604214        	ae_lq32f.i	aeq1, a2, 4
    14f0:	02fd           	mov.n	a15, a2
    14f2:	443314        	ae_lp16x2f.i	aep3, a3, 4
    14f5:	6d8e76        	loop	a14, 1566 <fix_fft40+0x19e>
    14f8:	03ba14        	ae_mulfq32sp16s.l	aeq3, aeq0, aep3
    14fb:	03b224        	ae_mulfq32sp16u.h	aeq2, aeq0, aep3
    14fe:	d56bfa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_mulfq32sp16u.h	aeq3, aeq1, aep2 }
    1503:	35a434        	ae_sraiq56	aeq2, aeq2, 16
    1506:	d5eb7a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_mulfq32sp16s.l	aeq3, aeq1, aep2 }
    150b:	632124        	ae_sq56s.i	aeq2, a1, 16
    150e:	633164        	ae_sq56s.i	aeq3, a1, 48
    1511:	61c124        	ae_lq56.i	aeq3, a1, 16
    1514:	618134        	ae_lq56.i	aeq2, a1, 24
    1517:	fbfa3dc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_addq56	aeq3, aeq3, aeq2 }
    151c:	633134        	ae_sq56s.i	aeq3, a1, 24
    151f:	61c144        	ae_lq56.i	aeq3, a1, 32
    1522:	35f434        	ae_sraiq56	aeq3, aeq3, 16
    1525:	01abc4        	ae_addq56	aeq2, aeq2, aeq3
    1528:	d56aba212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq2, aeq0, aep2 }
    152d:	03ba64        	ae_mulfq32sp16u.h	aeq3, aeq1, aep3
    1530:	d4ea3b248f 	{ ae_sraiq56	aeq2, aeq2, 16; ae_mulfq32sp16s.l	aeq0, aeq0, aep2 }
    1535:	d4ef7b34cf 	{ ae_sraiq56	aeq3, aeq3, 16; ae_mulfq32sp16s.l	aeq1, aeq1, aep3 }
    153a:	f8723dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq0, aeq2, aeq0 }
    153f:	f9ee3de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_addq56	aeq1, aeq1, aeq3 }
    1544:	fc645ba38f 	{ ae_lp16x2f.xu	aep2, a3, a8; ae_truncq32	aeq0, aeq0 }
    1549:	f8662d331f 	{ ae_lp16x2f.i	aep3, a3, 4; ae_addq56	aeq0, aeq0, aeq1 }
    154e:	fd747b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_truncq32	aeq1, aeq2 }
    1553:	fe7c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_truncq32	aeq2, aeq3 }
    1558:	f936fc0f6f 	{ ae_lq32f.xu	aeq0, a15, a6; ae_subq56	aeq1, aeq2, aeq1 }
    155d:	355074        	ae_sraiq56	aeq1, aeq1, 1
    1560:	625514        	ae_sq32f.iu	aeq1, a5, 4
    1563:	604f14        	ae_lq32f.i	aeq1, a15, 4

00001566 <fix_fft40+0x19e>:
    1566:	372142        	l32i	a4, a1, 220
    1569:	50c132        	addi	a3, a1, 80
    156c:	608324        	ae_lq32f.i	aeq2, a3, 8
    156f:	60c424        	ae_lq32f.i	aeq3, a4, 8
    1572:	600404        	ae_lq32f.i	aeq0, a4, 0
    1575:	fab6fa213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_subq56	aeq2, aeq2, aeq3 }
    157a:	01d1f2        	addmi	a15, a1, 0x100
    157d:	630154        	ae_sq56s.i	aeq0, a1, 40
    1580:	604434        	ae_lq32f.i	aeq1, a4, 12
    1583:	600334        	ae_lq32f.i	aeq0, a3, 12
    1586:	632174        	ae_sq56s.i	aeq2, a1, 56
    1589:	fb26fa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq3, aeq0, aeq1 }
    158e:	40cff2        	addi	a15, a15, 64
    1591:	631144        	ae_sq56s.i	aeq1, a1, 32
    1594:	630164        	ae_sq56s.i	aeq0, a1, 48
    1597:	614174        	ae_lq56.i	aeq1, a1, 56
    159a:	608304        	ae_lq32f.i	aeq2, a3, 0
    159d:	610154        	ae_lq56.i	aeq0, a1, 40
    15a0:	f972399f6f 	{ ae_sq32f.i	aeq1, a15, 24; ae_addq56	aeq1, aeq2, aeq0 }
    15a5:	f832fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq2, aeq0 }
    15aa:	621f04        	ae_sq32f.i	aeq1, a15, 0
    15ad:	604314        	ae_lq32f.i	aeq1, a3, 4
    15b0:	608414        	ae_lq32f.i	aeq2, a4, 4
    15b3:	fbea39bf7f 	{ ae_sq32f.i	aeq3, a15, 28; ae_addq56	aeq3, aeq1, aeq2 }
    15b8:	f9aafb002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_subq56	aeq1, aeq1, aeq2 }
    15bd:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    15c0:	620f24        	ae_sq32f.i	aeq0, a15, 8
    15c3:	623f14        	ae_sq32f.i	aeq3, a15, 4
    15c6:	3590b4        	ae_sraiq56	aeq2, aeq1, 2
    15c9:	61c124        	ae_lq56.i	aeq3, a1, 16
    15cc:	610134        	ae_lq56.i	aeq0, a1, 24
    15cf:	f9e63a215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_addq56	aeq1, aeq0, aeq3 }
    15d4:	61c144        	ae_lq56.i	aeq3, a1, 32
    15d7:	610164        	ae_lq56.i	aeq0, a1, 48
    15da:	fbe63d815f 	{ ae_lq56.i	aeq0, a1, 40; ae_addq56	aeq3, aeq0, aeq3 }
    15df:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    15e2:	620f34        	ae_sq32f.i	aeq0, a15, 12
    15e5:	608444        	ae_lq32f.i	aeq2, a4, 16
    15e8:	600344        	ae_lq32f.i	aeq0, a3, 16
    15eb:	fbe239bf5f 	{ ae_sq32f.i	aeq3, a15, 20; ae_addq56	aeq3, aeq0, aeq2 }
    15f0:	f8a2fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq0, aeq2 }
    15f5:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    15f8:	630144        	ae_sq56s.i	aeq0, a1, 32
    15fb:	392122        	l32i	a2, a1, 228
    15fe:	621f44        	ae_sq32f.i	aeq1, a15, 16
    1601:	633134        	ae_sq56s.i	aeq3, a1, 24
    1604:	604354        	ae_lq32f.i	aeq1, a3, 20
    1607:	608454        	ae_lq32f.i	aeq2, a4, 20
    160a:	f8ea3de14f 	{ ae_lq56.i	aeq3, a1, 32; ae_addq56	aeq0, aeq1, aeq2 }
    160f:	f9aafb30af 	{ ae_sraiq56	aeq2, aeq3, 2; ae_subq56	aeq1, aeq1, aeq2 }
    1614:	631124        	ae_sq56s.i	aeq1, a1, 16
    1617:	622224        	ae_sq32f.i	aeq2, a2, 8
    161a:	608374        	ae_lq32f.i	aeq2, a3, 28
    161d:	3540b4        	ae_sraiq56	aeq1, aeq0, 2
    1620:	610134        	ae_lq56.i	aeq0, a1, 24
    1623:	632134        	ae_sq56s.i	aeq2, a1, 24
    1626:	618124        	ae_lq56.i	aeq2, a1, 16
    1629:	620204        	ae_sq32f.i	aeq0, a2, 0
    162c:	3520b4        	ae_sraiq56	aeq0, aeq2, 2
    162f:	621214        	ae_sq32f.i	aeq1, a2, 4
    1632:	60c464        	ae_lq32f.i	aeq3, a4, 24
    1635:	604364        	ae_lq32f.i	aeq1, a3, 24
    1638:	fc1c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_movq56	aeq0, aeq3 }
    163d:	fbee3d447f 	{ ae_lq32f.i	aeq2, a4, 28; ae_addq56	aeq3, aeq1, aeq3 }
    1642:	f92afa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq1, aeq1, aeq0 }
    1647:	61c144        	ae_lq56.i	aeq3, a1, 32
    164a:	610134        	ae_lq56.i	aeq0, a1, 24
    164d:	fbe239b23f 	{ ae_sq32f.i	aeq3, a2, 12; ae_addq56	aeq3, aeq0, aeq2 }
    1652:	f8a2fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
    1657:	35a0b4        	ae_sraiq56	aeq2, aeq2, 2
    165a:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    165d:	622244        	ae_sq32f.i	aeq2, a2, 16
    1660:	620274        	ae_sq32f.i	aeq0, a2, 28
    1663:	621264        	ae_sq32f.i	aeq1, a2, 24
    1666:	623254        	ae_sq32f.i	aeq3, a2, 20
    1669:	600204        	ae_lq32f.i	aeq0, a2, 0
    166c:	604f04        	ae_lq32f.i	aeq1, a15, 0
    166f:	fb6a3d421f 	{ ae_lq32f.i	aeq2, a2, 4; ae_addq56	aeq3, aeq1, aeq0 }
    1674:	01d152        	addmi	a5, a1, 0x100
    1677:	f82af9b50f 	{ ae_sq32f.i	aeq3, a5, 0; ae_subq56	aeq0, aeq1, aeq0 }
    167c:	60cf14        	ae_lq32f.i	aeq3, a15, 4
    167f:	f8fa39854f 	{ ae_sq32f.i	aeq0, a5, 16; ae_addq56	aeq0, aeq3, aeq2 }
    1684:	fabaf3814e 	{ l32i	a4, a1, 224; ae_subq56	aeq2, aeq3, aeq2 }
    1689:	60c224        	ae_lq32f.i	aeq3, a2, 8
    168c:	620514        	ae_sq32f.i	aeq0, a5, 4
    168f:	604234        	ae_lq32f.i	aeq1, a2, 12
    1692:	600f24        	ae_lq32f.i	aeq0, a15, 8
    1695:	fb26fa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq3, aeq0, aeq1 }
    169a:	f96639a55f 	{ ae_sq32f.i	aeq2, a5, 20; ae_addq56	aeq1, aeq0, aeq1 }
    169f:	623404        	ae_sq32f.i	aeq3, a4, 0
    16a2:	600264        	ae_lq32f.i	aeq0, a2, 24
    16a5:	60cf64        	ae_lq32f.i	aeq3, a15, 24
    16a8:	f97a39942f 	{ ae_sq32f.i	aeq1, a4, 8; ae_addq56	aeq1, aeq3, aeq0 }
    16ad:	f83afb10af 	{ ae_sraiq56	aeq2, aeq1, 2; ae_subq56	aeq0, aeq3, aeq0 }
    16b2:	3500b4        	ae_sraiq56	aeq0, aeq0, 2
    16b5:	630134        	ae_sq56s.i	aeq0, a1, 24
    16b8:	604254        	ae_lq32f.i	aeq1, a2, 20
    16bb:	60c244        	ae_lq32f.i	aeq3, a2, 16
    16be:	631164        	ae_sq56s.i	aeq1, a1, 48
    16c1:	622f14        	ae_sq32f.i	aeq2, a15, 4
    16c4:	618134        	ae_lq56.i	aeq2, a1, 24
    16c7:	604f34        	ae_lq32f.i	aeq1, a15, 12
    16ca:	610124        	ae_lq56.i	aeq0, a1, 16
    16cd:	fa6a39af2f 	{ ae_sq32f.i	aeq2, a15, 8; ae_addq56	aeq2, aeq1, aeq0 }
    16d2:	f82afa213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_subq56	aeq0, aeq1, aeq0 }
    16d7:	630154        	ae_sq56s.i	aeq0, a1, 40
    16da:	614134        	ae_lq56.i	aeq1, a1, 24
    16dd:	608274        	ae_lq32f.i	aeq2, a2, 28
    16e0:	600f74        	ae_lq32f.i	aeq0, a15, 28
    16e3:	f9e239941f 	{ ae_sq32f.i	aeq1, a4, 4; ae_addq56	aeq1, aeq0, aeq2 }
    16e8:	f8a2fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
    16ed:	618124        	ae_lq56.i	aeq2, a1, 16
    16f0:	604f44        	ae_lq32f.i	aeq1, a15, 16
    16f3:	f8ee3a017f 	{ ae_sq56s.i	aeq0, a1, 56; ae_addq56	aeq0, aeq1, aeq3 }
    16f8:	f9aefb20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_subq56	aeq1, aeq1, aeq3 }
    16fd:	630134        	ae_sq56s.i	aeq0, a1, 24
    1700:	622f04        	ae_sq32f.i	aeq2, a15, 0
    1703:	600f54        	ae_lq32f.i	aeq0, a15, 20
    1706:	618164        	ae_lq56.i	aeq2, a1, 48
    1709:	fbe23a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_addq56	aeq3, aeq0, aeq2 }
    170e:	f832fa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq0, aeq2, aeq0 }
    1713:	630164        	ae_sq56s.i	aeq0, a1, 48
    1716:	61c174        	ae_lq56.i	aeq3, a1, 56
    1719:	604f04        	ae_lq32f.i	aeq1, a15, 0
    171c:	600f24        	ae_lq32f.i	aeq0, a15, 8
    171f:	fb6a3b30af 	{ ae_sraiq56	aeq2, aeq3, 2; ae_addq56	aeq3, aeq1, aeq0 }
    1724:	f82af9af3f 	{ ae_sq32f.i	aeq2, a15, 12; ae_subq56	aeq0, aeq1, aeq0 }
    1729:	fd84fa017f 	{ ae_sq56s.i	aeq0, a1, 56; ae_satq48s	aeq1, aeq3 }
    172e:	d4e3bd4f3f 	{ ae_lq32f.i	aeq2, a15, 12; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1733:	d4637d6f1f 	{ ae_lq32f.i	aeq3, a15, 4; ae_mulfq32sp16s.h	aeq1, aeq1, aep0 }
    1738:	6303e4        	ae_sq56s.i	aeq0, a3, -16
    173b:	610154        	ae_lq56.i	aeq0, a1, 40
    173e:	f8b6f9843f 	{ ae_sq32f.i	aeq0, a4, 12; ae_subq56	aeq0, aeq2, aeq3 }
    1743:	fafa3de3ef 	{ ae_lq56.i	aeq3, a3, -16; ae_addq56	aeq2, aeq3, aeq2 }
    1748:	fe80fa03ff 	{ ae_sq56s.i	aeq0, a3, -8; ae_satq48s	aeq2, aeq2 }
    174d:	353434        	ae_sraiq56	aeq0, aeq3, 16
    1750:	f86a3da17f 	{ ae_lq56.i	aeq1, a1, 56; ae_addq56	aeq0, aeq1, aeq0 }
    1755:	fc04fa015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_satq48s	aeq0, aeq1 }
    175a:	61c134        	ae_lq56.i	aeq3, a1, 24
    175d:	614124        	ae_lq56.i	aeq1, a1, 16
    1760:	623524        	ae_sq32f.i	aeq3, a5, 8
    1763:	61c144        	ae_lq56.i	aeq3, a1, 32
    1766:	d4e2f9953f 	{ ae_sq32f.i	aeq1, a5, 12; ae_mulfq32sp16u.l	aeq1, aeq0, aep0 }
    176b:	d46239b57f 	{ ae_sq32f.i	aeq3, a5, 28; ae_mulfq32sp16s.h	aeq0, aeq0, aep0 }
    1770:	61c3f4        	ae_lq56.i	aeq3, a3, -8
    1773:	ff84fa012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_satq48s	aeq3, aeq3 }
    1778:	610164        	ae_lq56.i	aeq0, a1, 48
    177b:	d6e3b9856f 	{ ae_sq32f.i	aeq0, a5, 24; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
    1780:	d7637b144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_mulfq32sp16s.h	aeq3, aeq3, aep0 }
    1785:	d6e6ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq0, aeq2, aep1 }
    178a:	d7663361fe 	{ l32i	a15, a1, 216; ae_mulfq32sp16s.h	aeq2, aeq2, aep1 }
    178f:	630144        	ae_sq56s.i	aeq0, a1, 32
    1792:	610124        	ae_lq56.i	aeq0, a1, 16
    1795:	f9663261ee 	{ l32i	a14, a1, 152; ae_addq56	aeq1, aeq0, aeq1 }
    179a:	631124        	ae_sq56s.i	aeq1, a1, 16
    179d:	614134        	ae_lq56.i	aeq1, a1, 24
    17a0:	351434        	ae_sraiq56	aeq0, aeq1, 16
    17a3:	614144        	ae_lq56.i	aeq1, a1, 32
    17a6:	630134        	ae_sq56s.i	aeq0, a1, 24
    17a9:	610154        	ae_lq56.i	aeq0, a1, 40
    17ac:	355434        	ae_sraiq56	aeq1, aeq1, 16
    17af:	f976398f0f 	{ ae_sq32f.i	aeq0, a15, 0; ae_addq56	aeq1, aeq2, aeq1 }
    17b4:	610134        	ae_lq56.i	aeq0, a1, 24
    17b7:	f87a3de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_addq56	aeq0, aeq3, aeq0 }
    17bc:	623f24        	ae_sq32f.i	aeq3, a15, 8
    17bf:	621f34        	ae_sq32f.i	aeq1, a15, 12
    17c2:	620f14        	ae_sq32f.i	aeq0, a15, 4
    17c5:	600504        	ae_lq32f.i	aeq0, a5, 0
    17c8:	604524        	ae_lq32f.i	aeq1, a5, 8
    17cb:	fa663d651f 	{ ae_lq32f.i	aeq3, a5, 4; ae_addq56	aeq2, aeq0, aeq1 }
    17d0:	f926fd053f 	{ ae_lq32f.i	aeq0, a5, 12; ae_subq56	aeq1, aeq0, aeq1 }
    17d5:	36a304        	ae_trunca32q48	a3, aeq2
    17d8:	f97a3f1fef 	{ ae_trunca32q48	a15, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    17dd:	f83afd442f 	{ ae_lq32f.i	aeq2, a4, 8; ae_subq56	aeq0, aeq3, aeq0 }
    17e2:	60c444        	ae_lq32f.i	aeq3, a4, 16
    17e5:	369a04        	ae_trunca32q48	a10, aeq1
    17e8:	f8f63f06ef 	{ ae_trunca32q48	a6, aeq0; ae_addq56	aeq0, aeq2, aeq3 }
    17ed:	fab6fd243f 	{ ae_lq32f.i	aeq1, a4, 12; ae_subq56	aeq2, aeq2, aeq3 }
    17f2:	60c454        	ae_lq32f.i	aeq3, a4, 20
    17f5:	f8ee3f08ef 	{ ae_trunca32q48	a8, aeq0; ae_addq56	aeq0, aeq1, aeq3 }
    17fa:	f9aefd655f 	{ ae_lq32f.i	aeq3, a5, 20; ae_subq56	aeq1, aeq1, aeq3 }
    17ff:	36a904        	ae_trunca32q48	a9, aeq2
    1802:	368c04        	ae_trunca32q48	a12, aeq0
    1805:	633134        	ae_sq56s.i	aeq3, a1, 24
    1808:	600544        	ae_lq32f.i	aeq0, a5, 16
    180b:	608564        	ae_lq32f.i	aeq2, a5, 24
    180e:	60c574        	ae_lq32f.i	aeq3, a5, 28
    1811:	272152        	l32i	a5, a1, 156
    1814:	0e39           	s32i.n	a3, a14, 0
    1816:	07f9           	s32i.n	a15, a7, 0
    1818:	05a9           	s32i.n	a10, a5, 0
    181a:	3121a2        	l32i	a10, a1, 196
    181d:	3c6172        	s32i	a7, a1, 240
    1820:	2a2172        	l32i	a7, a1, 168
    1823:	0a69           	s32i.n	a6, a10, 0
    1825:	fd047f1def 	{ ae_trunca32q48	a13, aeq1; ae_movq56	aeq1, aeq0 }
    182a:	f8a2d4078f 	{ s32i.n	a8, a7, 0; ae_subq56	aeq0, aeq0, aeq2 }
    182f:	f9ea32818e 	{ l32i	a8, a1, 160; ae_addq56	aeq1, aeq1, aeq2 }
    1834:	332162        	l32i	a6, a1, 204
    1837:	630124        	ae_sq56s.i	aeq0, a1, 16
    183a:	608404        	ae_lq32f.i	aeq2, a4, 0
    183d:	632144        	ae_sq56s.i	aeq2, a1, 32
    1840:	610124        	ae_lq56.i	aeq0, a1, 16
    1843:	618134        	ae_lq56.i	aeq2, a1, 24
    1846:	0899           	s32i.n	a9, a8, 0
    1848:	06c9           	s32i.n	a12, a6, 0
    184a:	fc1c7f0cef 	{ ae_trunca32q48	a12, aeq0; ae_movq56	aeq0, aeq3 }
    184f:	fbb6f2b1ee 	{ l32i	a14, a1, 172; ae_subq56	aeq3, aeq2, aeq3 }
    1854:	fa723a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_addq56	aeq2, aeq2, aeq0 }
    1859:	322182        	l32i	a8, a1, 200
    185c:	61c124        	ae_lq56.i	aeq3, a1, 16
    185f:	0ed9           	s32i.n	a13, a14, 0
    1861:	05fd           	mov.n	a15, a5
    1863:	369d04        	ae_trunca32q48	a13, aeq1
    1866:	36b504        	ae_trunca32q48	a5, aeq3
    1869:	60c414        	ae_lq32f.i	aeq3, a4, 4
    186c:	08c9           	s32i.n	a12, a8, 0
    186e:	633134        	ae_sq56s.i	aeq3, a1, 24
    1871:	0bd9           	s32i.n	a13, a11, 0
    1873:	3e21d2        	l32i	a13, a1, 248
    1876:	604464        	ae_lq32f.i	aeq1, a4, 24
    1879:	60c474        	ae_lq32f.i	aeq3, a4, 28
    187c:	2c2142        	l32i	a4, a1, 176
    187f:	610144        	ae_lq56.i	aeq0, a1, 32
    1882:	fe0c7f27ef 	{ ae_trunca32q48	a7, aeq2; ae_movq56	aeq2, aeq1 }
    1887:	f966140d5f 	{ s32i.n	a5, a13, 0; ae_addq56	aeq1, aeq0, aeq1 }
    188c:	f8a2fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
    1891:	0479           	s32i.n	a7, a4, 0
    1893:	292172        	l32i	a7, a1, 164
    1896:	614124        	ae_lq56.i	aeq1, a1, 16
    1899:	369904        	ae_trunca32q48	a9, aeq1
    189c:	618134        	ae_lq56.i	aeq2, a1, 24
    189f:	f9f614079f 	{ s32i.n	a9, a7, 0; ae_addq56	aeq1, aeq2, aeq3 }
    18a4:	3b61b2        	s32i	a11, a1, 236
    18a7:	fbb6f2f1be 	{ l32i	a11, a1, 188; ae_subq56	aeq3, aeq2, aeq3 }
    18ac:	2e2172        	l32i	a7, a1, 184
    18af:	368c04        	ae_trunca32q48	a12, aeq0
    18b2:	369904        	ae_trunca32q48	a9, aeq1
    18b5:	0bc9           	s32i.n	a12, a11, 0
    18b7:	0799           	s32i.n	a9, a7, 0
    18b9:	302192        	l32i	a9, a1, 192
    18bc:	36bc04        	ae_trunca32q48	a12, aeq3
    18bf:	3d2152        	l32i	a5, a1, 244
    18c2:	09c9           	s32i.n	a12, a9, 0
    18c4:	3a21c2        	l32i	a12, a1, 232
    18c7:	3f2132        	l32i	a3, a1, 252
    18ca:	258b           	addi.n	a2, a5, 8
    18cc:	5c0b           	addi.n	a5, a12, -1
    18ce:	c38b           	addi.n	a12, a3, 8
    18d0:	2d2132        	l32i	a3, a1, 180
    18d3:	aa3a           	add.n	a10, a10, a3
    18d5:	3161a2        	s32i	a10, a1, 196
    18d8:	ee3a           	add.n	a14, a14, a3
    18da:	773a           	add.n	a7, a7, a3
    18dc:	2621a2        	l32i	a10, a1, 152
    18df:	2b61e2        	s32i	a14, a1, 172
    18e2:	2e6172        	s32i	a7, a1, 184
    18e5:	993a           	add.n	a9, a9, a3
    18e7:	3b21e2        	l32i	a14, a1, 236
    18ea:	292172        	l32i	a7, a1, 164
    18ed:	443a           	add.n	a4, a4, a3
    18ef:	306192        	s32i	a9, a1, 192
    18f2:	282192        	l32i	a9, a1, 160
    18f5:	2c6142        	s32i	a4, a1, 176
    18f8:	054d           	mov.n	a4, a5
    18fa:	5a3a           	add.n	a5, a10, a3
    18fc:	bb3a           	add.n	a11, a11, a3
    18fe:	2a21a2        	l32i	a10, a1, 168
    1901:	266152        	s32i	a5, a1, 152
    1904:	2f61b2        	s32i	a11, a1, 188
    1907:	573a           	add.n	a5, a7, a3
    1909:	be3a           	add.n	a11, a14, a3
    190b:	3c21e2        	l32i	a14, a1, 240
    190e:	296152        	s32i	a5, a1, 164
    1911:	593a           	add.n	a5, a9, a3
    1913:	663a           	add.n	a6, a6, a3
    1915:	883a           	add.n	a8, a8, a3
    1917:	286152        	s32i	a5, a1, 160
    191a:	5a3a           	add.n	a5, a10, a3
    191c:	336162        	s32i	a6, a1, 204
    191f:	326182        	s32i	a8, a1, 200
    1922:	ff3a           	add.n	a15, a15, a3
    1924:	862c           	movi.n	a6, 40
    1926:	dd3a           	add.n	a13, a13, a3
    1928:	082c           	movi.n	a8, 32
    192a:	7e3a           	add.n	a7, a14, a3
    192c:	2a6152        	s32i	a5, a1, 168
    192f:	047416        	beqz	a4, 197a <fix_fft40+0x5b2>

00001932 <fix_fft40+0x56a>:
    1932:	d8c232        	addi	a3, a2, -40
    1935:	0358           	l32i.n	a5, a3, 0
    1937:	1338           	l32i.n	a3, a3, 4
    1939:	2761f2        	s32i	a15, a1, 156
    193c:	215150        	srai	a5, a5, 1
    193f:	213130        	srai	a3, a3, 1
    1942:	146152        	s32i	a5, a1, 80
    1945:	156132        	s32i	a3, a1, 84
    1948:	3f61c2        	s32i	a12, a1, 252
    194b:	3e61d2        	s32i	a13, a1, 248
    194e:	3d6122        	s32i	a2, a1, 244
    1951:	3a6142        	s32i	a4, a1, 232
    1954:	025426        	beqi	a4, 5, 195a <fix_fft40+0x592>
    1957:	fee146        	j	14e0 <fix_fft40+0x118>
    195a:	342152        	l32i	a5, a1, 208
    195d:	7f0c           	movi.n	a15, 7
    195f:	023d           	mov.n	a3, a2
    1961:	128f76        	loop	a15, 1977 <fix_fft40+0x5af>
    1964:	03f8           	l32i.n	a15, a3, 0
    1966:	1328           	l32i.n	a2, a3, 4
    1968:	28c332        	addi	a3, a3, 40
    196b:	21f1f0        	srai	a15, a15, 1
    196e:	212120        	srai	a2, a2, 1
    1971:	05f9           	s32i.n	a15, a5, 0
    1973:	1529           	s32i.n	a2, a5, 4
    1975:	558b           	addi.n	a5, a5, 8

00001977 <fix_fft40+0x5af>:
    1977:	fefac6        	j	1566 <fix_fft40+0x19e>

0000197a <fix_fft40+0x5b2>:
    197a:	f01d           	retw.n

0000197c <FFT4N>:
    197c:	012136        	entry	a1, 144
    197f:	f159           	s32i.n	a5, a1, 60
    1981:	0215e6        	bgei	a5, 1, 1987 <FFT4N+0xb>
    1984:	006006        	j	1b08 <FFT4N+0x18c>
    1987:	03ed           	mov.n	a14, a3
    1989:	f138           	l32i.n	a3, a1, 60
    198b:	04bd           	mov.n	a11, a4
    198d:	252142        	l32i	a4, a1, 148
    1990:	106142        	s32i	a4, a1, 64
    1993:	1143c0        	slli	a4, a3, 4
    1996:	1177f0        	slli	a7, a7, 1
    1999:	136172        	s32i	a7, a1, 76
    199c:	7b4a           	add.n	a7, a11, a4
    199e:	d1d630        	mul16s	a13, a6, a3
    19a1:	1021b2        	l32i	a11, a1, 64
    19a4:	190c           	movi.n	a9, 1
    19a6:	14c152        	addi	a5, a1, 20
    19a9:	242182        	l32i	a8, a1, 144
    19ac:	e159           	s32i.n	a5, a1, 56
    19ae:	1156e0        	slli	a5, a6, 2
    19b1:	119930        	slli	a9, a9, 13
    19b4:	8d6d           	ae_sext16	a6, a13
    19b6:	300994        	ae_cvtp24a16x2.ll	aep0, a9, a9
    19b9:	1196e0        	slli	a9, a6, 2
    19bc:	11dbf0        	slli	a13, a11, 1
    19bf:	126152        	s32i	a5, a1, 72
    19c2:	116142        	s32i	a4, a1, 68
    19c5:	1146d0        	slli	a4, a6, 3
    19c8:	606090        	neg	a6, a9
    19cb:	c097d0        	sub	a9, a7, a13
    19ce:	11a3d0        	slli	a10, a3, 3
    19d1:	20c1c2        	addi	a12, a1, 32
    19d4:	0f0c           	movi.n	a15, 0
    19d6:	b0d380        	addx8	a13, a3, a8
    19d9:	050c           	movi.n	a5, 0
    19db:	002ec6        	j	1a9a <FFT4N+0x11e>

000019de <FFT4N+0x62>:
    19de:	e1b8           	l32i.n	a11, a1, 56
    19e0:	0d7d           	mov.n	a7, a13
    19e2:	330c           	movi.n	a3, 3
    19e4:	601704        	ae_lq32f.iu	aeq0, a7, 0
    19e7:	108376        	loop	a3, 19fb <FFT4N+0x7f>
    19ea:	d4e23d271f 	{ ae_lq32f.i	aeq1, a7, 4; ae_mulfq32sp16s.l	aeq0, aeq0, aep0 }
    19ef:	030a54        	ae_mulfq32sp16s.l	aeq1, aeq1, aep0
    19f2:	624b14        	ae_sq32f.iu	aeq0, a11, 4
    19f5:	6037a4        	ae_lq32f.xu	aeq0, a7, a10
    19f8:	625b14        	ae_sq32f.iu	aeq1, a11, 4

000019fb <FFT4N+0x7f>:
    19fb:	600c04        	ae_lq32f.i	aeq0, a12, 0
    19fe:	604144        	ae_lq32f.i	aeq1, a1, 16
    1a01:	fb6a05017e 	{ addi	a7, a1, 80; ae_addq56	aeq3, aeq1, aeq0 }
    1a06:	f82af9b70f 	{ ae_sq32f.i	aeq3, a7, 0; ae_subq56	aeq0, aeq1, aeq0 }
    1a0b:	604c14        	ae_lq32f.i	aeq1, a12, 4
    1a0e:	60c154        	ae_lq32f.i	aeq3, a1, 20
    1a11:	f87e39872f 	{ ae_sq32f.i	aeq0, a7, 8; ae_addq56	aeq0, aeq3, aeq1 }
    1a16:	f93ef9871f 	{ ae_sq32f.i	aeq0, a7, 4; ae_subq56	aeq1, aeq3, aeq1 }
    1a1b:	60cc24        	ae_lq32f.i	aeq3, a12, 8
    1a1e:	600164        	ae_lq32f.i	aeq0, a1, 24
    1a21:	f9e639973f 	{ ae_sq32f.i	aeq1, a7, 12; ae_addq56	aeq1, aeq0, aeq3 }
    1a26:	f8a6fd617f 	{ ae_lq32f.i	aeq3, a1, 28; ae_subq56	aeq0, aeq0, aeq3 }
    1a2b:	608c34        	ae_lq32f.i	aeq2, a12, 12
    1a2e:	f9f639974f 	{ ae_sq32f.i	aeq1, a7, 16; ae_addq56	aeq1, aeq2, aeq3 }
    1a33:	fab6f9877f 	{ ae_sq32f.i	aeq0, a7, 28; ae_subq56	aeq2, aeq2, aeq3 }
    1a38:	621754        	ae_sq32f.i	aeq1, a7, 20
    1a3b:	600704        	ae_lq32f.i	aeq0, a7, 0
    1a3e:	604744        	ae_lq32f.i	aeq1, a7, 16
    1a41:	fb6639a76f 	{ ae_sq32f.i	aeq2, a7, 24; ae_addq56	aeq3, aeq0, aeq1 }
    1a46:	f826d3b22f 	{ or	a11, a2, a2; ae_subq56	aeq0, aeq0, aeq1 }
    1a4b:	604714        	ae_lq32f.i	aeq1, a7, 4
    1a4e:	608754        	ae_lq32f.i	aeq2, a7, 20
    1a51:	fbea38bb5f 	{ ae_sq32f.xu	aeq3, a11, a5; ae_addq56	aeq3, aeq1, aeq2 }
    1a56:	0e3d           	mov.n	a3, a14
    1a58:	f9aaf88b4f 	{ ae_sq32f.xu	aeq0, a11, a4; ae_subq56	aeq1, aeq1, aeq2 }
    1a5d:	62f354        	ae_sq32f.xu	aeq3, a3, a5
    1a60:	608724        	ae_lq32f.i	aeq2, a7, 8
    1a63:	600764        	ae_lq32f.i	aeq0, a7, 24
    1a66:	fb32f8934f 	{ ae_sq32f.xu	aeq1, a3, a4; ae_subq56	aeq3, aeq2, aeq0 }
    1a6b:	f8723d473f 	{ ae_lq32f.i	aeq2, a7, 12; ae_addq56	aeq0, aeq2, aeq0 }
    1a70:	604774        	ae_lq32f.i	aeq1, a7, 28
    1a73:	fb36f8bb6f 	{ ae_sq32f.xu	aeq3, a11, a6; ae_subq56	aeq3, aeq2, aeq1 }
    1a78:	f976388b4f 	{ ae_sq32f.xu	aeq0, a11, a4; ae_addq56	aeq1, aeq2, aeq1 }
    1a7d:	62f364        	ae_sq32f.xu	aeq3, a3, a6
    1a80:	62d344        	ae_sq32f.xu	aeq1, a3, a4
    1a83:	122172        	l32i	a7, a1, 72
    1a86:	132132        	l32i	a3, a1, 76
    1a89:	f1b8           	l32i.n	a11, a1, 60
    1a8b:	ff1b           	addi.n	a15, a15, 1
    1a8d:	dd8b           	addi.n	a13, a13, 8
    1a8f:	888b           	addi.n	a8, a8, 8
    1a91:	993a           	add.n	a9, a9, a3
    1a93:	ee7a           	add.n	a14, a14, a7
    1a95:	227a           	add.n	a2, a2, a7
    1a97:	6d1bf7        	beq	a11, a15, 1b08 <FFT4N+0x18c>

00001a9a <FFT4N+0x11e>:
    1a9a:	0878           	l32i.n	a7, a8, 0
    1a9c:	18b8           	l32i.n	a11, a8, 4
    1a9e:	112132        	l32i	a3, a1, 68
    1aa1:	217270        	srai	a7, a7, 2
    1aa4:	21b2b0        	srai	a11, a11, 2
    1aa7:	4179           	s32i.n	a7, a1, 16
    1aa9:	51b9           	s32i.n	a11, a1, 20
    1aab:	f2ff16        	beqz	a15, 19de <FFT4N+0x62>
    1aae:	097d           	mov.n	a7, a9
    1ab0:	600d04        	ae_lq32f.i	aeq0, a13, 0
    1ab3:	604d14        	ae_lq32f.i	aeq1, a13, 4
    1ab6:	441904        	ae_lp16x2f.i	aep1, a9, 0
    1ab9:	6d255ba73f 	{ ae_lp16x2f.xu	aep2, a7, a3; ae_mulzsafq32sp16s.lh	aeq3, aeq1, aep1, aeq0, aep1 }
    1abe:	0c249bf73f 	{ ae_lp16x2f.xu	aep7, a7, a3; ae_mulzaafq32sp16s.lh	aeq0, aeq0, aep1, aeq1, aep1 }
    1ac3:	0dbd           	mov.n	a11, a13
    1ac5:	633114        	ae_sq56s.i	aeq3, a1, 8
    1ac8:	e178           	l32i.n	a7, a1, 56
    1aca:	614114        	ae_lq56.i	aeq1, a1, 8
    1acd:	60bba4        	ae_lq32f.xu	aeq2, a11, a10
    1ad0:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
    1ad3:	60cb14        	ae_lq32f.i	aeq3, a11, 4
    1ad6:	6e4b79d71f 	{ ae_sq32f.iu	aeq1, a7, 4; ae_mulzsafq32sp16s.lh	aeq1, aeq3, aep2, aeq2, aep2 }
    1adb:	0f4abb002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_mulzaafq32sp16s.lh	aeq2, aeq2, aep2, aeq3, aep2 }
    1ae0:	624714        	ae_sq32f.iu	aeq0, a7, 4
    1ae3:	603ba4        	ae_lq32f.xu	aeq0, a11, a10
    1ae6:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
    1ae9:	60cb14        	ae_lq32f.i	aeq3, a11, 4
    1aec:	6efd79d71f 	{ ae_sq32f.iu	aeq1, a7, 4; ae_mulzsafq32sp16s.lh	aeq1, aeq3, aep7, aeq0, aep7 }
    1af1:	0cfebb20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_mulzaafq32sp16s.lh	aeq0, aeq0, aep7, aeq3, aep7 }
    1af6:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
    1af9:	626714        	ae_sq32f.iu	aeq2, a7, 4
    1afc:	3500b4        	ae_sraiq56	aeq0, aeq0, 2
    1aff:	625714        	ae_sq32f.iu	aeq1, a7, 4
    1b02:	624714        	ae_sq32f.iu	aeq0, a7, 4
    1b05:	ffbc86        	j	19fb <FFT4N+0x7f>

00001b08 <FFT4N+0x18c>:
    1b08:	f01d           	retw.n

00001b0a <FFT4N+0x18e>:
	...

00001b0c <FFT8N>:
    1b0c:	02a136        	entry	a1, 0x150
    1b0f:	256132        	s32i	a3, a1, 148
    1b12:	246152        	s32i	a5, a1, 144
    1b15:	0215e6        	bgei	a5, 1, 1b1b <FFT8N+0xf>
    1b18:	00e606        	j	1eb4 <FFT8N+0x3a8>
    1b1b:	7ea082        	movi	a8, 126
    1b1e:	82a092        	movi	a9, 130
    1b21:	07fd           	mov.n	a15, a7
    1b23:	242172        	l32i	a7, a1, 144
    1b26:	a5d882        	addmi	a8, a8, 0xffffa500
    1b29:	5ad992        	addmi	a9, a9, 0x5a00
    1b2c:	300984        	ae_cvtp24a16x2.ll	aep0, a9, a8
    1b2f:	01d192        	addmi	a9, a1, 0x100
    1b32:	552152        	l32i	a5, a1, 0x154
    1b35:	e0c982        	addi	a8, a9, -32
    1b38:	44c1e2        	addi	a14, a1, 68
    1b3b:	2361e2        	s32i	a14, a1, 140
    1b3e:	d1ef70        	mul16s	a14, a15, a7
    1b41:	296182        	s32i	a8, a1, 164
    1b44:	11fff0        	slli	a15, a15, 1
    1b47:	d18670        	mul16s	a8, a6, a7
    1b4a:	190c           	movi.n	a9, 1
    1b4c:	2861f2        	s32i	a15, a1, 160
    1b4f:	11f6e0        	slli	a15, a6, 2
    1b52:	116920        	slli	a6, a9, 14
    1b55:	542132        	l32i	a3, a1, 0x150
    1b58:	2761f2        	s32i	a15, a1, 156
    1b5b:	301664        	ae_cvtp24a16x2.ll	aep1, a6, a6
    1b5e:	90fe40        	addx2	a15, a14, a4
    1b61:	1155f0        	slli	a5, a5, 1
    1b64:	886d           	ae_sext16	a6, a8
    1b66:	c09f50        	sub	a9, a15, a5
    1b69:	11f6c0        	slli	a15, a6, 4
    1b6c:	01d1c2        	addmi	a12, a1, 0x100
    1b6f:	01d1d2        	addmi	a13, a1, 0x100
    1b72:	e086f0        	subx4	a8, a6, a15
    1b75:	114ef0        	slli	a4, a14, 1
    1b78:	03ed           	mov.n	a14, a3
    1b7a:	11a7d0        	slli	a10, a7, 3
    1b7d:	60c1b2        	addi	a11, a1, 96
    1b80:	10ccc2        	addi	a12, a12, 16
    1b83:	d0cdd2        	addi	a13, a13, -48
    1b86:	266182        	s32i	a8, a1, 152
    1b89:	060c           	movi.n	a6, 0
    1b8b:	b05730        	addx8	a5, a7, a3

00001b8e <FFT8N+0x82>:
    1b8e:	0e78           	l32i.n	a7, a14, 0
    1b90:	1e88           	l32i.n	a8, a14, 4
    1b92:	2b61e2        	s32i	a14, a1, 172
    1b95:	217170        	srai	a7, a7, 1
    1b98:	218180        	srai	a8, a8, 1
    1b9b:	106172        	s32i	a7, a1, 64
    1b9e:	116182        	s32i	a8, a1, 68
    1ba1:	2a6192        	s32i	a9, a1, 168
    1ba4:	2eb616        	beqz	a6, 1e93 <FFT8N+0x387>
    1ba7:	600504        	ae_lq32f.i	aeq0, a5, 0
    1baa:	604514        	ae_lq32f.i	aeq1, a5, 4
    1bad:	442904        	ae_lp16x2f.i	aep2, a9, 0
    1bb0:	854932317e 	{ l32i	a7, a1, 140; ae_mulzsaq32sp16s.lh	aeq2, aeq1, aep2, aeq0, aep2 }
    1bb5:	098d           	mov.n	a8, a9
    1bb7:	330c           	movi.n	a3, 3
    1bb9:	2448b9e71f 	{ ae_sq32f.iu	aeq2, a7, 4; ae_mulzaaq32sp16s.lh	aeq0, aeq0, aep2, aeq1, aep2 }
    1bbe:	45a844        	ae_lp16x2f.xu	aep2, a8, a4
    1bc1:	05ed           	mov.n	a14, a5
    1bc3:	624714        	ae_sq32f.iu	aeq0, a7, 4
    1bc6:	258376        	loop	a3, 1bef <FFT8N+0xe3>
    1bc9:	603ea4        	ae_lq32f.xu	aeq0, a14, a10
    1bcc:	604e14        	ae_lq32f.i	aeq1, a14, 4
    1bcf:	85497c4eaf 	{ ae_lq32f.xu	aeq2, a14, a10; ae_mulzsaq32sp16s.lh	aeq3, aeq1, aep2, aeq0, aep2 }
    1bd4:	24489bb84f 	{ ae_lp16x2f.xu	aep3, a8, a4; ae_mulzaaq32sp16s.lh	aeq0, aeq0, aep2, aeq1, aep2 }
    1bd9:	604e14        	ae_lq32f.i	aeq1, a14, 4
    1bdc:	856f79f71f 	{ ae_sq32f.iu	aeq3, a7, 4; ae_mulzsaq32sp16s.lh	aeq3, aeq1, aep3, aeq2, aep3 }
    1be1:	266cf9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulzaaq32sp16s.lh	aeq1, aeq2, aep3, aeq1, aep3 }
    1be6:	627714        	ae_sq32f.iu	aeq3, a7, 4
    1be9:	45a844        	ae_lp16x2f.xu	aep2, a8, a4
    1bec:	625714        	ae_sq32f.iu	aeq1, a7, 4

00001bef <FFT8N+0xe3>:
    1bef:	40c182        	addi	a8, a1, 64
    1bf2:	60cb24        	ae_lq32f.i	aeq3, a11, 8
    1bf5:	608824        	ae_lq32f.i	aeq2, a8, 8
    1bf8:	600b04        	ae_lq32f.i	aeq0, a11, 0
    1bfb:	fab6fa213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_subq56	aeq2, aeq2, aeq3 }
    1c00:	01d1e2        	addmi	a14, a1, 0x100
    1c03:	630154        	ae_sq56s.i	aeq0, a1, 40
    1c06:	604b34        	ae_lq32f.i	aeq1, a11, 12
    1c09:	600834        	ae_lq32f.i	aeq0, a8, 12
    1c0c:	632174        	ae_sq56s.i	aeq2, a1, 56
    1c0f:	fb26fa314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_subq56	aeq3, aeq0, aeq1 }
    1c14:	631124        	ae_sq56s.i	aeq1, a1, 16
    1c17:	630164        	ae_sq56s.i	aeq0, a1, 48
    1c1a:	614174        	ae_lq56.i	aeq1, a1, 56
    1c1d:	608804        	ae_lq32f.i	aeq2, a8, 0
    1c20:	610154        	ae_lq56.i	aeq0, a1, 40
    1c23:	f972399e2f 	{ ae_sq32f.i	aeq1, a14, 8; ae_addq56	aeq1, aeq2, aeq0 }
    1c28:	f832fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq2, aeq0 }
    1c2d:	621ec4        	ae_sq32f.i	aeq1, a14, -16
    1c30:	604814        	ae_lq32f.i	aeq1, a8, 4
    1c33:	608b14        	ae_lq32f.i	aeq2, a11, 4
    1c36:	fbea39be3f 	{ ae_sq32f.i	aeq3, a14, 12; ae_addq56	aeq3, aeq1, aeq2 }
    1c3b:	f9aafb002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_subq56	aeq1, aeq1, aeq2 }
    1c40:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    1c43:	620ee4        	ae_sq32f.i	aeq0, a14, -8
    1c46:	623ed4        	ae_sq32f.i	aeq3, a14, -12
    1c49:	3590b4        	ae_sraiq56	aeq2, aeq1, 2
    1c4c:	61c144        	ae_lq56.i	aeq3, a1, 32
    1c4f:	610134        	ae_lq56.i	aeq0, a1, 24
    1c52:	f9e63a215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_addq56	aeq1, aeq0, aeq3 }
    1c57:	61c124        	ae_lq56.i	aeq3, a1, 16
    1c5a:	610164        	ae_lq56.i	aeq0, a1, 48
    1c5d:	fbe63d815f 	{ ae_lq56.i	aeq0, a1, 40; ae_addq56	aeq3, aeq0, aeq3 }
    1c62:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    1c65:	620ef4        	ae_sq32f.i	aeq0, a14, -4
    1c68:	608b44        	ae_lq32f.i	aeq2, a11, 16
    1c6b:	600844        	ae_lq32f.i	aeq0, a8, 16
    1c6e:	fbe239be1f 	{ ae_sq32f.i	aeq3, a14, 4; ae_addq56	aeq3, aeq0, aeq2 }
    1c73:	f8a2fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq0, aeq2 }
    1c78:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    1c7b:	630124        	ae_sq56s.i	aeq0, a1, 16
    1c7e:	621e04        	ae_sq32f.i	aeq1, a14, 0
    1c81:	633134        	ae_sq56s.i	aeq3, a1, 24
    1c84:	604854        	ae_lq32f.i	aeq1, a8, 20
    1c87:	608b54        	ae_lq32f.i	aeq2, a11, 20
    1c8a:	f8ea3de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_addq56	aeq0, aeq1, aeq2 }
    1c8f:	f9aafb30af 	{ ae_sraiq56	aeq2, aeq3, 2; ae_subq56	aeq1, aeq1, aeq2 }
    1c94:	631144        	ae_sq56s.i	aeq1, a1, 32
    1c97:	622c24        	ae_sq32f.i	aeq2, a12, 8
    1c9a:	608874        	ae_lq32f.i	aeq2, a8, 28
    1c9d:	3540b4        	ae_sraiq56	aeq1, aeq0, 2
    1ca0:	610134        	ae_lq56.i	aeq0, a1, 24
    1ca3:	632134        	ae_sq56s.i	aeq2, a1, 24
    1ca6:	618144        	ae_lq56.i	aeq2, a1, 32
    1ca9:	620c04        	ae_sq32f.i	aeq0, a12, 0
    1cac:	3520b4        	ae_sraiq56	aeq0, aeq2, 2
    1caf:	621c14        	ae_sq32f.i	aeq1, a12, 4
    1cb2:	604864        	ae_lq32f.i	aeq1, a8, 24
    1cb5:	60cb64        	ae_lq32f.i	aeq3, a11, 24
    1cb8:	fc1c7a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_movq56	aeq0, aeq3 }
    1cbd:	fbee3d4b7f 	{ ae_lq32f.i	aeq2, a11, 28; ae_addq56	aeq3, aeq1, aeq3 }
    1cc2:	f92afa314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_subq56	aeq1, aeq1, aeq0 }
    1cc7:	61c124        	ae_lq56.i	aeq3, a1, 16
    1cca:	610134        	ae_lq56.i	aeq0, a1, 24
    1ccd:	fbe239bc3f 	{ ae_sq32f.i	aeq3, a12, 12; ae_addq56	aeq3, aeq0, aeq2 }
    1cd2:	f8a2fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_subq56	aeq0, aeq0, aeq2 }
    1cd7:	35a0b4        	ae_sraiq56	aeq2, aeq2, 2
    1cda:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
    1cdd:	622c44        	ae_sq32f.i	aeq2, a12, 16
    1ce0:	620c74        	ae_sq32f.i	aeq0, a12, 28
    1ce3:	621c64        	ae_sq32f.i	aeq1, a12, 24
    1ce6:	623c54        	ae_sq32f.i	aeq3, a12, 20
    1ce9:	01d172        	addmi	a7, a1, 0x100
    1cec:	600c04        	ae_lq32f.i	aeq0, a12, 0
    1cef:	604ec4        	ae_lq32f.i	aeq1, a14, -16
    1cf2:	fb6a0b077e 	{ addi	a7, a7, -80; ae_addq56	aeq3, aeq1, aeq0 }
    1cf7:	f82af9b70f 	{ ae_sq32f.i	aeq3, a7, 0; ae_subq56	aeq0, aeq1, aeq0 }
    1cfc:	608c14        	ae_lq32f.i	aeq2, a12, 4
    1cff:	60ced4        	ae_lq32f.i	aeq3, a14, -12
    1d02:	f8fa39874f 	{ ae_sq32f.i	aeq0, a7, 16; ae_addq56	aeq0, aeq3, aeq2 }
    1d07:	fabaf9871f 	{ ae_sq32f.i	aeq0, a7, 4; ae_subq56	aeq2, aeq3, aeq2 }
    1d0c:	604c34        	ae_lq32f.i	aeq1, a12, 12
    1d0f:	600ee4        	ae_lq32f.i	aeq0, a14, -8
    1d12:	fa26f9a75f 	{ ae_sq32f.i	aeq2, a7, 20; ae_subq56	aeq2, aeq0, aeq1 }
    1d17:	f86639ad0f 	{ ae_sq32f.i	aeq2, a13, 0; ae_addq56	aeq0, aeq0, aeq1 }
    1d1c:	630124        	ae_sq56s.i	aeq0, a1, 16
    1d1f:	608c44        	ae_lq32f.i	aeq2, a12, 16
    1d22:	632134        	ae_sq56s.i	aeq2, a1, 24
    1d25:	618124        	ae_lq56.i	aeq2, a1, 16
    1d28:	60cc24        	ae_lq32f.i	aeq3, a12, 8
    1d2b:	600ef4        	ae_lq32f.i	aeq0, a14, -4
    1d2e:	f9e639ad2f 	{ ae_sq32f.i	aeq2, a13, 8; ae_addq56	aeq1, aeq0, aeq3 }
    1d33:	f8a6fd4e0f 	{ ae_lq32f.i	aeq2, a14, 0; ae_subq56	aeq0, aeq0, aeq3 }
    1d38:	61c134        	ae_lq56.i	aeq3, a1, 24
    1d3b:	f8f63a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_addq56	aeq0, aeq2, aeq3 }
    1d40:	fab6f99d1f 	{ ae_sq32f.i	aeq1, a13, 4; ae_subq56	aeq2, aeq2, aeq3 }
    1d45:	630124        	ae_sq56s.i	aeq0, a1, 16
    1d48:	61c144        	ae_lq56.i	aeq3, a1, 32
    1d4b:	604c64        	ae_lq32f.i	aeq1, a12, 24
    1d4e:	600e24        	ae_lq32f.i	aeq0, a14, 8
    1d51:	fb6639bd3f 	{ ae_sq32f.i	aeq3, a13, 12; ae_addq56	aeq3, aeq0, aeq1 }
    1d56:	f826fda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq1 }
    1d5b:	632134        	ae_sq56s.i	aeq2, a1, 24
    1d5e:	621724        	ae_sq32f.i	aeq1, a7, 8
    1d61:	3570b4        	ae_sraiq56	aeq1, aeq3, 2
    1d64:	60cc54        	ae_lq32f.i	aeq3, a12, 20
    1d67:	3500b4        	ae_sraiq56	aeq0, aeq0, 2
    1d6a:	608e14        	ae_lq32f.i	aeq2, a14, 4
    1d6d:	f8f6398eef 	{ ae_sq32f.i	aeq0, a14, -8; ae_addq56	aeq0, aeq2, aeq3 }
    1d72:	fabaf99edf 	{ ae_sq32f.i	aeq1, a14, -12; ae_subq56	aeq2, aeq3, aeq2 }
    1d77:	630124        	ae_sq56s.i	aeq0, a1, 16
    1d7a:	61c134        	ae_lq56.i	aeq3, a1, 24
    1d7d:	604c74        	ae_lq32f.i	aeq1, a12, 28
    1d80:	600e34        	ae_lq32f.i	aeq0, a14, 12
    1d83:	632144        	ae_sq56s.i	aeq2, a1, 32
    1d86:	fb6639b77f 	{ ae_sq32f.i	aeq3, a7, 28; ae_addq56	aeq3, aeq0, aeq1 }
    1d8b:	f826fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq0, aeq1 }
    1d90:	622734        	ae_sq32f.i	aeq2, a7, 12
    1d93:	35b0b4        	ae_sraiq56	aeq2, aeq3, 2
    1d96:	3500b4        	ae_sraiq56	aeq0, aeq0, 2
    1d99:	622ec4        	ae_sq32f.i	aeq2, a14, -16
    1d9c:	620ef4        	ae_sq32f.i	aeq0, a14, -4
    1d9f:	600ec4        	ae_lq32f.i	aeq0, a14, -16
    1da2:	604ee4        	ae_lq32f.i	aeq1, a14, -8
    1da5:	0900bd6eff 	{ ae_lq32f.i	aeq3, a14, -4; ae_mulzaafq32sp16s.hh	aeq2, aeq0, aep0, aeq1, aep0 }
    1daa:	3800ba316f 	{ ae_sq56s.i	aeq3, a1, 48; ae_mulzasfq32sp16s.hh	aeq0, aeq0, aep0, aeq1, aep0 }
    1daf:	60ced4        	ae_lq32f.i	aeq3, a14, -12
    1db2:	630124        	ae_sq56s.i	aeq0, a1, 16
    1db5:	610164        	ae_lq56.i	aeq0, a1, 48
    1db8:	292132        	l32i	a3, a1, 164
    1dbb:	3902ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulzasfq32sp16s.hh	aeq2, aeq0, aep0, aeq3, aep0 }
    1dc0:	1002bda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulzaafq32sp16s.ll	aeq0, aeq0, aep0, aeq3, aep0 }
    1dc5:	621764        	ae_sq32f.i	aeq1, a7, 24
    1dc8:	614134        	ae_lq56.i	aeq1, a1, 24
    1dcb:	61c124        	ae_lq56.i	aeq3, a1, 16
    1dce:	621304        	ae_sq32f.i	aeq1, a3, 0
    1dd1:	623324        	ae_sq32f.i	aeq3, a3, 8
    1dd4:	620334        	ae_sq32f.i	aeq0, a3, 12
    1dd7:	622314        	ae_sq32f.i	aeq2, a3, 4
    1dda:	252132        	l32i	a3, a1, 148
    1ddd:	600704        	ae_lq32f.i	aeq0, a7, 0
    1de0:	608724        	ae_lq32f.i	aeq2, a7, 8
    1de3:	fbe213822f 	{ or	a8, a2, a2; ae_addq56	aeq3, aeq0, aeq2 }
    1de8:	f8a2c0009f 	{ movi	a9, 0; ae_subq56	aeq0, aeq0, aeq2 }
    1ded:	604714        	ae_lq32f.i	aeq1, a7, 4
    1df0:	608734        	ae_lq32f.i	aeq2, a7, 12
    1df3:	fbea38b89f 	{ ae_sq32f.xu	aeq3, a8, a9; ae_addq56	aeq3, aeq1, aeq2 }
    1df8:	03ed           	mov.n	a14, a3
    1dfa:	f9aaf888ff 	{ ae_sq32f.xu	aeq0, a8, a15; ae_subq56	aeq1, aeq1, aeq2 }
    1dff:	62fe94        	ae_sq32f.xu	aeq3, a14, a9
    1e02:	262192        	l32i	a9, a1, 152
    1e05:	608d24        	ae_lq32f.i	aeq2, a13, 8
    1e08:	600d44        	ae_lq32f.i	aeq0, a13, 16
    1e0b:	fb72389eff 	{ ae_sq32f.xu	aeq1, a14, a15; ae_addq56	aeq3, aeq2, aeq0 }
    1e10:	f832f8b89f 	{ ae_sq32f.xu	aeq3, a8, a9; ae_subq56	aeq0, aeq2, aeq0 }
    1e15:	608d34        	ae_lq32f.i	aeq2, a13, 12
    1e18:	604d54        	ae_lq32f.i	aeq1, a13, 20
    1e1b:	fb763888ff 	{ ae_sq32f.xu	aeq0, a8, a15; ae_addq56	aeq3, aeq2, aeq1 }
    1e20:	f936fd074f 	{ ae_lq32f.i	aeq0, a7, 16; ae_subq56	aeq1, aeq2, aeq1 }
    1e25:	608764        	ae_lq32f.i	aeq2, a7, 24
    1e28:	fba2f8be9f 	{ ae_sq32f.xu	aeq3, a14, a9; ae_subq56	aeq3, aeq0, aeq2 }
    1e2d:	f8e2389eff 	{ ae_sq32f.xu	aeq1, a14, a15; ae_addq56	aeq0, aeq0, aeq2 }
    1e32:	62f894        	ae_sq32f.xu	aeq3, a8, a9
    1e35:	604754        	ae_lq32f.i	aeq1, a7, 20
    1e38:	608774        	ae_lq32f.i	aeq2, a7, 28
    1e3b:	fbaaf888ff 	{ ae_sq32f.xu	aeq0, a8, a15; ae_subq56	aeq3, aeq1, aeq2 }
    1e40:	f9ea3d4d0f 	{ ae_lq32f.i	aeq2, a13, 0; ae_addq56	aeq1, aeq1, aeq2 }
    1e45:	600d64        	ae_lq32f.i	aeq0, a13, 24
    1e48:	fb7238be9f 	{ ae_sq32f.xu	aeq3, a14, a9; ae_addq56	aeq3, aeq2, aeq0 }
    1e4d:	f832f89eff 	{ ae_sq32f.xu	aeq1, a14, a15; ae_subq56	aeq0, aeq2, aeq0 }
    1e52:	62f894        	ae_sq32f.xu	aeq3, a8, a9
    1e55:	608d14        	ae_lq32f.i	aeq2, a13, 4
    1e58:	604d74        	ae_lq32f.i	aeq1, a13, 28
    1e5b:	fb763888ff 	{ ae_sq32f.xu	aeq0, a8, a15; ae_addq56	aeq3, aeq2, aeq1 }
    1e60:	f936f8be9f 	{ ae_sq32f.xu	aeq3, a14, a9; ae_subq56	aeq1, aeq2, aeq1 }
    1e65:	282192        	l32i	a9, a1, 160
    1e68:	2a2182        	l32i	a8, a1, 168
    1e6b:	62def4        	ae_sq32f.xu	aeq1, a14, a15
    1e6e:	2b21e2        	l32i	a14, a1, 172
    1e71:	989a           	add.n	a9, a8, a9
    1e73:	272182        	l32i	a8, a1, 156
    1e76:	661b           	addi.n	a6, a6, 1
    1e78:	558b           	addi.n	a5, a5, 8
    1e7a:	338a           	add.n	a3, a3, a8
    1e7c:	228a           	add.n	a2, a2, a8
    1e7e:	242182        	l32i	a8, a1, 144
    1e81:	ee8b           	addi.n	a14, a14, 8
    1e83:	256132        	s32i	a3, a1, 148
    1e86:	021867        	beq	a8, a6, 1e8c <FFT8N+0x380>
    1e89:	ff4046        	j	1b8e <FFT8N+0x82>
    1e8c:	000906        	j	1eb4 <FFT8N+0x3a8>

00001e8f <FFT8N+0x383>:
    1e8f:	00000000                                ....

00001e93 <FFT8N+0x387>:
    1e93:	232182        	l32i	a8, a1, 140
    1e96:	057d           	mov.n	a7, a5
    1e98:	730c           	movi.n	a3, 7
    1e9a:	601704        	ae_lq32f.iu	aeq0, a7, 0
    1e9d:	108376        	loop	a3, 1eb1 <FFT8N+0x3a5>
    1ea0:	d4e63d271f 	{ ae_lq32f.i	aeq1, a7, 4; ae_mulfq32sp16s.l	aeq0, aeq0, aep1 }
    1ea5:	031a54        	ae_mulfq32sp16s.l	aeq1, aeq1, aep1
    1ea8:	624814        	ae_sq32f.iu	aeq0, a8, 4
    1eab:	6037a4        	ae_lq32f.xu	aeq0, a7, a10
    1eae:	625814        	ae_sq32f.iu	aeq1, a8, 4

00001eb1 <FFT8N+0x3a5>:
    1eb1:	ff4e86        	j	1bef <FFT8N+0xe3>

00001eb4 <FFT8N+0x3a8>:
    1eb4:	f01d           	retw.n

00001eb6 <FFT8N+0x3aa>:
	...

00001eb8 <FFT12N>:
    1eb8:	020136        	entry	a1, 0x100
    1ebb:	6129           	s32i.n	a2, a1, 24
    1ebd:	412122        	l32i	a2, a1, 0x104
    1ec0:	3cc1f2        	addi	a15, a1, 60
    1ec3:	038d           	mov.n	a8, a3
    1ec5:	1135d0        	slli	a3, a5, 3
    1ec8:	7179           	s32i.n	a7, a1, 28
    1eca:	d149           	s32i.n	a4, a1, 52
    1ecc:	8199           	s32i.n	a9, a1, 32
    1ece:	c1f9           	s32i.n	a15, a1, 48
    1ed0:	9169           	s32i.n	a6, a1, 36
    1ed2:	2616a6        	blti	a6, 1, 1efc <FFT12N+0x44>
    1ed5:	c178           	l32i.n	a7, a1, 48
    1ed7:	c04230        	sub	a4, a2, a3
    1eda:	0b8676        	loop	a6, 1ee9 <FFT12N+0x31>
    1edd:	603434        	ae_lq32f.xu	aeq0, a4, a3
    1ee0:	624714        	ae_sq32f.iu	aeq0, a7, 4
    1ee3:	60c414        	ae_lq32f.i	aeq3, a4, 4
    1ee6:	627714        	ae_sq32f.iu	aeq3, a7, 4

00001ee9 <FFT12N+0x31>:
    1ee9:	0fa666        	bnei	a6, 12, 1efc <FFT12N+0x44>
    1eec:	f86a41        	l32r	a4, 94 (570 <fix_fft12>)
    1eef:	40c1a2        	addi	a10, a1, 64
    1ef2:	086d           	mov.n	a6, a8
    1ef4:	0004e0        	callx8	a4
    1ef7:	140c           	movi.n	a4, 1
    1ef9:	000446        	j	1f0e <FFT12N+0x56>

00001efc <FFT12N+0x44>:
    1efc:	f86741        	l32r	a4, 98 (370 <fix_fft6>)
    1eff:	44c1b2        	addi	a11, a1, 68
    1f02:	40c1a2        	addi	a10, a1, 64
    1f05:	2c0c           	movi.n	a12, 2
    1f07:	086d           	mov.n	a6, a8
    1f09:	0004e0        	callx8	a4
    1f0c:	040c           	movi.n	a4, 0
    1f0e:	91b8           	l32i.n	a11, a1, 36
    1f10:	40c1f2        	addi	a15, a1, 64
    1f13:	b1f9           	s32i.n	a15, a1, 44
    1f15:	a149           	s32i.n	a4, a1, 40
    1f17:	05ed           	mov.n	a14, a5
    1f19:	06fd           	mov.n	a15, a6
    1f1b:	291ba6        	blti	a11, 1, 1f48 <FFT12N+0x90>
    1f1e:	7168           	l32i.n	a6, a1, 28
    1f20:	b148           	l32i.n	a4, a1, 44
    1f22:	61d8           	l32i.n	a13, a1, 24
    1f24:	d15e60        	mul16s	a5, a14, a6
    1f27:	d166e0        	mul16s	a6, a6, a14
    1f2a:	1175e0        	slli	a7, a5, 2
    1f2d:	1156e0        	slli	a5, a6, 2
    1f30:	c06d70        	sub	a6, a13, a7
    1f33:	601404        	ae_lq32f.iu	aeq0, a4, 0
    1f36:	c07f70        	sub	a7, a15, a7
    1f39:	0b8b76        	loop	a11, 1f48 <FFT12N+0x90>
    1f3c:	605414        	ae_lq32f.iu	aeq1, a4, 4
    1f3f:	62c654        	ae_sq32f.xu	aeq0, a6, a5
    1f42:	62d754        	ae_sq32f.xu	aeq1, a7, a5
    1f45:	601414        	ae_lq32f.iu	aeq0, a4, 4

00001f48 <FFT12N+0x90>:
    1f48:	022ee6        	bgei	a14, 2, 1f4e <FFT12N+0x96>
    1f4b:	004486        	j	2061 <FFT12N+0x1a9>
    1f4e:	7158           	l32i.n	a5, a1, 28
    1f50:	117ee0        	slli	a7, a14, 2
    1f53:	490c           	movi.n	a9, 4
    1f55:	d28b           	addi.n	a13, a2, 8
    1f57:	c02970        	sub	a2, a9, a7
    1f5a:	822250        	mull	a2, a2, a5
    1f5d:	422162        	l32i	a6, a1, 0x108
    1f60:	8148           	l32i.n	a4, a1, 32
    1f62:	11a5e0        	slli	a10, a5, 2
    1f65:	6158           	l32i.n	a5, a1, 24
    1f67:	402182        	l32i	a8, a1, 0x100
    1f6a:	44c142        	addi	a4, a1, 68
    1f6d:	7f2a           	add.n	a7, a15, a2
    1f6f:	290c           	movi.n	a9, 2
    1f71:	d1f8           	l32i.n	a15, a1, 52
    1f73:	e149           	s32i.n	a4, a1, 56
    1f75:	81a9           	s32i.n	a10, a1, 32
    1f77:	824ae0        	mull	a4, a10, a14
    1f7a:	90ae90        	addx2	a10, a14, a9
    1f7d:	ce0b           	addi.n	a12, a14, -1
    1f7f:	552a           	add.n	a5, a5, a2
    1f81:	d1e8e0        	mul16s	a14, a8, a14
    1f84:	822a80        	mull	a2, a10, a8
    1f87:	1188f0        	slli	a8, a8, 1
    1f8a:	1166f0        	slli	a6, a6, 1
    1f8d:	f189           	s32i.n	a8, a1, 60
    1f8f:	c08f60        	sub	a8, a15, a6
    1f92:	116ef0        	slli	a6, a14, 1
    1f95:	282a           	add.n	a2, a8, a2
    1f97:	000ec6        	j	1fd6 <FFT12N+0x11e>

00001f9a <FFT12N+0xe2>:
    1f9a:	e1b8           	l32i.n	a11, a1, 56
    1f9c:	f83f81        	l32r	a8, 98 (370 <fix_fft6>)
    1f9f:	2c0c           	movi.n	a12, 2
    1fa1:	0008e0        	callx8	a8
    1fa4:	91b8           	l32i.n	a11, a1, 36
    1fa6:	61d8           	l32i.n	a13, a1, 24
    1fa8:	71c8           	l32i.n	a12, a1, 28
    1faa:	171ba6        	blti	a11, 1, 1fc5 <FFT12N+0x10d>
    1fad:	b188           	l32i.n	a8, a1, 44
    1faf:	079d           	mov.n	a9, a7
    1fb1:	05ad           	mov.n	a10, a5
    1fb3:	601804        	ae_lq32f.iu	aeq0, a8, 0
    1fb6:	0b8b76        	loop	a11, 1fc5 <FFT12N+0x10d>
    1fb9:	605814        	ae_lq32f.iu	aeq1, a8, 4
    1fbc:	62ca44        	ae_sq32f.xu	aeq0, a10, a4
    1fbf:	62d944        	ae_sq32f.xu	aeq1, a9, a4
    1fc2:	601814        	ae_lq32f.iu	aeq0, a8, 4

00001fc5 <FFT12N+0x10d>:
    1fc5:	81f8           	l32i.n	a15, a1, 32
    1fc7:	f188           	l32i.n	a8, a1, 60
    1fc9:	cc0b           	addi.n	a12, a12, -1
    1fcb:	dd8b           	addi.n	a13, a13, 8
    1fcd:	228a           	add.n	a2, a2, a8
    1fcf:	77fa           	add.n	a7, a7, a15
    1fd1:	55fa           	add.n	a5, a5, a15
    1fd3:	08ac16        	beqz	a12, 2061 <FFT12N+0x1a9>

00001fd6 <FFT12N+0x11e>:
    1fd6:	0d8d           	mov.n	a8, a13
    1fd8:	601804        	ae_lq32f.iu	aeq0, a8, 0
    1fdb:	604814        	ae_lq32f.i	aeq1, a8, 4
    1fde:	60f834        	ae_lq32f.xu	aeq3, a8, a3
    1fe1:	608814        	ae_lq32f.i	aeq2, a8, 4
    1fe4:	02ad           	mov.n	a10, a2
    1fe6:	632114        	ae_sq56s.i	aeq2, a1, 8
    1fe9:	0c2192        	l32i	a9, a1, 48
    1fec:	448a04        	ae_lp16x2f.iu	aep0, a10, 0
    1fef:	618114        	ae_lq56.i	aeq2, a1, 8
    1ff2:	6f02b9c91f 	{ ae_sq32f.iu	aeq0, a9, 4; ae_mulzsafq32sp16s.lh	aeq2, aeq2, aep0, aeq3, aep0 }
    1ff7:	625914        	ae_sq32f.iu	aeq1, a9, 4
    1ffa:	632124        	ae_sq56s.i	aeq2, a1, 16
    1ffd:	618114        	ae_lq56.i	aeq2, a1, 8
    2000:	0f033de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_mulzaafq32sp16s.lh	aeq2, aeq3, aep0, aeq2, aep0 }
    2005:	627914        	ae_sq32f.iu	aeq3, a9, 4
    2008:	603834        	ae_lq32f.xu	aeq0, a8, a3
    200b:	604814        	ae_lq32f.i	aeq1, a8, 4
    200e:	458a64        	ae_lp16x2f.xu	aep0, a10, a6
    2011:	626914        	ae_sq32f.iu	aeq2, a9, 4
    2014:	343ba6        	blti	a11, 3, 204c <FFT12N+0x194>
    2017:	ffcbb2        	addi	a11, a11, -1
    201a:	41b1b0        	srli	a11, a11, 1
    201d:	2b8b76        	loop	a11, 204c <FFT12N+0x194>
    2020:	6d017c483f 	{ ae_lq32f.xu	aeq2, a8, a3; ae_mulzsafq32sp16s.lh	aeq3, aeq1, aep0, aeq0, aep0 }
    2025:	0c00db9a6f 	{ ae_lp16x2f.xu	aep1, a10, a6; ae_mulzaafq32sp16s.lh	aeq1, aeq0, aep0, aeq1, aep0 }
    202a:	627914        	ae_sq32f.iu	aeq3, a9, 4
    202d:	631114        	ae_sq56s.i	aeq1, a1, 8
    2030:	604814        	ae_lq32f.i	aeq1, a8, 4
    2033:	61c114        	ae_lq56.i	aeq3, a1, 8
    2036:	6d2779f91f 	{ ae_sq32f.iu	aeq3, a9, 4; ae_mulzsafq32sp16s.lh	aeq3, aeq1, aep1, aeq2, aep1 }
    203b:	0f24bc083f 	{ ae_lq32f.xu	aeq0, a8, a3; ae_mulzaafq32sp16s.lh	aeq2, aeq2, aep1, aeq1, aep1 }
    2040:	627914        	ae_sq32f.iu	aeq3, a9, 4
    2043:	458a64        	ae_lp16x2f.xu	aep0, a10, a6
    2046:	604814        	ae_lq32f.i	aeq1, a8, 4
    2049:	626914        	ae_sq32f.iu	aeq2, a9, 4

0000204c <FFT12N+0x194>:
    204c:	a188           	l32i.n	a8, a1, 40
    204e:	40c1a2        	addi	a10, a1, 64
    2051:	71c9           	s32i.n	a12, a1, 28
    2053:	61d9           	s32i.n	a13, a1, 24
    2055:	f41816        	beqz	a8, 1f9a <FFT12N+0xe2>
    2058:	f80f81        	l32r	a8, 94 (570 <fix_fft12>)
    205b:	0008e0        	callx8	a8
    205e:	ffd086        	j	1fa4 <FFT12N+0xec>

00002061 <FFT12N+0x1a9>:
    2061:	f01d           	retw.n

00002063 <FFT12N+0x1ab>:
	...

00002064 <__do_global_ctors_aux>:
    2064:	004136        	entry	a1, 32
    2067:	f80d31        	l32r	a3, 9c (2384 <__CTOR_END__>)
    206a:	fcc322        	addi	a2, a3, -4
    206d:	0228           	l32i.n	a2, a2, 0
    206f:	f8c332        	addi	a3, a3, -8
    2072:	0a0226        	beqi	a2, -1, 2080 <__do_global_ctors_aux+0x1c>

00002075 <__do_global_ctors_aux+0x11>:
    2075:	0002e0        	callx8	a2
    2078:	0328           	l32i.n	a2, a3, 0
    207a:	fcc332        	addi	a3, a3, -4
    207d:	f40266        	bnei	a2, -1, 2075 <__do_global_ctors_aux+0x11>
    2080:	f01d           	retw.n

00002082 <__do_global_ctors_aux+0x1e>:
	...

00002084 <_fini>:
    2084:	008136        	entry	a1, 64
    2087:	f80681        	l32r	a8, a0 (bc <__do_global_dtors_aux>)
    208a:	f03d           	nop.n
    208c:	0008e0        	callx8	a8

0000208f <_fini+0xb>:
    208f:	f01d           	retw.n
