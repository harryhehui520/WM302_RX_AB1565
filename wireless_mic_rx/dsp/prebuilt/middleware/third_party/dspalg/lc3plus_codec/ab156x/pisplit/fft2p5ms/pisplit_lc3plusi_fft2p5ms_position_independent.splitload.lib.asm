
Build/fft2p5ms/pisplit_lc3plusi_fft2p5ms_position_independent.splitload.lib:     file format elf32-xtensa-le


Disassembly of section .text:

00000000 <_init-0x98>:
       0:	000000e4 00001ccc 000020dc 00000000     ......... ......
      10:	000020a4 00000000 000020c4 00002164     . ....... ..d!..
      20:	00002108 00000150 0000211b 00001348     .!..P....!..H...
      30:	00002127 00000c64 00002133 000015f0     '!..d...3!......
      40:	00002143 000017fc 00002153 000005f4     C!......S!......
      50:	000020f0 000023f8 b0000001 478dde64     . ...#......d..G
      60:	d18053ce 9d839db0 79bc3854 00000164     .S......T8.yd...
      70:	91261468 00001d48 5a82799a a57d8666     h.&.H....y.Zf.}.
      80:	00001d88 00001341 000015ee 000002ac     ....A...........
      90:	000020ac 000000b0                       . ......

00000098 <_init>:
      98:	008136        	entry	a1, 64
      9b:	ffd981        	l32r	a8, 0 (e4 <frame_dummy>)
      9e:	f03d           	nop.n
      a0:	0008e0        	callx8	a8
      a3:	ffd881        	l32r	a8, 4 (1ccc <__do_global_ctors_aux>)
      a6:	f03d           	nop.n
      a8:	0008e0        	callx8	a8
      ab:	f01d           	retw.n

000000ad <_init+0x15>:
      ad:	000000                                        ...

000000b0 <__do_global_dtors_aux>:
      b0:	004136        	entry	a1, 32
      b3:	ffd521        	l32r	a2, 8 (20dc <__do_global_dtors_aux.completed>)
      b6:	000232        	l8ui	a3, a2, 0
      b9:	23ec           	bnez.n	a3, df <__do_global_dtors_aux+0x2f>

000000bb <__do_global_dtors_aux+0xb>:
      bb:	1248           	l32i.n	a4, a2, 4
      bd:	0438           	l32i.n	a3, a4, 0
      bf:	444b           	addi.n	a4, a4, 4
      c1:	738c           	beqz.n	a3, cc <__do_global_dtors_aux+0x1c>
      c3:	1249           	s32i.n	a4, a2, 4
      c5:	0003e0        	callx8	a3
      c8:	fffbc6        	j	bb <__do_global_dtors_aux+0xb>

000000cb <__do_global_dtors_aux+0x1b>:
	...

000000cc <__do_global_dtors_aux+0x1c>:
      cc:	ffd031        	l32r	a3, c (0 <_text_start>)
      cf:	ffd0a1        	l32r	a10, 10 (20a4 <__FRAME_END__>)
      d2:	438c           	beqz.n	a3, da <__do_global_dtors_aux+0x2a>
      d4:	ffce81        	l32r	a8, c (0 <_text_start>)
      d7:	0008e0        	callx8	a8
      da:	130c           	movi.n	a3, 1
      dc:	004232        	s8i	a3, a2, 0
      df:	f01d           	retw.n

000000e1 <__do_global_dtors_aux+0x31>:
      e1:	000000                                        ...

000000e4 <frame_dummy>:
      e4:	004136        	entry	a1, 32
      e7:	ffcb21        	l32r	a2, 14 (0 <_text_start>)
      ea:	ffc9a1        	l32r	a10, 10 (20a4 <__FRAME_END__>)
      ed:	ffcab1        	l32r	a11, 18 (20c4 <frame_dummy.object>)
      f0:	428c           	beqz.n	a2, f8 <frame_dummy+0x14>
      f2:	ffc881        	l32r	a8, 14 (0 <_text_start>)
      f5:	0008e0        	callx8	a8

000000f8 <frame_dummy+0x14>:
      f8:	f01d           	retw.n

000000fa <frame_dummy+0x16>:
	...

000000fc <_start>:
      fc:	004136        	entry	a1, 32
      ff:	ffc731        	l32r	a3, 1c (2164 <printf_ptr>)
     102:	0228           	l32i.n	a2, a2, 0
     104:	ffc7a1        	l32r	a10, 20 (2108 <export_parameter_array+0x18>)
     107:	ffc7b1        	l32r	a11, 24 (150 <fix_fft_Init>)
     10a:	0329           	s32i.n	a2, a3, 0
     10c:	0002e0        	callx8	a2
     10f:	0328           	l32i.n	a2, a3, 0
     111:	ffc5a1        	l32r	a10, 28 (211b <export_parameter_array+0x2b>)
     114:	ffc6b1        	l32r	a11, 2c (1348 <FFT4N>)
     117:	0002e0        	callx8	a2
     11a:	0328           	l32i.n	a2, a3, 0
     11c:	ffc5a1        	l32r	a10, 30 (2127 <export_parameter_array+0x37>)
     11f:	ffc5b1        	l32r	a11, 34 (c64 <FFT8N>)
     122:	0002e0        	callx8	a2
     125:	0328           	l32i.n	a2, a3, 0
     127:	ffc4a1        	l32r	a10, 38 (2133 <export_parameter_array+0x43>)
     12a:	ffc4b1        	l32r	a11, 3c (15f0 <fix_fft15>)
     12d:	0002e0        	callx8	a2
     130:	0328           	l32i.n	a2, a3, 0
     132:	ffc3a1        	l32r	a10, 40 (2143 <export_parameter_array+0x53>)
     135:	ffc3b1        	l32r	a11, 44 (17fc <fix_fft20>)
     138:	0002e0        	callx8	a2
     13b:	0328           	l32i.n	a2, a3, 0
     13d:	ffc2a1        	l32r	a10, 48 (2153 <export_parameter_array+0x63>)
     140:	ffc3b1        	l32r	a11, 4c (5f4 <fix_fft40>)
     143:	0002e0        	callx8	a2
     146:	ffc221        	l32r	a2, 50 (20f0 <export_parameter_array>)
     149:	f01d           	retw.n

0000014b <_start+0x4f>:
     14b:	00000000                                 .....

00000150 <fix_fft_Init>:
     150:	004136        	entry	a1, 32
     153:	f8a032        	movi	a3, 248
     156:	ffbf41        	l32r	a4, 54 (23f8 <LC3Plus_RotVector_40_32>)
     159:	55d332        	addmi	a3, a3, 0x5500
     15c:	223a           	add.n	a2, a2, a3
     15e:	0429           	s32i.n	a2, a4, 0
     160:	f01d           	retw.n

00000162 <fix_fft_Init+0x12>:
	...

00000164 <fix_fft5_stage>:
     164:	008136        	entry	a1, 64
     167:	2468           	l32i.n	a6, a4, 8
     169:	8478           	l32i.n	a7, a4, 32
     16b:	4488           	l32i.n	a8, a4, 16
     16d:	6498           	l32i.n	a9, a4, 24
     16f:	025d           	mov.n	a5, a2
     171:	ffb921        	l32r	a2, 58 (b0000001 <_end+0xafffdbdd>)
     174:	04c8           	l32i.n	a12, a4, 0
     176:	7139           	s32i.n	a3, a1, 28
     178:	d76a           	add.n	a13, a7, a6
     17a:	c0a670        	sub	a10, a6, a7
     17d:	398a           	add.n	a3, a9, a8
     17f:	ffb761        	l32r	a6, 5c (478dde64 <_end+0x478dba40>)
     182:	fd3a           	add.n	a15, a13, a3
     184:	ffb771        	l32r	a7, 60 (d18053ce <_end+0xd1802faa>)
     187:	c0b890        	sub	a11, a8, a9
     18a:	9fca           	add.n	a9, a15, a12
     18c:	b2ef20        	mulsh	a14, a15, a2
     18f:	82ff20        	mull	a15, a15, a2
     192:	c02d30        	sub	a2, a13, a3
     195:	823260        	mull	a3, a2, a6
     198:	b28260        	mulsh	a8, a2, a6
     19b:	82db70        	mull	a13, a11, a7
     19e:	05cf30        	extui	a12, a3, 31, 1
     1a1:	b22b70        	mulsh	a2, a11, a7
     1a4:	9088c0        	addx2	a8, a8, a12
     1a7:	05cfd0        	extui	a12, a13, 31, 1
     1aa:	90d2c0        	addx2	a13, a2, a12
     1ad:	ffadc1        	l32r	a12, 64 (9d839db0 <_end+0x9d83798c>)
     1b0:	2aba           	add.n	a2, a10, a11
     1b2:	0599           	s32i.n	a9, a5, 0
     1b4:	823ac0        	mull	a3, a10, a12
     1b7:	b2aac0        	mulsh	a10, a10, a12
     1ba:	05bf30        	extui	a11, a3, 31, 1
     1bd:	11bbf0        	slli	a11, a11, 1
     1c0:	a0aab0        	addx4	a10, a10, a11
     1c3:	ffa9b1        	l32r	a11, 68 (79bc3854 <_end+0x79bc1430>)
     1c6:	8232b0        	mull	a3, a2, a11
     1c9:	b222b0        	mulsh	a2, a2, a11
     1cc:	053f30        	extui	a3, a3, 31, 1
     1cf:	902230        	addx2	a2, a2, a3
     1d2:	3a2a           	add.n	a3, a10, a2
     1d4:	05aff0        	extui	a10, a15, 31, 1
     1d7:	d2da           	add.n	a13, a2, a13
     1d9:	112af0        	slli	a2, a10, 1
     1dc:	360d34        	ae_cvtq48a32s	aeq0, a13
     1df:	a0ee20        	addx4	a14, a14, a2
     1e2:	05ad           	mov.n	a10, a5
     1e4:	54f8           	l32i.n	a15, a4, 20
     1e6:	7428           	l32i.n	a2, a4, 28
     1e8:	34d8           	l32i.n	a13, a4, 12
     1ea:	9458           	l32i.n	a5, a4, 36
     1ec:	6139           	s32i.n	a3, a1, 24
     1ee:	3e9a           	add.n	a3, a14, a9
     1f0:	e2fa           	add.n	a14, a2, a15
     1f2:	c02f20        	sub	a2, a15, a2
     1f5:	f5da           	add.n	a15, a5, a13
     1f7:	c09d50        	sub	a9, a13, a5
     1fa:	b2d9c0        	mulsh	a13, a9, a12
     1fd:	82c9c0        	mull	a12, a9, a12
     200:	b25270        	mulsh	a5, a2, a7
     203:	827270        	mull	a7, a2, a7
     206:	292a           	add.n	a2, a9, a2
     208:	c09fe0        	sub	a9, a15, a14
     20b:	efea           	add.n	a14, a15, a14
     20d:	c0f380        	sub	a15, a3, a8
     210:	338a           	add.n	a3, a3, a8
     212:	364334        	ae_cvtq48a32s	aeq1, a3
     215:	b23960        	mulsh	a3, a9, a6
     218:	826960        	mull	a6, a9, a6
     21b:	b292b0        	mulsh	a9, a2, a11
     21e:	8222b0        	mull	a2, a2, a11
     221:	ff8d81        	l32r	a8, 58 (b0000001 <_end+0xafffdbdd>)
     224:	14b8           	l32i.n	a11, a4, 4
     226:	057f70        	extui	a7, a7, 31, 1
     229:	052f20        	extui	a2, a2, 31, 1
     22c:	905570        	addx2	a5, a5, a7
     22f:	7178           	l32i.n	a7, a1, 28
     231:	902920        	addx2	a2, a9, a2
     234:	829e80        	mull	a9, a14, a8
     237:	525a           	add.n	a5, a2, a5
     239:	4eba           	add.n	a4, a14, a11
     23b:	05cfc0        	extui	a12, a12, 31, 1
     23e:	368534        	ae_cvtq48a32s	aeq2, a5
     241:	11bcf0        	slli	a11, a12, 1
     244:	fbea14074f 	{ s32i.n	a4, a7, 0; ae_addq56	aeq3, aeq1, aeq2 }
     249:	578b           	addi.n	a5, a7, 8
     24b:	7a8b           	addi.n	a7, a10, 8
     24d:	b2ae80        	mulsh	a10, a14, a8
     250:	059f90        	extui	a9, a9, 31, 1
     253:	a0bdb0        	addx4	a11, a13, a11
     256:	056f60        	extui	a6, a6, 31, 1
     259:	11d9f0        	slli	a13, a9, 1
     25c:	f9aad1336f 	{ addx2	a3, a3, a6; ae_subq56	aeq1, aeq1, aeq2 }
     261:	a06ad0        	addx4	a6, a10, a13
     264:	2b2a           	add.n	a2, a11, a2
     266:	627704        	ae_sq32f.iu	aeq3, a7, 0
     269:	e64a           	add.n	a14, a6, a4
     26b:	630124        	ae_sq56s.i	aeq0, a1, 16
     26e:	36cf34        	ae_cvtq48a32s	aeq3, a15
     271:	360234        	ae_cvtq48a32s	aeq0, a2
     274:	fa3af9d76f 	{ ae_sq32f.iu	aeq1, a7, 24; ae_subq56	aeq2, aeq3, aeq0 }
     279:	4e3a           	add.n	a4, a14, a3
     27b:	f87a39e7cf 	{ ae_sq32f.iu	aeq2, a7, -16; ae_addq56	aeq0, aeq3, aeq0 }
     280:	364434        	ae_cvtq48a32s	aeq1, a4
     283:	618124        	ae_lq56.i	aeq2, a1, 16
     286:	fbaaf061fe 	{ l32i	a15, a1, 24; ae_subq56	aeq3, aeq1, aeq2 }
     28b:	f9ea152e3f 	{ sub	a2, a14, a3; ae_addq56	aeq1, aeq1, aeq2 }
     290:	624724        	ae_sq32f.iu	aeq0, a7, 8
     293:	627504        	ae_sq32f.iu	aeq3, a5, 0
     296:	360f34        	ae_cvtq48a32s	aeq0, a15
     299:	368234        	ae_cvtq48a32s	aeq2, a2
     29c:	fb7239d56f 	{ ae_sq32f.iu	aeq1, a5, 24; ae_addq56	aeq3, aeq2, aeq0 }
     2a1:	f832f9f5cf 	{ ae_sq32f.iu	aeq3, a5, -16; ae_subq56	aeq0, aeq2, aeq0 }
     2a6:	624524        	ae_sq32f.iu	aeq0, a5, 8
     2a9:	f01d           	retw.n

000002ab <fix_fft5_stage+0x147>:
	...

000002ac <fix_fft15_stage>:
     2ac:	00c136        	entry	a1, 96
     2af:	ff6f71        	l32r	a7, 6c (164 <fix_fft5_stage>)
     2b2:	b44b           	addi.n	a11, a4, 4
     2b4:	04ad           	mov.n	a10, a4
     2b6:	04cd           	mov.n	a12, a4
     2b8:	28c462        	addi	a6, a4, 40
     2bb:	50c452        	addi	a5, a4, 80
     2be:	0007e0        	callx8	a7
     2c1:	2cc4b2        	addi	a11, a4, 44
     2c4:	06ad           	mov.n	a10, a6
     2c6:	06cd           	mov.n	a12, a6
     2c8:	0007e0        	callx8	a7
     2cb:	54c4b2        	addi	a11, a4, 84
     2ce:	05ad           	mov.n	a10, a5
     2d0:	05cd           	mov.n	a12, a5
     2d2:	0007e0        	callx8	a7
     2d5:	672c           	movi.n	a7, 38
     2d7:	91d772        	addmi	a7, a7, 0xffff9100
     2da:	ff6581        	l32r	a8, 70 (91261468 <_end+0x9125f044>)
     2dd:	600604        	ae_lq32f.i	aeq0, a6, 0
     2e0:	604504        	ae_lq32f.i	aeq1, a5, 0
     2e3:	fa6603c19e 	{ addi	a9, a1, 60; ae_addq56	aeq2, aeq0, aeq1 }
     2e8:	300874        	ae_cvtp24a16x2.ll	aep0, a8, a7
     2eb:	630144        	ae_sq56s.i	aeq0, a1, 32
     2ee:	460904        	ae_sp16x2f.i	aep0, a9, 0
     2f1:	352074        	ae_sraiq56	aeq0, aeq2, 1
     2f4:	60c404        	ae_lq32f.i	aeq3, a4, 0
     2f7:	fafa3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     2fc:	610144        	ae_lq56.i	aeq0, a1, 32
     2ff:	f826ff2bef 	{ ae_trunca32q48	a11, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     304:	440904        	ae_lp16x2f.i	aep0, a9, 0
     307:	d462fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     30c:	fe345402bf 	{ s32i.n	a11, a2, 0; ae_roundsq32asym	aeq2, aeq2 }
     311:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     316:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     31b:	608614        	ae_lq32f.i	aeq2, a6, 4
     31e:	fd6c7d651f 	{ ae_lq32f.i	aeq3, a5, 4; ae_truncq32	aeq1, aeq1 }
     323:	012bc4        	ae_addq56	aeq0, aeq2, aeq3
     326:	fab6fb00df 	{ ae_sraiq56	aeq3, aeq0, 1; ae_subq56	aeq2, aeq2, aeq3 }
     32b:	633134        	ae_sq56s.i	aeq3, a1, 24
     32e:	632154        	ae_sq56s.i	aeq2, a1, 40
     331:	608414        	ae_lq32f.i	aeq2, a4, 4
     334:	f8723de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_addq56	aeq0, aeq2, aeq0 }
     339:	fc3c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_roundsq32asym	aeq0, aeq3 }
     33e:	61c154        	ae_lq56.i	aeq3, a1, 40
     341:	d663ba016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_mulfq32sp16u.h	aeq0, aeq3, aep0 }
     346:	630134        	ae_sq56s.i	aeq0, a1, 24
     349:	610164        	ae_lq56.i	aeq0, a1, 48
     34c:	f832fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_subq56	aeq0, aeq2, aeq0 }
     351:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     354:	f783bde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq3, aep0 }
     359:	fb663f3cef 	{ ae_trunca32q48	a12, aeq3; ae_addq56	aeq3, aeq0, aeq1 }
     35e:	f826ff3def 	{ ae_trunca32q48	a13, aeq3; ae_subq56	aeq0, aeq0, aeq1 }
     363:	fe747f0eef 	{ ae_trunca32q48	a14, aeq0; ae_truncq32	aeq2, aeq2 }
     368:	610124        	ae_lq56.i	aeq0, a1, 16
     36b:	fba2d403cf 	{ s32i.n	a12, a3, 0; ae_subq56	aeq3, aeq0, aeq2 }
     370:	f9e23f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     375:	369a04        	ae_trunca32q48	a10, aeq1
     378:	1462f2        	s32i	a15, a2, 80
     37b:	a2a9           	s32i.n	a10, a2, 40
     37d:	1463d2        	s32i	a13, a3, 80
     380:	a3e9           	s32i.n	a14, a3, 40
     382:	60c624        	ae_lq32f.i	aeq3, a6, 8
     385:	604524        	ae_lq32f.i	aeq1, a5, 8
     388:	f87e3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     38d:	60c424        	ae_lq32f.i	aeq3, a4, 8
     390:	fa7a3b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_addq56	aeq2, aeq3, aeq0 }
     395:	fc247a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     39a:	618144        	ae_lq56.i	aeq2, a1, 32
     39d:	f936fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq1, aeq2, aeq1 }
     3a2:	d563bf2bef 	{ ae_trunca32q48	a11, aeq2; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     3a7:	630124        	ae_sq56s.i	aeq0, a1, 16
     3aa:	352434        	ae_sraiq56	aeq0, aeq2, 16
     3ad:	f483bdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     3b2:	fabad4c2bf 	{ s32i.n	a11, a2, 48; ae_subq56	aeq2, aeq3, aeq2 }
     3b7:	632124        	ae_sq56s.i	aeq2, a1, 16
     3ba:	608634        	ae_lq32f.i	aeq2, a6, 12
     3bd:	604534        	ae_lq32f.i	aeq1, a5, 12
     3c0:	fb763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq3, aeq2, aeq1 }
     3c5:	fa36fd043f 	{ ae_lq32f.i	aeq0, a4, 12; ae_subq56	aeq2, aeq2, aeq1 }
     3ca:	fbe63b305f 	{ ae_sraiq56	aeq1, aeq3, 1; ae_addq56	aeq3, aeq0, aeq3 }
     3cf:	d762fa314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     3d4:	631134        	ae_sq56s.i	aeq1, a1, 24
     3d7:	614134        	ae_lq56.i	aeq1, a1, 24
     3da:	fd2c7b34cf 	{ ae_sraiq56	aeq3, aeq3, 16; ae_roundsq32asym	aeq1, aeq1 }
     3df:	f782fdc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     3e4:	010dc4        	ae_subq56	aeq0, aeq0, aeq1
     3e7:	fd747dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_truncq32	aeq1, aeq2 }
     3ec:	fa663f2cef 	{ ae_trunca32q48	a12, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     3f1:	f826ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     3f6:	fd7c7dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_truncq32	aeq1, aeq3 }
     3fb:	fb36ff0eef 	{ ae_trunca32q48	a14, aeq0; ae_subq56	aeq3, aeq2, aeq1 }
     400:	f9763f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq2, aeq1 }
     405:	369a04        	ae_trunca32q48	a10, aeq1
     408:	c3c9           	s32i.n	a12, a3, 48
     40a:	22f9           	s32i.n	a15, a2, 8
     40c:	1662a2        	s32i	a10, a2, 88
     40f:	23d9           	s32i.n	a13, a3, 8
     411:	1663e2        	s32i	a14, a3, 88
     414:	600644        	ae_lq32f.i	aeq0, a6, 16
     417:	604544        	ae_lq32f.i	aeq1, a5, 16
     41a:	fa663d644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_addq56	aeq2, aeq0, aeq1 }
     41f:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     424:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     429:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     42e:	36ab04        	ae_trunca32q48	a11, aeq2
     431:	618144        	ae_lq56.i	aeq2, a1, 32
     434:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     439:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     43e:	1862b2        	s32i	a11, a2, 96
     441:	f482fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     446:	608654        	ae_lq32f.i	aeq2, a6, 20
     449:	600554        	ae_lq32f.i	aeq0, a5, 20
     44c:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     44f:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     454:	632134        	ae_sq56s.i	aeq2, a1, 24
     457:	630124        	ae_sq56s.i	aeq0, a1, 16
     45a:	600454        	ae_lq32f.i	aeq0, a4, 20
     45d:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     462:	ff347a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_roundsq32asym	aeq3, aeq2 }
     467:	618124        	ae_lq56.i	aeq2, a1, 16
     46a:	0382a4        	ae_mulfq32sp16u.h	aeq2, aeq2, aep0
     46d:	faa6fa216f 	{ ae_sq56s.i	aeq2, a1, 48; ae_subq56	aeq2, aeq0, aeq3 }
     472:	61c164        	ae_lq56.i	aeq3, a1, 48
     475:	353434        	ae_sraiq56	aeq0, aeq3, 16
     478:	61c124        	ae_lq56.i	aeq3, a1, 16
     47b:	f683ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulafq32sp16s.l	aeq0, aeq3, aep0 }
     480:	ff6c7da15f 	{ ae_lq56.i	aeq1, a1, 40; ae_truncq32	aeq3, aeq1 }
     485:	faf63f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq2, aeq2, aeq3 }
     48a:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     48f:	fa26ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq2, aeq0, aeq1 }
     494:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     499:	618134        	ae_lq56.i	aeq2, a1, 24
     49c:	f8b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq0, aeq2, aeq3 }
     4a1:	368904        	ae_trunca32q48	a9, aeq0
     4a4:	1863c2        	s32i	a12, a3, 96
     4a7:	e2e9           	s32i.n	a14, a2, 56
     4a9:	42f9           	s32i.n	a15, a2, 16
     4ab:	e3d9           	s32i.n	a13, a3, 56
     4ad:	4399           	s32i.n	a9, a3, 16
     4af:	60c664        	ae_lq32f.i	aeq3, a6, 24
     4b2:	608564        	ae_lq32f.i	aeq2, a5, 24
     4b5:	f9fa3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq1, aeq3, aeq2 }
     4ba:	60c464        	ae_lq32f.i	aeq3, a4, 24
     4bd:	f87e0704de 	{ addi	a13, a4, 112; ae_addq56	aeq0, aeq3, aeq1 }
     4c2:	630124        	ae_sq56s.i	aeq0, a1, 16
     4c5:	610144        	ae_lq56.i	aeq0, a1, 32
     4c8:	010ec4        	ae_subq56	aeq0, aeq0, aeq2
     4cb:	630134        	ae_sq56s.i	aeq0, a1, 24
     4ce:	351074        	ae_sraiq56	aeq0, aeq1, 1
     4d1:	fc247da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     4d6:	f83aff1aef 	{ ae_trunca32q48	a10, aeq1; ae_subq56	aeq0, aeq3, aeq0 }
     4db:	614134        	ae_lq56.i	aeq1, a1, 24
     4de:	d5639462af 	{ s32i.n	a10, a2, 24; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     4e3:	60c674        	ae_lq32f.i	aeq3, a6, 28
     4e6:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     4e9:	f583bd257f 	{ ae_lq32f.i	aeq1, a5, 28; ae_mulafq32sp16s.l	aeq2, aeq1, aep0 }
     4ee:	f87e3a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     4f3:	f93efd647f 	{ ae_lq32f.i	aeq3, a4, 28; ae_subq56	aeq1, aeq3, aeq1 }
     4f8:	631124        	ae_sq56s.i	aeq1, a1, 16
     4fb:	f87a3b005f 	{ ae_sraiq56	aeq1, aeq0, 1; ae_addq56	aeq0, aeq3, aeq0 }
     500:	631134        	ae_sq56s.i	aeq1, a1, 24
     503:	614134        	ae_lq56.i	aeq1, a1, 24
     506:	fc2c7a016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_roundsq32asym	aeq0, aeq1 }
     50b:	614124        	ae_lq56.i	aeq1, a1, 16
     50e:	030a64        	ae_mulfq32sp16u.h	aeq1, aeq1, aep0
     511:	f93afa115f 	{ ae_sq56s.i	aeq1, a1, 40; ae_subq56	aeq1, aeq3, aeq0 }
     516:	61c164        	ae_lq56.i	aeq3, a1, 48
     519:	ff747f3bef 	{ ae_trunca32q48	a11, aeq3; ae_truncq32	aeq3, aeq2 }
     51e:	618154        	ae_lq56.i	aeq2, a1, 40
     521:	faee3b240f 	{ ae_sraiq56	aeq0, aeq2, 16; ae_addq56	aeq2, aeq1, aeq3 }
     526:	631134        	ae_sq56s.i	aeq1, a1, 24
     529:	614124        	ae_lq56.i	aeq1, a1, 16
     52c:	f483bf2cef 	{ ae_trunca32q48	a12, aeq2; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     531:	63b9           	s32i.n	a11, a3, 24
     533:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     538:	018dc4        	ae_subq56	aeq2, aeq0, aeq1
     53b:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     540:	618134        	ae_lq56.i	aeq2, a1, 24
     543:	f9b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq1, aeq2, aeq3 }
     548:	369904        	ae_trunca32q48	a9, aeq1
     54b:	1a62e2        	s32i	a14, a2, 104
     54e:	1062f2        	s32i	a15, a2, 64
     551:	1a63c2        	s32i	a12, a3, 104
     554:	106392        	s32i	a9, a3, 64
     557:	6005e4        	ae_lq32f.i	aeq0, a5, -8
     55a:	604d04        	ae_lq32f.i	aeq1, a13, 0
     55d:	fa663d66ef 	{ ae_lq32f.i	aeq3, a6, -8; ae_addq56	aeq2, aeq0, aeq1 }
     562:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     567:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     56c:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     571:	36aa04        	ae_trunca32q48	a10, aeq2
     574:	618144        	ae_lq56.i	aeq2, a1, 32
     577:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     57c:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     581:	1262a2        	s32i	a10, a2, 72
     584:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     589:	6085f4        	ae_lq32f.i	aeq2, a5, -4
     58c:	fd6c7d0d1f 	{ ae_lq32f.i	aeq0, a13, 4; ae_truncq32	aeq1, aeq1 }
     591:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     594:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     599:	632134        	ae_sq56s.i	aeq2, a1, 24
     59c:	630154        	ae_sq56s.i	aeq0, a1, 40
     59f:	6006f4        	ae_lq32f.i	aeq0, a6, -4
     5a2:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     5a7:	ff347a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_roundsq32asym	aeq3, aeq2 }
     5ac:	618154        	ae_lq56.i	aeq2, a1, 40
     5af:	d762fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     5b4:	633164        	ae_sq56s.i	aeq3, a1, 48
     5b7:	61c134        	ae_lq56.i	aeq3, a1, 24
     5ba:	f8a6fde16f 	{ ae_lq56.i	aeq3, a1, 48; ae_subq56	aeq0, aeq0, aeq3 }
     5bf:	35f434        	ae_sraiq56	aeq3, aeq3, 16
     5c2:	f782fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     5c7:	fa663f2bef 	{ ae_trunca32q48	a11, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     5cc:	f826ff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     5d1:	fe7c7f0def 	{ ae_trunca32q48	a13, aeq0; ae_truncq32	aeq2, aeq3 }
     5d6:	610124        	ae_lq56.i	aeq0, a1, 16
     5d9:	01cec4        	ae_subq56	aeq3, aeq0, aeq2
     5dc:	f9e23f3eef 	{ ae_trunca32q48	a14, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     5e1:	369f04        	ae_trunca32q48	a15, aeq1
     5e4:	1263b2        	s32i	a11, a3, 72
     5e7:	82e9           	s32i.n	a14, a2, 32
     5e9:	1c62f2        	s32i	a15, a2, 112
     5ec:	83c9           	s32i.n	a12, a3, 32
     5ee:	1c63d2        	s32i	a13, a3, 112
     5f1:	f01d           	retw.n

000005f3 <fix_fft15_stage+0x347>:
	...

000005f4 <fix_fft40>:
     5f4:	034136        	entry	a1, 0x1a0
     5f7:	256122        	s32i	a2, a1, 148
     5fa:	fe9e21        	l32r	a2, 74 (1d48 <LC3Plus_lc3_scratch_push>)
     5fd:	40a1b2        	movi	a11, 0x140
     600:	05ad           	mov.n	a10, a5
     602:	326152        	s32i	a5, a1, 200
     605:	276132        	s32i	a3, a1, 156
     608:	045d           	mov.n	a5, a4
     60a:	0002e0        	callx8	a2
     60d:	fe9181        	l32r	a8, 54 (23f8 <LC3Plus_RotVector_40_32>)
     610:	1124e0        	slli	a2, a4, 2
     613:	2e6122        	s32i	a2, a1, 184
     616:	08f8           	l32i.n	a15, a8, 0
     618:	1124b0        	slli	a2, a4, 5
     61b:	2661a2        	s32i	a10, a1, 152
     61e:	fcca82        	addi	a8, a10, -4
     621:	2521a2        	l32i	a10, a1, 148
     624:	2e2142        	l32i	a4, a1, 184
     627:	830c           	movi.n	a3, 8
     629:	060c           	movi.n	a6, 0
     62b:	570c           	movi.n	a7, 5
     62d:	2461f2        	s32i	a15, a1, 144

00000630 <fix_fft40+0x3c>:
     630:	0a9d           	mov.n	a9, a10
     632:	603964        	ae_lq32f.xu	aeq0, a9, a6
     635:	0b8776        	loop	a7, 644 <fix_fft40+0x50>
     638:	624814        	ae_sq32f.iu	aeq0, a8, 4
     63b:	600914        	ae_lq32f.i	aeq0, a9, 4
     63e:	624814        	ae_sq32f.iu	aeq0, a8, 4
     641:	603924        	ae_lq32f.xu	aeq0, a9, a2

00000644 <fix_fft40+0x50>:
     644:	330b           	addi.n	a3, a3, -1
     646:	664a           	add.n	a6, a6, a4
     648:	fe4356        	bnez	a3, 630 <fix_fft40+0x3c>
     64b:	170c           	movi.n	a7, 1
     64d:	117750        	slli	a7, a7, 11
     650:	300774        	ae_cvtp24a16x2.ll	aep0, a7, a7
     653:	fe8621        	l32r	a2, 6c (164 <fix_fft5_stage>)
     656:	262172        	l32i	a7, a1, 152
     659:	830c           	movi.n	a3, 8
     65b:	50c142        	addi	a4, a1, 80
     65e:	560174        	ae_sp24x2s.i	aep0, a1, 56

00000661 <fix_fft40+0x6d>:
     661:	600704        	ae_lq32f.i	aeq0, a7, 0
     664:	540174        	ae_lp24x2.i	aep0, a1, 56
     667:	d5e2fd471f 	{ ae_lq32f.i	aeq2, a7, 4; ae_mulfq32sp16u.l	aeq3, aeq0, aep0 }
     66c:	d7e293844f 	{ or	a8, a4, a4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     671:	ff3c7d273f 	{ ae_lq32f.i	aeq1, a7, 12; ae_roundsq32asym	aeq3, aeq3 }
     676:	fe3479f80f 	{ ae_sq32f.iu	aeq3, a8, 0; ae_roundsq32asym	aeq2, aeq2 }
     67b:	60c744        	ae_lq32f.i	aeq3, a7, 16
     67e:	600724        	ae_lq32f.i	aeq0, a7, 8
     681:	d4e2ba112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     686:	633134        	ae_sq56s.i	aeq3, a1, 24
     689:	fc247de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     68e:	d7e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     693:	618134        	ae_lq56.i	aeq2, a1, 24
     696:	d7e28047be 	{ addi	a11, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     69b:	ff3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq3 }
     6a0:	0bad           	mov.n	a10, a11
     6a2:	632124        	ae_sq56s.i	aeq2, a1, 16
     6a5:	079d           	mov.n	a9, a7
     6a7:	604754        	ae_lq32f.i	aeq1, a7, 20
     6aa:	d4e3fd1a6f 	{ ae_lq32f.iu	aeq0, a10, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     6af:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6b2:	fd2c7de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq1, aeq1 }
     6b7:	ff3c7d596f 	{ ae_lq32f.iu	aeq2, a9, 24; ae_roundsq32asym	aeq3, aeq3 }
     6bc:	d7e2ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     6c1:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6c4:	fe347de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq2, aeq2 }
     6c9:	d7e3fd092f 	{ ae_lq32f.i	aeq0, a9, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     6ce:	d4e2b9d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     6d3:	ff3c7d2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_roundsq32asym	aeq3, aeq3 }
     6d8:	d4e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     6dd:	fc2479f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq0, aeq0 }
     6e2:	ff2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq1 }
     6e7:	07ad           	mov.n	a10, a7
     6e9:	04cd           	mov.n	a12, a4
     6eb:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6ee:	0002e0        	callx8	a2
     6f1:	330b           	addi.n	a3, a3, -1
     6f3:	28c772        	addi	a7, a7, 40
     6f6:	f67356        	bnez	a3, 661 <fix_fft40+0x6d>
     6f9:	242162        	l32i	a6, a1, 144
     6fc:	a0f550        	addx4	a15, a5, a5
     6ff:	2a6142        	s32i	a4, a1, 168
     702:	8f4d           	ae_sext16	a4, a15
     704:	f8c692        	addi	a9, a6, -8
     707:	252162        	l32i	a6, a1, 148
     70a:	82a032        	movi	a3, 130
     70d:	7da082        	movi	a8, 125
     710:	2721f2        	l32i	a15, a1, 156
     713:	f05440        	subx8	a5, a4, a4
     716:	fe5821        	l32r	a2, 78 (5a82799a <_end+0x5a825576>)
     719:	5ad332        	addmi	a3, a3, 0x5a00
     71c:	fe5871        	l32r	a7, 7c (a57d8666 <_end+0xa57d6242>)
     71f:	a5d882        	addmi	a8, a8, 0xffffa500
     722:	a0b440        	addx4	a11, a4, a4
     725:	90c440        	addx2	a12, a4, a4
     728:	1155e0        	slli	a5, a5, 2
     72b:	301874        	ae_cvtp24a16x2.ll	aep1, a8, a7
     72e:	300324        	ae_cvtp24a16x2.ll	aep0, a3, a2
     731:	1184c0        	slli	a8, a4, 4
     734:	b0a460        	addx8	a10, a4, a6
     737:	113be0        	slli	a3, a11, 2
     73a:	11bcd0        	slli	a11, a12, 3
     73d:	765a           	add.n	a7, a6, a5
     73f:	11cce0        	slli	a12, a12, 2
     742:	3161a2        	s32i	a10, a1, 196
     745:	af8a           	add.n	a10, a15, a8
     747:	268a           	add.n	a2, a6, a8
     749:	2f6172        	s32i	a7, a1, 188
     74c:	7fca           	add.n	a7, a15, a12
     74e:	3061a2        	s32i	a10, a1, 192
     751:	246122        	s32i	a2, a1, 144
     754:	8f5a           	add.n	a8, a15, a5
     756:	2d6172        	s32i	a7, a1, 180
     759:	56ca           	add.n	a5, a6, a12
     75b:	afba           	add.n	a10, a15, a11
     75d:	26ba           	add.n	a2, a6, a11
     75f:	c63a           	add.n	a12, a6, a3
     761:	01d172        	addmi	a7, a1, 0x100
     764:	bf3a           	add.n	a11, a15, a3
     766:	2c61a2        	s32i	a10, a1, 176
     769:	296122        	s32i	a2, a1, 164
     76c:	60c722        	addi	a2, a7, 96
     76f:	2861c2        	s32i	a12, a1, 160
     772:	2621c2        	l32i	a12, a1, 152
     775:	01d1a2        	addmi	a10, a1, 0x100
     778:	2b61b2        	s32i	a11, a1, 172
     77b:	386122        	s32i	a2, a1, 224
     77e:	20ca22        	addi	a2, a10, 32
     781:	a0d4f0        	addx4	a13, a4, a15
     784:	b0e4f0        	addx8	a14, a4, a15
     787:	a04460        	addx4	a4, a4, a6
     78a:	01d1b2        	addmi	a11, a1, 0x100
     78d:	e149           	s32i.n	a4, a1, 56
     78f:	54c132        	addi	a3, a1, 84
     792:	58c142        	addi	a4, a1, 88
     795:	70c162        	addi	a6, a1, 112
     798:	366122        	s32i	a2, a1, 216
     79b:	30cb22        	addi	a2, a11, 48
     79e:	346132        	s32i	a3, a1, 208
     7a1:	336142        	s32i	a4, a1, 204
     7a4:	376162        	s32i	a6, a1, 220
     7a7:	356122        	s32i	a2, a1, 212
     7aa:	28ccc2        	addi	a12, a12, 40
     7ad:	570c           	movi.n	a7, 5
     7af:	8a2c           	movi.n	a10, 40
     7b1:	0b2c           	movi.n	a11, 32
     7b3:	011346        	j	c04 <fix_fft40+0x610>

000007b6 <fix_fft40+0x1c2>:
	...

000007b7 <fix_fft40+0x1c3>:
     7b7:	093d           	mov.n	a3, a9
     7b9:	342142        	l32i	a4, a1, 208
     7bc:	2a2162        	l32i	a6, a1, 168
     7bf:	44a304        	ae_lp16x2f.iu	aep2, a3, 0
     7c2:	720c           	movi.n	a2, 7
     7c4:	60cc04        	ae_lq32f.i	aeq3, a12, 0
     7c7:	604c14        	ae_lq32f.i	aeq1, a12, 4
     7ca:	443314        	ae_lp16x2f.i	aep3, a3, 4
     7cd:	5c8276        	loop	a2, 82d <fix_fft40+0x239>
     7d0:	03a2e4        	ae_mulfq32sp16u.h	aeq2, aeq3, aep2
     7d3:	0332e4        	ae_mulfq32sp16u.h	aeq0, aeq3, aep3
     7d6:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     7d9:	f78bbb040f 	{ ae_sraiq56	aeq0, aeq0, 16; ae_mulafq32sp16s.l	aeq2, aeq3, aep2 }
     7de:	0330d4        	ae_mulafq32sp16s.l	aeq0, aeq3, aep3
     7e1:	d56fba212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq2, aeq1, aep3 }
     7e6:	630134        	ae_sq56s.i	aeq0, a1, 24
     7e9:	d56bba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16u.h	aeq2, aeq1, aep2 }
     7ee:	632144        	ae_sq56s.i	aeq2, a1, 32
     7f1:	618154        	ae_lq56.i	aeq2, a1, 40
     7f4:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     7f7:	f58fbde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq1, aep3 }
     7fc:	353434        	ae_sraiq56	aeq0, aeq3, 16
     7ff:	f48bbda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep2 }
     804:	f9ea3dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq1, aeq1, aeq2 }
     809:	f8a2fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     80e:	618124        	ae_lq56.i	aeq2, a1, 16
     811:	35a074        	ae_sraiq56	aeq2, aeq2, 1
     814:	fe347b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_roundsq32asym	aeq2, aeq2 }
     819:	fc245ba3bf 	{ ae_lp16x2f.xu	aep2, a3, a11; ae_roundsq32asym	aeq0, aeq0 }
     81e:	626414        	ae_sq32f.iu	aeq2, a4, 4
     821:	60fca4        	ae_lq32f.xu	aeq3, a12, a10
     824:	604c14        	ae_lq32f.i	aeq1, a12, 4
     827:	443314        	ae_lp16x2f.i	aep3, a3, 4
     82a:	624414        	ae_sq32f.iu	aeq0, a4, 4

0000082d <fix_fft40+0x239>:
     82d:	372172        	l32i	a7, a1, 220
     830:	600624        	ae_lq32f.i	aeq0, a6, 8
     833:	630124        	ae_sq56s.i	aeq0, a1, 16
     836:	60c724        	ae_lq32f.i	aeq3, a7, 8
     839:	633134        	ae_sq56s.i	aeq3, a1, 24
     83c:	604734        	ae_lq32f.i	aeq1, a7, 12
     83f:	608604        	ae_lq32f.i	aeq2, a6, 0
     842:	631144        	ae_sq56s.i	aeq1, a1, 32
     845:	632154        	ae_sq56s.i	aeq2, a1, 40
     848:	618124        	ae_lq56.i	aeq2, a1, 16
     84b:	614134        	ae_lq56.i	aeq1, a1, 24
     84e:	fa36fd663f 	{ ae_lq32f.i	aeq3, a6, 12; ae_subq56	aeq2, aeq2, aeq1 }
     853:	614144        	ae_lq56.i	aeq1, a1, 32
     856:	01d142        	addmi	a4, a1, 0x100
     859:	f93ec7812e 	{ addi	a2, a1, 120; ae_subq56	aeq1, aeq3, aeq1 }
     85e:	40c442        	addi	a4, a4, 64
     861:	6312a4        	ae_sq56s.i	aeq1, a2, -48
     864:	600704        	ae_lq32f.i	aeq0, a7, 0
     867:	614154        	ae_lq56.i	aeq1, a1, 40
     86a:	fa6a39a46f 	{ ae_sq32f.i	aeq2, a4, 24; ae_addq56	aeq2, aeq1, aeq0 }
     86f:	f82afda2af 	{ ae_lq56.i	aeq1, a2, -48; ae_subq56	aeq0, aeq1, aeq0 }
     874:	630164        	ae_sq56s.i	aeq0, a1, 48
     877:	3520b4        	ae_sraiq56	aeq0, aeq2, 2
     87a:	fd2479947f 	{ ae_sq32f.i	aeq1, a4, 28; ae_roundsq32asym	aeq1, aeq0 }
     87f:	608614        	ae_lq32f.i	aeq2, a6, 4
     882:	600714        	ae_lq32f.i	aeq0, a7, 4
     885:	f97239940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_addq56	aeq1, aeq2, aeq0 }
     88a:	f832fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_subq56	aeq0, aeq2, aeq0 }
     88f:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
     892:	630154        	ae_sq56s.i	aeq0, a1, 40
     895:	fe2c7b202f 	{ ae_sraiq56	aeq0, aeq2, 2; ae_roundsq32asym	aeq2, aeq1 }
     89a:	fc2479a41f 	{ ae_sq32f.i	aeq2, a4, 4; ae_roundsq32asym	aeq0, aeq0 }
     89f:	614124        	ae_lq56.i	aeq1, a1, 16
     8a2:	618134        	ae_lq56.i	aeq2, a1, 24
     8a5:	f9ea3dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_addq56	aeq1, aeq1, aeq2 }
     8aa:	fbfa3dc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_addq56	aeq3, aeq3, aeq2 }
     8af:	35a0b4        	ae_sraiq56	aeq2, aeq2, 2
     8b2:	fe347b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq2 }
     8b7:	ff3c79842f 	{ ae_sq32f.i	aeq0, a4, 8; ae_roundsq32asym	aeq3, aeq3 }
     8bc:	622434        	ae_sq32f.i	aeq2, a4, 12
     8bf:	600644        	ae_lq32f.i	aeq0, a6, 16
     8c2:	608744        	ae_lq32f.i	aeq2, a7, 16
     8c5:	fbe239b45f 	{ ae_sq32f.i	aeq3, a4, 20; ae_addq56	aeq3, aeq0, aeq2 }
     8ca:	faa2fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq2, aeq0, aeq2 }
     8cf:	fd2c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq1, aeq1 }
     8d4:	632134        	ae_sq56s.i	aeq2, a1, 24
     8d7:	608664        	ae_lq32f.i	aeq2, a6, 24
     8da:	3821d2        	l32i	a13, a1, 224
     8dd:	632124        	ae_sq56s.i	aeq2, a1, 16
     8e0:	618134        	ae_lq56.i	aeq2, a1, 24
     8e3:	fe3479944f 	{ ae_sq32f.i	aeq1, a4, 16; ae_roundsq32asym	aeq2, aeq2 }
     8e8:	604654        	ae_lq32f.i	aeq1, a6, 20
     8eb:	600754        	ae_lq32f.i	aeq0, a7, 20
     8ee:	fa6a39ad2f 	{ ae_sq32f.i	aeq2, a13, 8; ae_addq56	aeq2, aeq1, aeq0 }
     8f3:	f82afb30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_subq56	aeq0, aeq1, aeq0 }
     8f8:	ff3c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq3, aeq3 }
     8fd:	fe347b002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_roundsq32asym	aeq2, aeq2 }
     902:	fc2479bd0f 	{ ae_sq32f.i	aeq3, a13, 0; ae_roundsq32asym	aeq0, aeq0 }
     907:	60c764        	ae_lq32f.i	aeq3, a7, 24
     90a:	fd1c79ad1f 	{ ae_sq32f.i	aeq2, a13, 4; ae_movq56	aeq1, aeq3 }
     90f:	608674        	ae_lq32f.i	aeq2, a6, 28
     912:	630154        	ae_sq56s.i	aeq0, a1, 40
     915:	610124        	ae_lq56.i	aeq0, a1, 16
     918:	fbe63a214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_addq56	aeq3, aeq0, aeq3 }
     91d:	f826fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq0, aeq0, aeq1 }
     922:	61c154        	ae_lq56.i	aeq3, a1, 40
     925:	608774        	ae_lq32f.i	aeq2, a7, 28
     928:	614144        	ae_lq56.i	aeq1, a1, 32
     92b:	f8aafa012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_subq56	aeq0, aeq1, aeq2 }
     930:	fbea39bd3f 	{ ae_sq32f.i	aeq3, a13, 12; ae_addq56	aeq3, aeq1, aeq2 }
     935:	618134        	ae_lq56.i	aeq2, a1, 24
     938:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     93b:	fe2c7b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq1 }
     940:	fe3c79ad4f 	{ ae_sq32f.i	aeq2, a13, 16; ae_roundsq32asym	aeq2, aeq3 }
     945:	61c124        	ae_lq56.i	aeq3, a1, 16
     948:	622d54        	ae_sq32f.i	aeq2, a13, 20
     94b:	620d74        	ae_sq32f.i	aeq0, a13, 28
     94e:	623d64        	ae_sq32f.i	aeq3, a13, 24
     951:	600d04        	ae_lq32f.i	aeq0, a13, 0
     954:	604404        	ae_lq32f.i	aeq1, a4, 0
     957:	fb6a3d4d1f 	{ ae_lq32f.i	aeq2, a13, 4; ae_addq56	aeq3, aeq1, aeq0 }
     95c:	01d132        	addmi	a3, a1, 0x100
     95f:	f92afd0d3f 	{ ae_lq32f.i	aeq0, a13, 12; ae_subq56	aeq1, aeq1, aeq0 }
     964:	623304        	ae_sq32f.i	aeq3, a3, 0
     967:	630124        	ae_sq56s.i	aeq0, a1, 16
     96a:	60c414        	ae_lq32f.i	aeq3, a4, 4
     96d:	f8fa3361ae 	{ l32i	a10, a1, 216; ae_addq56	aeq0, aeq3, aeq2 }
     972:	fabaf9934f 	{ ae_sq32f.i	aeq1, a3, 16; ae_subq56	aeq2, aeq3, aeq2 }
     977:	604424        	ae_lq32f.i	aeq1, a4, 8
     97a:	61c124        	ae_lq56.i	aeq3, a1, 16
     97d:	faaef9a35f 	{ ae_sq32f.i	aeq2, a3, 20; ae_subq56	aeq2, aeq1, aeq3 }
     982:	f9ee39831f 	{ ae_sq32f.i	aeq0, a3, 4; ae_addq56	aeq1, aeq1, aeq3 }
     987:	622a04        	ae_sq32f.i	aeq2, a10, 0
     98a:	60c434        	ae_lq32f.i	aeq3, a4, 12
     98d:	608d24        	ae_lq32f.i	aeq2, a13, 8
     990:	f9fa399a2f 	{ ae_sq32f.i	aeq1, a10, 8; ae_addq56	aeq1, aeq3, aeq2 }
     995:	fabafd046f 	{ ae_lq32f.i	aeq0, a4, 24; ae_subq56	aeq2, aeq3, aeq2 }
     99a:	60cd64        	ae_lq32f.i	aeq3, a13, 24
     99d:	fae63a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_addq56	aeq2, aeq0, aeq3 }
     9a2:	fba6f99a1f 	{ ae_sq32f.i	aeq1, a10, 4; ae_subq56	aeq3, aeq0, aeq3 }
     9a7:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     9aa:	fe2c7d2d5f 	{ ae_lq32f.i	aeq1, a13, 20; ae_roundsq32asym	aeq2, aeq1 }
     9af:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
     9b2:	fd3c7a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq1, aeq3 }
     9b7:	600d44        	ae_lq32f.i	aeq0, a13, 16
     9ba:	621424        	ae_sq32f.i	aeq1, a4, 8
     9bd:	622414        	ae_sq32f.i	aeq2, a4, 4
     9c0:	614124        	ae_lq56.i	aeq1, a1, 16
     9c3:	608d74        	ae_lq32f.i	aeq2, a13, 28
     9c6:	60c474        	ae_lq32f.i	aeq3, a4, 28
     9c9:	f9fa399a3f 	{ ae_sq32f.i	aeq1, a10, 12; ae_addq56	aeq1, aeq3, aeq2 }
     9ce:	fabafd644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_subq56	aeq2, aeq3, aeq2 }
     9d3:	fa7a3a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_addq56	aeq2, aeq3, aeq0 }
     9d8:	f83afb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq3, aeq0 }
     9dd:	fd2c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq1, aeq1 }
     9e2:	630124        	ae_sq56s.i	aeq0, a1, 16
     9e5:	3530b4        	ae_sraiq56	aeq0, aeq3, 2
     9e8:	ff2479940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_roundsq32asym	aeq3, aeq0 }
     9ed:	600454        	ae_lq32f.i	aeq0, a4, 20
     9f0:	614144        	ae_lq56.i	aeq1, a1, 32
     9f3:	622324        	ae_sq32f.i	aeq2, a3, 8
     9f6:	fb6639b43f 	{ ae_sq32f.i	aeq3, a4, 12; ae_addq56	aeq3, aeq0, aeq1 }
     9fb:	f82afd440f 	{ ae_lq32f.i	aeq2, a4, 0; ae_subq56	aeq0, aeq1, aeq0 }
     a00:	632154        	ae_sq56s.i	aeq2, a1, 40
     a03:	633134        	ae_sq56s.i	aeq3, a1, 24
     a06:	60c424        	ae_lq32f.i	aeq3, a4, 8
     a09:	fd1c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_movq56	aeq1, aeq3 }
     a0e:	610154        	ae_lq56.i	aeq0, a1, 40
     a11:	fbe63d443f 	{ ae_lq32f.i	aeq2, a4, 12; ae_addq56	aeq3, aeq0, aeq3 }
     a16:	f826fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_subq56	aeq0, aeq0, aeq1 }
     a1b:	614124        	ae_lq56.i	aeq1, a1, 16
     a1e:	608414        	ae_lq32f.i	aeq2, a4, 4
     a21:	621374        	ae_sq32f.i	aeq1, a3, 28
     a24:	614294        	ae_lq56.i	aeq1, a2, -56
     a27:	fbaafa32af 	{ ae_sq56s.i	aeq3, a2, -48; ae_subq56	aeq3, aeq1, aeq2 }
     a2c:	fa763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq2, aeq2, aeq1 }
     a31:	610134        	ae_lq56.i	aeq0, a1, 24
     a34:	633124        	ae_sq56s.i	aeq3, a1, 16
     a37:	61c2a4        	ae_lq56.i	aeq3, a2, -48
     a3a:	d6e3b9833f 	{ ae_sq32f.i	aeq0, a3, 12; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
     a3f:	614144        	ae_lq56.i	aeq1, a1, 32
     a42:	630164        	ae_sq56s.i	aeq0, a1, 48
     a45:	610154        	ae_lq56.i	aeq0, a1, 40
     a48:	d5e2ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
     a4d:	621364        	ae_sq32f.i	aeq1, a3, 24
     a50:	614124        	ae_lq56.i	aeq1, a1, 16
     a53:	d4e3fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     a58:	618164        	ae_lq56.i	aeq2, a1, 48
     a5b:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a5e:	f703ba116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_mulafq32sp16s.h	aeq2, aeq3, aep0 }
     a63:	61c164        	ae_lq56.i	aeq3, a1, 48
     a66:	357434        	ae_sraiq56	aeq1, aeq3, 16
     a69:	61c134        	ae_lq56.i	aeq3, a1, 24
     a6c:	d7e7fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep1 }
     a71:	618294        	ae_lq56.i	aeq2, a2, -56
     a74:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a77:	f502b351fe 	{ l32i	a15, a1, 212; ae_mulafq32sp16s.h	aeq2, aeq0, aep0 }
     a7c:	353434        	ae_sraiq56	aeq0, aeq3, 16
     a7f:	61c124        	ae_lq56.i	aeq3, a1, 16
     a82:	f603fde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.h	aeq1, aeq3, aep0 }
     a87:	623f04        	ae_sq32f.i	aeq3, a15, 0
     a8a:	61c134        	ae_lq56.i	aeq3, a1, 24
     a8d:	f607b9af2f 	{ ae_sq32f.i	aeq2, a15, 8; ae_mulafq32sp16s.h	aeq0, aeq3, aep1 }
     a92:	621f14        	ae_sq32f.i	aeq1, a15, 4
     a95:	620f34        	ae_sq32f.i	aeq0, a15, 12
     a98:	604304        	ae_lq32f.i	aeq1, a3, 0
     a9b:	608324        	ae_lq32f.i	aeq2, a3, 8
     a9e:	fbea3251be 	{ l32i	a11, a1, 148; ae_addq56	aeq3, aeq1, aeq2 }
     aa3:	faaafa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq2, aeq1, aeq2 }
     aa8:	2421f2        	l32i	a15, a1, 144
     aab:	614124        	ae_lq56.i	aeq1, a1, 16
     aae:	369204        	ae_trunca32q48	a2, aeq1
     ab1:	60c314        	ae_lq32f.i	aeq3, a3, 4
     ab4:	600334        	ae_lq32f.i	aeq0, a3, 12
     ab7:	fa7a3f26ef 	{ ae_trunca32q48	a6, aeq2; ae_addq56	aeq2, aeq3, aeq0 }
     abc:	0b29           	s32i.n	a2, a11, 0
     abe:	0f69           	s32i.n	a6, a15, 0
     ac0:	f83afd2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_subq56	aeq0, aeq3, aeq0 }
     ac5:	60ca44        	ae_lq32f.i	aeq3, a10, 16
     ac8:	2721f2        	l32i	a15, a1, 156
     acb:	302122        	l32i	a2, a1, 192
     ace:	e148           	l32i.n	a4, a1, 56
     ad0:	36ac04        	ae_trunca32q48	a12, aeq2
     ad3:	f8ee3f08ef 	{ ae_trunca32q48	a8, aeq0; ae_addq56	aeq0, aeq1, aeq3 }
     ad8:	f9aefd4a3f 	{ ae_lq32f.i	aeq2, a10, 12; ae_subq56	aeq1, aeq1, aeq3 }
     add:	60ca54        	ae_lq32f.i	aeq3, a10, 20
     ae0:	f8f63f07ef 	{ ae_trunca32q48	a7, aeq0; ae_addq56	aeq0, aeq2, aeq3 }
     ae5:	fab6ff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq2, aeq2, aeq3 }
     aea:	36ae04        	ae_trunca32q48	a14, aeq2
     aed:	0fc9           	s32i.n	a12, a15, 0
     aef:	0289           	s32i.n	a8, a2, 0
     af1:	0479           	s32i.n	a7, a4, 0
     af3:	600344        	ae_lq32f.i	aeq0, a3, 16
     af6:	608364        	ae_lq32f.i	aeq2, a3, 24
     af9:	282162        	l32i	a6, a1, 160
     afc:	3e2172        	l32i	a7, a1, 248
     aff:	fd047f19ef 	{ ae_trunca32q48	a9, aeq1; ae_movq56	aeq1, aeq0 }
     b04:	f8a2fd635f 	{ ae_lq32f.i	aeq3, a3, 20; ae_subq56	aeq0, aeq0, aeq2 }
     b09:	f9ea3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq1, aeq1, aeq2 }
     b0e:	0699           	s32i.n	a9, a6, 0
     b10:	633134        	ae_sq56s.i	aeq3, a1, 24
     b13:	60c374        	ae_lq32f.i	aeq3, a3, 28
     b16:	07d9           	s32i.n	a13, a7, 0
     b18:	07dd           	mov.n	a13, a7
     b1a:	610124        	ae_lq56.i	aeq0, a1, 16
     b1d:	608a04        	ae_lq32f.i	aeq2, a10, 0
     b20:	2b21b2        	l32i	a11, a1, 172
     b23:	312162        	l32i	a6, a1, 196
     b26:	292172        	l32i	a7, a1, 164
     b29:	fc1c7f08ef 	{ ae_trunca32q48	a8, aeq0; ae_movq56	aeq0, aeq3 }
     b2e:	632144        	ae_sq56s.i	aeq2, a1, 32
     b31:	618134        	ae_lq56.i	aeq2, a1, 24
     b34:	fbb6ff19ef 	{ ae_trunca32q48	a9, aeq1; ae_subq56	aeq3, aeq2, aeq3 }
     b39:	fa723d2a6f 	{ ae_lq32f.i	aeq1, a10, 24; ae_addq56	aeq2, aeq2, aeq0 }
     b3e:	610144        	ae_lq56.i	aeq0, a1, 32
     b41:	0be9           	s32i.n	a14, a11, 0
     b43:	633124        	ae_sq56s.i	aeq3, a1, 16
     b46:	0689           	s32i.n	a8, a6, 0
     b48:	0799           	s32i.n	a9, a7, 0
     b4a:	fe0c7f29ef 	{ ae_trunca32q48	a9, aeq2; ae_movq56	aeq2, aeq1 }
     b4f:	f96633d1ee 	{ l32i	a14, a1, 244; ae_addq56	aeq1, aeq0, aeq1 }
     b54:	f8a2fde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     b59:	631124        	ae_sq56s.i	aeq1, a1, 16
     b5c:	2c2142        	l32i	a4, a1, 176
     b5f:	36bc04        	ae_trunca32q48	a12, aeq3
     b62:	60ca14        	ae_lq32f.i	aeq3, a10, 4
     b65:	614124        	ae_lq56.i	aeq1, a1, 16
     b68:	633134        	ae_sq56s.i	aeq3, a1, 24
     b6b:	0ec9           	s32i.n	a12, a14, 0
     b6d:	369c04        	ae_trunca32q48	a12, aeq1
     b70:	60ca74        	ae_lq32f.i	aeq3, a10, 28
     b73:	0499           	s32i.n	a9, a4, 0
     b75:	618134        	ae_lq56.i	aeq2, a1, 24
     b78:	f9f61405cf 	{ s32i.n	a12, a5, 0; ae_addq56	aeq1, aeq2, aeq3 }
     b7d:	3b6152        	s32i	a5, a1, 236
     b80:	fbb6f2f15e 	{ l32i	a5, a1, 188; ae_subq56	aeq3, aeq2, aeq3 }
     b85:	2d21a2        	l32i	a10, a1, 180
     b88:	368704        	ae_trunca32q48	a7, aeq0
     b8b:	369904        	ae_trunca32q48	a9, aeq1
     b8e:	0579           	s32i.n	a7, a5, 0
     b90:	0a99           	s32i.n	a9, a10, 0
     b92:	3c2182        	l32i	a8, a1, 240
     b95:	3a2172        	l32i	a7, a1, 232
     b98:	392192        	l32i	a9, a1, 228
     b9b:	3f2132        	l32i	a3, a1, 252
     b9e:	36bc04        	ae_trunca32q48	a12, aeq3
     ba1:	08c9           	s32i.n	a12, a8, 0
     ba3:	c78b           	addi.n	a12, a7, 8
     ba5:	790b           	addi.n	a7, a9, -1
     ba7:	938b           	addi.n	a9, a3, 8
     ba9:	2e2132        	l32i	a3, a1, 184
     bac:	443a           	add.n	a4, a4, a3
     bae:	2c6142        	s32i	a4, a1, 176
     bb1:	252142        	l32i	a4, a1, 148
     bb4:	223a           	add.n	a2, a2, a3
     bb6:	306122        	s32i	a2, a1, 192
     bb9:	243a           	add.n	a2, a4, a3
     bbb:	256122        	s32i	a2, a1, 148
     bbe:	3b2122        	l32i	a2, a1, 236
     bc1:	292142        	l32i	a4, a1, 164
     bc4:	663a           	add.n	a6, a6, a3
     bc6:	553a           	add.n	a5, a5, a3
     bc8:	316162        	s32i	a6, a1, 196
     bcb:	282162        	l32i	a6, a1, 160
     bce:	2f6152        	s32i	a5, a1, 188
     bd1:	523a           	add.n	a5, a2, a3
     bd3:	243a           	add.n	a2, a4, a3
     bd5:	296122        	s32i	a2, a1, 164
     bd8:	e128           	l32i.n	a2, a1, 56
     bda:	463a           	add.n	a4, a6, a3
     bdc:	242162        	l32i	a6, a1, 144
     bdf:	286142        	s32i	a4, a1, 160
     be2:	423a           	add.n	a4, a2, a3
     be4:	bb3a           	add.n	a11, a11, a3
     be6:	aa3a           	add.n	a10, a10, a3
     be8:	e149           	s32i.n	a4, a1, 56
     bea:	463a           	add.n	a4, a6, a3
     bec:	2b61b2        	s32i	a11, a1, 172
     bef:	2d61a2        	s32i	a10, a1, 180
     bf2:	ff3a           	add.n	a15, a15, a3
     bf4:	dd3a           	add.n	a13, a13, a3
     bf6:	0b2c           	movi.n	a11, 32
     bf8:	ee3a           	add.n	a14, a14, a3
     bfa:	8a2c           	movi.n	a10, 40
     bfc:	883a           	add.n	a8, a8, a3
     bfe:	246142        	s32i	a4, a1, 144
     c01:	051716        	beqz	a7, c56 <fix_fft40+0x662>

00000c04 <fix_fft40+0x610>:
     c04:	d8cc32        	addi	a3, a12, -40
     c07:	0348           	l32i.n	a4, a3, 0
     c09:	1338           	l32i.n	a3, a3, 4
     c0b:	2761f2        	s32i	a15, a1, 156
     c0e:	214140        	srai	a4, a4, 1
     c11:	213130        	srai	a3, a3, 1
     c14:	146142        	s32i	a4, a1, 80
     c17:	156132        	s32i	a3, a1, 84
     c1a:	3f6192        	s32i	a9, a1, 252
     c1d:	3e61d2        	s32i	a13, a1, 248
     c20:	3d61e2        	s32i	a14, a1, 244
     c23:	3c6182        	s32i	a8, a1, 240
     c26:	3a61c2        	s32i	a12, a1, 232
     c29:	396172        	s32i	a7, a1, 228
     c2c:	025726        	beqi	a7, 5, c32 <fix_fft40+0x63e>
     c2f:	fee106        	j	7b7 <fix_fft40+0x1c3>
     c32:	332142        	l32i	a4, a1, 204
     c35:	2a2162        	l32i	a6, a1, 168
     c38:	720c           	movi.n	a2, 7
     c3a:	203cc0        	or	a3, a12, a12
     c3d:	128276        	loop	a2, c53 <fix_fft40+0x65f>
     c40:	03c8           	l32i.n	a12, a3, 0
     c42:	1378           	l32i.n	a7, a3, 4
     c44:	28c332        	addi	a3, a3, 40
     c47:	21c1c0        	srai	a12, a12, 1
     c4a:	217170        	srai	a7, a7, 1
     c4d:	04c9           	s32i.n	a12, a4, 0
     c4f:	1479           	s32i.n	a7, a4, 4
     c51:	448b           	addi.n	a4, a4, 8

00000c53 <fix_fft40+0x65f>:
     c53:	fef586        	j	82d <fix_fft40+0x239>

00000c56 <fix_fft40+0x662>:
     c56:	fd0a21        	l32r	a2, 80 (1d88 <LC3Plus_lc3_scratch_pop>)
     c59:	3221a2        	l32i	a10, a1, 200
     c5c:	2621b2        	l32i	a11, a1, 152
     c5f:	0002e0        	callx8	a2
     c62:	f01d           	retw.n

00000c64 <FFT8N>:
     c64:	020136        	entry	a1, 0x100
     c67:	186132        	s32i	a3, a1, 96
     c6a:	176122        	s32i	a2, a1, 92
     c6d:	0215e6        	bgei	a5, 1, c73 <FFT8N+0xf>
     c70:	01b346        	j	1341 <FFT8N+0x6dd>
     c73:	d1e750        	mul16s	a14, a7, a5
     c76:	412132        	l32i	a3, a1, 0x104
     c79:	11a6e0        	slli	a10, a6, 2
     c7c:	90cee0        	addx2	a12, a14, a14
     c7f:	11b7e0        	slli	a11, a7, 2
     c82:	a08ee0        	addx4	a8, a14, a14
     c85:	3061a2        	s32i	a10, a1, 192
     c88:	11acf0        	slli	a10, a12, 1
     c8b:	f09ee0        	subx8	a9, a14, a14
     c8e:	2f61b2        	s32i	a11, a1, 188
     c91:	e0be30        	subx4	a11, a14, a3
     c94:	c07c30        	sub	a7, a12, a3
     c97:	d0ce30        	subx2	a12, a14, a3
     c9a:	c0aa30        	sub	a10, a10, a3
     c9d:	c08830        	sub	a8, a8, a3
     ca0:	c0ee30        	sub	a14, a14, a3
     ca3:	c03930        	sub	a3, a9, a3
     ca6:	172192        	l32i	a9, a1, 92
     ca9:	d12650        	mul16s	a2, a6, a5
     cac:	a06840        	addx4	a6, a8, a4
     caf:	a08a40        	addx4	a8, a10, a4
     cb2:	a0a740        	addx4	a10, a7, a4
     cb5:	182172        	l32i	a7, a1, 96
     cb8:	a0f290        	addx4	a15, a2, a9
     cbb:	a0bb40        	addx4	a11, a11, a4
     cbe:	2e61f2        	s32i	a15, a1, 184
     cc1:	a0fc40        	addx4	a15, a12, a4
     cc4:	a03340        	addx4	a3, a3, a4
     cc7:	a04e40        	addx4	a4, a14, a4
     cca:	216162        	s32i	a6, a1, 132
     ccd:	206182        	s32i	a8, a1, 128
     cd0:	1c61a2        	s32i	a10, a1, 112
     cd3:	c1b9           	s32i.n	a11, a1, 48
     cd5:	a06270        	addx4	a6, a2, a7
     cd8:	b08290        	addx8	a8, a2, a9
     cdb:	b0a270        	addx8	a10, a2, a7
     cde:	90b220        	addx2	a11, a2, a2
     ce1:	f0c220        	subx8	a12, a2, a2
     ce4:	a0e220        	addx4	a14, a2, a2
     ce7:	1122c0        	slli	a2, a2, 4
     cea:	4021d2        	l32i	a13, a1, 0x100
     ced:	226132        	s32i	a3, a1, 136
     cf0:	1b61f2        	s32i	a15, a1, 108
     cf3:	1f6142        	s32i	a4, a1, 124
     cf6:	114ce0        	slli	a4, a12, 2
     cf9:	f72a           	add.n	a15, a7, a2
     cfb:	292a           	add.n	a2, a9, a2
     cfd:	113bd0        	slli	a3, a11, 3
     d00:	2b6122        	s32i	a2, a1, 172
     d03:	112be0        	slli	a2, a11, 2
     d06:	b74a           	add.n	a11, a7, a4
     d08:	c94a           	add.n	a12, a9, a4
     d0a:	473a           	add.n	a4, a7, a3
     d0c:	393a           	add.n	a3, a9, a3
     d0e:	246162        	s32i	a6, a1, 144
     d11:	116ee0        	slli	a6, a14, 2
     d14:	e92a           	add.n	a14, a9, a2
     d16:	286132        	s32i	a3, a1, 160
     d19:	272a           	add.n	a2, a7, a2
     d1b:	f03550        	subx8	a3, a5, a5
     d1e:	2d6182        	s32i	a8, a1, 180
     d21:	876a           	add.n	a8, a7, a6
     d23:	2c61a2        	s32i	a10, a1, 176
     d26:	a96a           	add.n	a10, a9, a6
     d28:	236122        	s32i	a2, a1, 140
     d2b:	b023d0        	addx8	a2, a3, a13
     d2e:	a06550        	addx4	a6, a5, a5
     d31:	1e6122        	s32i	a2, a1, 120
     d34:	b026d0        	addx8	a2, a6, a13
     d37:	1175b0        	slli	a7, a5, 5
     d3a:	2a6182        	s32i	a8, a1, 168
     d3d:	b129           	s32i.n	a2, a1, 44
     d3f:	2d7a           	add.n	a2, a13, a7
     d41:	908550        	addx2	a8, a5, a5
     d44:	2961a2        	s32i	a10, a1, 164
     d47:	1a6122        	s32i	a2, a1, 104
     d4a:	1198c0        	slli	a9, a8, 4
     d4d:	b028d0        	addx8	a2, a8, a13
     d50:	11a5c0        	slli	a10, a5, 4
     d53:	2761e2        	s32i	a14, a1, 156
     d56:	3d9a           	add.n	a3, a13, a9
     d58:	196122        	s32i	a2, a1, 100
     d5b:	2daa           	add.n	a2, a13, a10
     d5d:	b0e5d0        	addx8	a14, a5, a13
     d60:	070c           	movi.n	a7, 0
     d62:	a139           	s32i.n	a3, a1, 40
     d64:	086122        	s32i	a2, a1, 32
     d67:	2561d2        	s32i	a13, a1, 148
     d6a:	0d61e2        	s32i	a14, a1, 52
     d6d:	178576        	loop	a5, d88 <FFT8N+0x124>
     d70:	030150        	rsr.lend	a5
     d73:	130050        	wsr.lbeg	a5
     d76:	fcc351        	l32r	a5, 84 (1341 <FFT8N+0x6dd>)
     d79:	0020f0        	nop
     d7c:	130150        	wsr.lend	a5
     d7f:	002000        	isync
     d82:	030250        	rsr.lcount	a5
     d85:	01c552        	addi	a5, a5, 1
     d88:	252122        	l32i	a2, a1, 148
     d8b:	d1a8           	l32i.n	a10, a1, 52
     d8d:	346142        	s32i	a4, a1, 208
     d90:	0238           	l32i.n	a3, a2, 0
     d92:	1298           	l32i.n	a9, a2, 4
     d94:	0a68           	l32i.n	a6, a10, 0
     d96:	331b           	addi.n	a3, a3, 1
     d98:	491b           	addi.n	a4, a9, 1
     d9a:	21d130        	srai	a13, a3, 1
     d9d:	21e140        	srai	a14, a4, 1
     da0:	3761f2        	s32i	a15, a1, 220
     da3:	3661b2        	s32i	a11, a1, 216
     da6:	3561c2        	s32i	a12, a1, 212
     da9:	266172        	s32i	a7, a1, 152
     dac:	1d61d2        	s32i	a13, a1, 116
     daf:	91e9           	s32i.n	a14, a1, 36
     db1:	4169           	s32i.n	a6, a1, 16
     db3:	213716        	beqz	a7, fca <FFT8N+0x366>
     db6:	8128           	l32i.n	a2, a1, 32
     db8:	1b2132        	l32i	a3, a1, 108
     dbb:	c198           	l32i.n	a9, a1, 48
     dbd:	0278           	l32i.n	a7, a2, 0
     dbf:	0348           	l32i.n	a4, a3, 0
     dc1:	192152        	l32i	a5, a1, 100
     dc4:	1c2162        	l32i	a6, a1, 112
     dc7:	13c8           	l32i.n	a12, a3, 4
     dc9:	8129           	s32i.n	a2, a1, 32
     dcb:	12a8           	l32i.n	a10, a2, 4
     dcd:	822740        	mull	a2, a7, a4
     dd0:	05b8           	l32i.n	a11, a5, 0
     dd2:	15d8           	l32i.n	a13, a5, 4
     dd4:	0688           	l32i.n	a8, a6, 0
     dd6:	1658           	l32i.n	a5, a6, 4
     dd8:	09e8           	l32i.n	a14, a9, 0
     dda:	096d           	mov.n	a6, a9
     ddc:	c199           	s32i.n	a9, a1, 48
     dde:	b29740        	mulsh	a9, a7, a4
     de1:	052f20        	extui	a2, a2, 31, 1
     de4:	902920        	addx2	a2, a9, a2
     de7:	8297c0        	mull	a9, a7, a12
     dea:	b277c0        	mulsh	a7, a7, a12
     ded:	059f90        	extui	a9, a9, 31, 1
     df0:	909790        	addx2	a9, a7, a9
     df3:	827ac0        	mull	a7, a10, a12
     df6:	b2cac0        	mulsh	a12, a10, a12
     df9:	057f70        	extui	a7, a7, 31, 1
     dfc:	907c70        	addx2	a7, a12, a7
     dff:	c02270        	sub	a2, a2, a7
     e02:	7129           	s32i.n	a2, a1, 28
     e04:	b22a40        	mulsh	a2, a10, a4
     e07:	824a40        	mull	a4, a10, a4
     e0a:	82ab50        	mull	a10, a11, a5
     e0d:	054f40        	extui	a4, a4, 31, 1
     e10:	902240        	addx2	a2, a2, a4
     e13:	824b80        	mull	a4, a11, a8
     e16:	292a           	add.n	a2, a9, a2
     e18:	1a2132        	l32i	a3, a1, 104
     e1b:	f129           	s32i.n	a2, a1, 60
     e1d:	b29b80        	mulsh	a9, a11, a8
     e20:	052f40        	extui	a2, a4, 31, 1
     e23:	054fa0        	extui	a4, a10, 31, 1
     e26:	b2bb50        	mulsh	a11, a11, a5
     e29:	82ad50        	mull	a10, a13, a5
     e2c:	b25d50        	mulsh	a5, a13, a5
     e2f:	03f8           	l32i.n	a15, a3, 0
     e31:	902920        	addx2	a2, a9, a2
     e34:	059fa0        	extui	a9, a10, 31, 1
     e37:	904b40        	addx2	a4, a11, a4
     e3a:	b2bd80        	mulsh	a11, a13, a8
     e3d:	82dd80        	mull	a13, a13, a8
     e40:	16c8           	l32i.n	a12, a6, 4
     e42:	b168           	l32i.n	a6, a1, 44
     e44:	905590        	addx2	a5, a5, a9
     e47:	2121a2        	l32i	a10, a1, 132
     e4a:	1338           	l32i.n	a3, a3, 4
     e4c:	c02250        	sub	a2, a2, a5
     e4f:	055fd0        	extui	a5, a13, 31, 1
     e52:	166122        	s32i	a2, a1, 88
     e55:	902b50        	addx2	a2, a11, a5
     e58:	82bfe0        	mull	a11, a15, a14
     e5b:	242a           	add.n	a2, a4, a2
     e5d:	825fc0        	mull	a5, a15, a12
     e60:	0678           	l32i.n	a7, a6, 0
     e62:	b169           	s32i.n	a6, a1, 44
     e64:	1688           	l32i.n	a8, a6, 4
     e66:	0a98           	l32i.n	a9, a10, 0
     e68:	b2dfe0        	mulsh	a13, a15, a14
     e6b:	b26fc0        	mulsh	a6, a15, a12
     e6e:	0afd           	mov.n	a15, a10
     e70:	82a3c0        	mull	a10, a3, a12
     e73:	136122        	s32i	a2, a1, 76
     e76:	052fb0        	extui	a2, a11, 31, 1
     e79:	b2b3c0        	mulsh	a11, a3, a12
     e7c:	054f50        	extui	a4, a5, 31, 1
     e7f:	055fa0        	extui	a5, a10, 31, 1
     e82:	b2c3e0        	mulsh	a12, a3, a14
     e85:	8233e0        	mull	a3, a3, a14
     e88:	902d20        	addx2	a2, a13, a2
     e8b:	905b50        	addx2	a5, a11, a5
     e8e:	1fa8           	l32i.n	a10, a15, 4
     e90:	c02250        	sub	a2, a2, a5
     e93:	053f30        	extui	a3, a3, 31, 1
     e96:	904640        	addx2	a4, a6, a4
     e99:	6129           	s32i.n	a2, a1, 24
     e9b:	902c30        	addx2	a2, a12, a3
     e9e:	82d790        	mull	a13, a7, a9
     ea1:	242a           	add.n	a2, a4, a2
     ea3:	b2e790        	mulsh	a14, a7, a9
     ea6:	8247a0        	mull	a4, a7, a10
     ea9:	146122        	s32i	a2, a1, 80
     eac:	052fd0        	extui	a2, a13, 31, 1
     eaf:	a168           	l32i.n	a6, a1, 40
     eb1:	902e20        	addx2	a2, a14, a2
     eb4:	b277a0        	mulsh	a7, a7, a10
     eb7:	82b8a0        	mull	a11, a8, a10
     eba:	2021e2        	l32i	a14, a1, 128
     ebd:	053f40        	extui	a3, a4, 31, 1
     ec0:	b2a8a0        	mulsh	a10, a8, a10
     ec3:	903730        	addx2	a3, a7, a3
     ec6:	057fb0        	extui	a7, a11, 31, 1
     ec9:	907a70        	addx2	a7, a10, a7
     ecc:	0658           	l32i.n	a5, a6, 0
     ece:	0ea8           	l32i.n	a10, a14, 0
     ed0:	82d890        	mull	a13, a8, a9
     ed3:	b2c890        	mulsh	a12, a8, a9
     ed6:	1e88           	l32i.n	a8, a14, 4
     ed8:	c02270        	sub	a2, a2, a7
     edb:	057fd0        	extui	a7, a13, 31, 1
     ede:	16d8           	l32i.n	a13, a6, 4
     ee0:	8245a0        	mull	a4, a5, a10
     ee3:	82b580        	mull	a11, a5, a8
     ee6:	156122        	s32i	a2, a1, 84
     ee9:	902c70        	addx2	a2, a12, a7
     eec:	057f40        	extui	a7, a4, 31, 1
     eef:	b295a0        	mulsh	a9, a5, a10
     ef2:	b25580        	mulsh	a5, a5, a8
     ef5:	824d80        	mull	a4, a13, a8
     ef8:	a169           	s32i.n	a6, a1, 40
     efa:	05cfb0        	extui	a12, a11, 31, 1
     efd:	b26d80        	mulsh	a6, a13, a8
     f00:	232a           	add.n	a2, a3, a2
     f02:	9035c0        	addx2	a3, a5, a12
     f05:	055f40        	extui	a5, a4, 31, 1
     f08:	126122        	s32i	a2, a1, 72
     f0b:	902970        	addx2	a2, a9, a7
     f0e:	905650        	addx2	a5, a6, a5
     f11:	222162        	l32i	a6, a1, 136
     f14:	b27da0        	mulsh	a7, a13, a10
     f17:	82bda0        	mull	a11, a13, a10
     f1a:	1e21d2        	l32i	a13, a1, 120
     f1d:	0698           	l32i.n	a9, a6, 0
     f1f:	c02250        	sub	a2, a2, a5
     f22:	0d88           	l32i.n	a8, a13, 0
     f24:	055fb0        	extui	a5, a11, 31, 1
     f27:	5129           	s32i.n	a2, a1, 20
     f29:	902750        	addx2	a2, a7, a5
     f2c:	82c890        	mull	a12, a8, a9
     f2f:	232a           	add.n	a2, a3, a2
     f31:	1638           	l32i.n	a3, a6, 4
     f33:	e129           	s32i.n	a2, a1, 56
     f35:	052fc0        	extui	a2, a12, 31, 1
     f38:	1dc8           	l32i.n	a12, a13, 4
     f3a:	b24890        	mulsh	a4, a8, a9
     f3d:	827830        	mull	a7, a8, a3
     f40:	902420        	addx2	a2, a4, a2
     f43:	b28830        	mulsh	a8, a8, a3
     f46:	824c30        	mull	a4, a12, a3
     f49:	05af70        	extui	a10, a7, 31, 1
     f4c:	9058a0        	addx2	a5, a8, a10
     f4f:	058f40        	extui	a8, a4, 31, 1
     f52:	1f2142        	l32i	a4, a1, 124
     f55:	b23c30        	mulsh	a3, a12, a3
     f58:	41b8           	l32i.n	a11, a1, 16
     f5a:	827c90        	mull	a7, a12, a9
     f5d:	b2ac90        	mulsh	a10, a12, a9
     f60:	1498           	l32i.n	a9, a4, 4
     f62:	903380        	addx2	a3, a3, a8
     f65:	c08230        	sub	a8, a2, a3
     f68:	052f70        	extui	a2, a7, 31, 1
     f6b:	902a20        	addx2	a2, a10, a2
     f6e:	82cb90        	mull	a12, a11, a9
     f71:	0478           	l32i.n	a7, a4, 0
     f73:	d1a8           	l32i.n	a10, a1, 52
     f75:	252a           	add.n	a2, a5, a2
     f77:	b25b90        	mulsh	a5, a11, a9
     f7a:	053fc0        	extui	a3, a12, 31, 1
     f7d:	116122        	s32i	a2, a1, 68
     f80:	902530        	addx2	a2, a5, a3
     f83:	1a38           	l32i.n	a3, a10, 4
     f85:	82cb70        	mull	a12, a11, a7
     f88:	b2bb70        	mulsh	a11, a11, a7
     f8b:	05afc0        	extui	a10, a12, 31, 1
     f8e:	825370        	mull	a5, a3, a7
     f91:	90aba0        	addx2	a10, a11, a10
     f94:	b2b370        	mulsh	a11, a3, a7
     f97:	827390        	mull	a7, a3, a9
     f9a:	b23390        	mulsh	a3, a3, a9
     f9d:	055f50        	extui	a5, a5, 31, 1
     fa0:	057f70        	extui	a7, a7, 31, 1
     fa3:	903370        	addx2	a3, a3, a7
     fa6:	905b50        	addx2	a5, a11, a5
     fa9:	c03a30        	sub	a3, a10, a3
     fac:	225a           	add.n	a2, a2, a5
     fae:	04ad           	mov.n	a10, a4
     fb0:	106122        	s32i	a2, a1, 64
     fb3:	4139           	s32i.n	a3, a1, 16
     fb5:	1921c2        	l32i	a12, a1, 100
     fb8:	1b2192        	l32i	a9, a1, 108
     fbb:	1a2142        	l32i	a4, a1, 104
     fbe:	a1b8           	l32i.n	a11, a1, 40
     fc0:	b128           	l32i.n	a2, a1, 44
     fc2:	c158           	l32i.n	a5, a1, 48
     fc4:	1c2132        	l32i	a3, a1, 112
     fc7:	0017c6        	j	102a <FFT8N+0x3c6>

00000fca <FFT8N+0x366>:
     fca:	d128           	l32i.n	a2, a1, 52
     fcc:	8158           	l32i.n	a5, a1, 32
     fce:	1921c2        	l32i	a12, a1, 100
     fd1:	1228           	l32i.n	a2, a2, 4
     fd3:	106122        	s32i	a2, a1, 64
     fd6:	1528           	l32i.n	a2, a5, 4
     fd8:	f129           	s32i.n	a2, a1, 60
     fda:	b128           	l32i.n	a2, a1, 44
     fdc:	1a2142        	l32i	a4, a1, 104
     fdf:	0538           	l32i.n	a3, a5, 0
     fe1:	12b8           	l32i.n	a11, a2, 4
     fe3:	1261b2        	s32i	a11, a1, 72
     fe6:	a1b8           	l32i.n	a11, a1, 40
     fe8:	0c68           	l32i.n	a6, a12, 0
     fea:	0488           	l32i.n	a8, a4, 0
     fec:	0bd8           	l32i.n	a13, a11, 0
     fee:	51d9           	s32i.n	a13, a1, 20
     ff0:	1e21d2        	l32i	a13, a1, 120
     ff3:	1498           	l32i.n	a9, a4, 4
     ff5:	02a8           	l32i.n	a10, a2, 0
     ff7:	1be8           	l32i.n	a14, a11, 4
     ff9:	1df8           	l32i.n	a15, a13, 4
     ffb:	7139           	s32i.n	a3, a1, 28
     ffd:	8159           	s32i.n	a5, a1, 32
     fff:	166162        	s32i	a6, a1, 88
    1002:	6189           	s32i.n	a8, a1, 24
    1004:	146192        	s32i	a9, a1, 80
    1007:	1561a2        	s32i	a10, a1, 84
    100a:	e1e9           	s32i.n	a14, a1, 56
    100c:	1161f2        	s32i	a15, a1, 68
    100f:	0d88           	l32i.n	a8, a13, 0
    1011:	222162        	l32i	a6, a1, 136
    1014:	2121f2        	l32i	a15, a1, 132
    1017:	2021e2        	l32i	a14, a1, 128
    101a:	1c2132        	l32i	a3, a1, 112
    101d:	c158           	l32i.n	a5, a1, 48
    101f:	1b2192        	l32i	a9, a1, 108
    1022:	1f21a2        	l32i	a10, a1, 124
    1025:	1c78           	l32i.n	a7, a12, 4
    1027:	136172        	s32i	a7, a1, 76
    102a:	262172        	l32i	a7, a1, 152
    102d:	dd8b           	addi.n	a13, a13, 8
    102f:	bb8b           	addi.n	a11, a11, 8
    1031:	770b           	addi.n	a7, a7, -1
    1033:	266172        	s32i	a7, a1, 152
    1036:	8178           	l32i.n	a7, a1, 32
    1038:	1e61d2        	s32i	a13, a1, 120
    103b:	2f21d2        	l32i	a13, a1, 188
    103e:	a1b9           	s32i.n	a11, a1, 40
    1040:	cc8b           	addi.n	a12, a12, 8
    1042:	d1b8           	l32i.n	a11, a1, 52
    1044:	228b           	addi.n	a2, a2, 8
    1046:	448b           	addi.n	a4, a4, 8
    1048:	1961c2        	s32i	a12, a1, 100
    104b:	2521c2        	l32i	a12, a1, 148
    104e:	b129           	s32i.n	a2, a1, 44
    1050:	278b           	addi.n	a2, a7, 8
    1052:	1a6142        	s32i	a4, a1, 104
    1055:	142142        	l32i	a4, a1, 80
    1058:	8129           	s32i.n	a2, a1, 32
    105a:	2b8b           	addi.n	a2, a11, 8
    105c:	55da           	add.n	a5, a5, a13
    105e:	d129           	s32i.n	a2, a1, 52
    1060:	2c8b           	addi.n	a2, a12, 8
    1062:	66da           	add.n	a6, a6, a13
    1064:	c159           	s32i.n	a5, a1, 48
    1066:	9158           	l32i.n	a5, a1, 36
    1068:	256122        	s32i	a2, a1, 148
    106b:	241b           	addi.n	a2, a4, 1
    106d:	226162        	s32i	a6, a1, 136
    1070:	7168           	l32i.n	a6, a1, 28
    1072:	5178           	l32i.n	a7, a1, 20
    1074:	212120        	srai	a2, a2, 1
    1077:	33da           	add.n	a3, a3, a13
    1079:	99da           	add.n	a9, a9, a13
    107b:	b25a           	add.n	a11, a2, a5
    107d:	c02520        	sub	a2, a5, a2
    1080:	1c6132        	s32i	a3, a1, 112
    1083:	371b           	addi.n	a3, a7, 1
    1085:	1b6192        	s32i	a9, a1, 108
    1088:	9129           	s32i.n	a2, a1, 36
    108a:	261b           	addi.n	a2, a6, 1
    108c:	162192        	l32i	a9, a1, 88
    108f:	eeda           	add.n	a14, a14, a13
    1091:	212120        	srai	a2, a2, 1
    1094:	213130        	srai	a3, a3, 1
    1097:	523a           	add.n	a5, a2, a3
    1099:	2061e2        	s32i	a14, a1, 128
    109c:	ffda           	add.n	a15, a15, a13
    109e:	aada           	add.n	a10, a10, a13
    10a0:	c02230        	sub	a2, a2, a3
    10a3:	41d8           	l32i.n	a13, a1, 16
    10a5:	1521e2        	l32i	a14, a1, 84
    10a8:	1f61a2        	s32i	a10, a1, 124
    10ab:	7129           	s32i.n	a2, a1, 28
    10ad:	291b           	addi.n	a2, a9, 1
    10af:	a81b           	addi.n	a10, a8, 1
    10b1:	2131a0        	srai	a3, a10, 1
    10b4:	212120        	srai	a2, a2, 1
    10b7:	6168           	l32i.n	a6, a1, 24
    10b9:	c23a           	add.n	a12, a2, a3
    10bb:	c07230        	sub	a7, a2, a3
    10be:	2d1b           	addi.n	a2, a13, 1
    10c0:	3e1b           	addi.n	a3, a14, 1
    10c2:	212120        	srai	a2, a2, 1
    10c5:	213130        	srai	a3, a3, 1
    10c8:	1d21a2        	l32i	a10, a1, 116
    10cb:	2161f2        	s32i	a15, a1, 132
    10ce:	f23a           	add.n	a15, a2, a3
    10d0:	c0e230        	sub	a14, a2, a3
    10d3:	261b           	addi.n	a2, a6, 1
    10d5:	212120        	srai	a2, a2, 1
    10d8:	2181f0        	srai	a8, a15, 1
    10db:	5129           	s32i.n	a2, a1, 20
    10dd:	22aa           	add.n	a2, a2, a10
    10df:	381b           	addi.n	a3, a8, 1
    10e1:	212120        	srai	a2, a2, 1
    10e4:	21c1c0        	srai	a12, a12, 1
    10e7:	219130        	srai	a9, a3, 1
    10ea:	3c1b           	addi.n	a3, a12, 1
    10ec:	221b           	addi.n	a2, a2, 1
    10ee:	215150        	srai	a5, a5, 1
    10f1:	21d130        	srai	a13, a3, 1
    10f4:	21f120        	srai	a15, a2, 1
    10f7:	251b           	addi.n	a2, a5, 1
    10f9:	212120        	srai	a2, a2, 1
    10fc:	69da           	add.n	a6, a9, a13
    10fe:	156192        	s32i	a9, a1, 84
    1101:	172182        	l32i	a8, a1, 92
    1104:	132192        	l32i	a9, a1, 76
    1107:	1121c2        	l32i	a12, a1, 68
    110a:	32fa           	add.n	a3, a2, a15
    110c:	1661d2        	s32i	a13, a1, 88
    110f:	61f9           	s32i.n	a15, a1, 24
    1111:	4129           	s32i.n	a2, a1, 16
    1113:	263a           	add.n	a2, a6, a3
    1115:	1221f2        	l32i	a15, a1, 72
    1118:	1021d2        	l32i	a13, a1, 64
    111b:	336132        	s32i	a3, a1, 204
    111e:	3c1b           	addi.n	a3, a12, 1
    1120:	0829           	s32i.n	a2, a8, 0
    1122:	291b           	addi.n	a2, a9, 1
    1124:	212120        	srai	a2, a2, 1
    1127:	213130        	srai	a3, a3, 1
    112a:	923a           	add.n	a9, a2, a3
    112c:	4f1b           	addi.n	a4, a15, 1
    112e:	c02230        	sub	a2, a2, a3
    1131:	3d1b           	addi.n	a3, a13, 1
    1133:	146162        	s32i	a6, a1, 80
    1136:	216130        	srai	a6, a3, 1
    1139:	215140        	srai	a5, a4, 1
    113c:	c03650        	sub	a3, a6, a5
    113f:	832a           	add.n	a8, a3, a2
    1141:	21c180        	srai	a12, a8, 1
    1144:	c04320        	sub	a4, a3, a2
    1147:	3c1b           	addi.n	a3, a12, 1
    1149:	c0fe70        	sub	a15, a14, a7
    114c:	21d130        	srai	a13, a3, 1
    114f:	2131f0        	srai	a3, a15, 1
    1152:	331b           	addi.n	a3, a3, 1
    1154:	fbc9c1        	l32r	a12, 78 (5a82799a <_end+0x5a825576>)
    1157:	213130        	srai	a3, a3, 1
    115a:	126132        	s32i	a3, a1, 72
    115d:	33da           	add.n	a3, a3, a13
    115f:	8223c0        	mull	a2, a3, a12
    1162:	b283c0        	mulsh	a8, a3, a12
    1165:	1361d2        	s32i	a13, a1, 76
    1168:	052f20        	extui	a2, a2, 31, 1
    116b:	de7a           	add.n	a13, a14, a7
    116d:	908820        	addx2	a8, a8, a2
    1170:	2121d0        	srai	a2, a13, 1
    1173:	221b           	addi.n	a2, a2, 1
    1175:	21f140        	srai	a15, a4, 1
    1178:	21e120        	srai	a14, a2, 1
    117b:	2f1b           	addi.n	a2, a15, 1
    117d:	212120        	srai	a2, a2, 1
    1180:	106122        	s32i	a2, a1, 64
    1183:	c022e0        	sub	a2, a2, a14
    1186:	8272c0        	mull	a7, a2, a12
    1189:	b242c0        	mulsh	a4, a2, a12
    118c:	f1c8           	l32i.n	a12, a1, 60
    118e:	e1f8           	l32i.n	a15, a1, 56
    1190:	057f70        	extui	a7, a7, 31, 1
    1193:	dc1b           	addi.n	a13, a12, 1
    1195:	2f1b           	addi.n	a2, a15, 1
    1197:	1161e2        	s32i	a14, a1, 68
    119a:	90e470        	addx2	a14, a4, a7
    119d:	765a           	add.n	a7, a6, a5
    119f:	2151d0        	srai	a5, a13, 1
    11a2:	216120        	srai	a6, a2, 1
    11a5:	214170        	srai	a4, a7, 1
    11a8:	756a           	add.n	a7, a5, a6
    11aa:	219190        	srai	a9, a9, 1
    11ad:	2131b0        	srai	a3, a11, 1
    11b0:	21b170        	srai	a11, a7, 1
    11b3:	441b           	addi.n	a4, a4, 1
    11b5:	991b           	addi.n	a9, a9, 1
    11b7:	c31b           	addi.n	a12, a3, 1
    11b9:	bb1b           	addi.n	a11, a11, 1
    11bb:	214140        	srai	a4, a4, 1
    11be:	219190        	srai	a9, a9, 1
    11c1:	21c1c0        	srai	a12, a12, 1
    11c4:	21b1b0        	srai	a11, a11, 1
    11c7:	f49a           	add.n	a15, a4, a9
    11c9:	dbca           	add.n	a13, a11, a12
    11cb:	e1f9           	s32i.n	a15, a1, 56
    11cd:	3fda           	add.n	a3, a15, a13
    11cf:	182172        	l32i	a7, a1, 96
    11d2:	51f8           	l32i.n	a15, a1, 20
    11d4:	c05560        	sub	a5, a5, a6
    11d7:	0739           	s32i.n	a3, a7, 0
    11d9:	c03af0        	sub	a3, a10, a15
    11dc:	9178           	l32i.n	a7, a1, 36
    11de:	71f8           	l32i.n	a15, a1, 28
    11e0:	216130        	srai	a6, a3, 1
    11e3:	661b           	addi.n	a6, a6, 1
    11e5:	215150        	srai	a5, a5, 1
    11e8:	212160        	srai	a2, a6, 1
    11eb:	2161f0        	srai	a6, a15, 1
    11ee:	21a170        	srai	a10, a7, 1
    11f1:	551b           	addi.n	a5, a5, 1
    11f3:	761b           	addi.n	a7, a6, 1
    11f5:	f1d9           	s32i.n	a13, a1, 60
    11f7:	da1b           	addi.n	a13, a10, 1
    11f9:	215150        	srai	a5, a5, 1
    11fc:	21d1d0        	srai	a13, a13, 1
    11ff:	217170        	srai	a7, a7, 1
    1202:	c0ad70        	sub	a10, a13, a7
    1205:	652a           	add.n	a6, a5, a2
    1207:	316182        	s32i	a8, a1, 196
    120a:	3261e2        	s32i	a14, a1, 200
    120d:	3eaa           	add.n	a3, a14, a10
    120f:	1d61a2        	s32i	a10, a1, 116
    1212:	e86a           	add.n	a14, a8, a6
    1214:	5169           	s32i.n	a6, a1, 20
    1216:	2e21a2        	l32i	a10, a1, 184
    1219:	2421f2        	l32i	a15, a1, 144
    121c:	4168           	l32i.n	a6, a1, 16
    121e:	6188           	l32i.n	a8, a1, 24
    1220:	0ae9           	s32i.n	a14, a10, 0
    1222:	77da           	add.n	a7, a7, a13
    1224:	c09940        	sub	a9, a9, a4
    1227:	0f39           	s32i.n	a3, a15, 0
    1229:	c06860        	sub	a6, a8, a6
    122c:	1321d2        	l32i	a13, a1, 76
    122f:	1221f2        	l32i	a15, a1, 72
    1232:	4199           	s32i.n	a9, a1, 16
    1234:	9169           	s32i.n	a6, a1, 36
    1236:	c09690        	sub	a9, a6, a9
    1239:	c06250        	sub	a6, a2, a5
    123c:	fb8f51        	l32r	a5, 78 (5a82799a <_end+0x5a825576>)
    123f:	2d21e2        	l32i	a14, a1, 180
    1242:	c03df0        	sub	a3, a13, a15
    1245:	c04cb0        	sub	a4, a12, a11
    1248:	1621b2        	l32i	a11, a1, 88
    124b:	1521c2        	l32i	a12, a1, 84
    124e:	1121d2        	l32i	a13, a1, 68
    1251:	1021f2        	l32i	a15, a1, 64
    1254:	828350        	mull	a8, a3, a5
    1257:	0e99           	s32i.n	a9, a14, 0
    1259:	2c2192        	l32i	a9, a1, 176
    125c:	c02cb0        	sub	a2, a12, a11
    125f:	05cf80        	extui	a12, a8, 31, 1
    1262:	8dfa           	add.n	a8, a13, a15
    1264:	fb86d1        	l32r	a13, 7c (a57d8666 <_end+0xa57d6242>)
    1267:	c0b420        	sub	a11, a4, a2
    126a:	09b9           	s32i.n	a11, a9, 0
    126c:	b2b350        	mulsh	a11, a3, a5
    126f:	82f8d0        	mull	a15, a8, a13
    1272:	90bbc0        	addx2	a11, a11, a12
    1275:	b2c8d0        	mulsh	a12, a8, a13
    1278:	05dff0        	extui	a13, a15, 31, 1
    127b:	90ccd0        	addx2	a12, a12, a13
    127e:	7179           	s32i.n	a7, a1, 28
    1280:	dc7a           	add.n	a13, a12, a7
    1282:	272172        	l32i	a7, a1, 156
    1285:	232152        	l32i	a5, a1, 140
    1288:	3b6a           	add.n	a3, a11, a6
    128a:	6169           	s32i.n	a6, a1, 24
    128c:	0739           	s32i.n	a3, a7, 0
    128e:	05d9           	s32i.n	a13, a5, 0
    1290:	f168           	l32i.n	a6, a1, 60
    1292:	e188           	l32i.n	a8, a1, 56
    1294:	1421d2        	l32i	a13, a1, 80
    1297:	3321f2        	l32i	a15, a1, 204
    129a:	c03680        	sub	a3, a6, a8
    129d:	2b2182        	l32i	a8, a1, 172
    12a0:	c05fd0        	sub	a5, a15, a13
    12a3:	322162        	l32i	a6, a1, 200
    12a6:	1d21d2        	l32i	a13, a1, 116
    12a9:	0859           	s32i.n	a5, a8, 0
    12ab:	3721f2        	l32i	a15, a1, 220
    12ae:	c0dd60        	sub	a13, a13, a6
    12b1:	312152        	l32i	a5, a1, 196
    12b4:	5168           	l32i.n	a6, a1, 20
    12b6:	0f39           	s32i.n	a3, a15, 0
    12b8:	c03650        	sub	a3, a6, a5
    12bb:	292162        	l32i	a6, a1, 164
    12be:	2a2152        	l32i	a5, a1, 168
    12c1:	0639           	s32i.n	a3, a6, 0
    12c3:	05d9           	s32i.n	a13, a5, 0
    12c5:	324a           	add.n	a3, a2, a4
    12c7:	4148           	l32i.n	a4, a1, 16
    12c9:	91d8           	l32i.n	a13, a1, 36
    12cb:	44da           	add.n	a4, a4, a13
    12cd:	2821d2        	l32i	a13, a1, 160
    12d0:	0d49           	s32i.n	a4, a13, 0
    12d2:	342142        	l32i	a4, a1, 208
    12d5:	0439           	s32i.n	a3, a4, 0
    12d7:	7138           	l32i.n	a3, a1, 28
    12d9:	c023c0        	sub	a2, a3, a12
    12dc:	61c8           	l32i.n	a12, a1, 24
    12de:	c03cb0        	sub	a3, a12, a11
    12e1:	3521c2        	l32i	a12, a1, 212
    12e4:	3621b2        	l32i	a11, a1, 216
    12e7:	0c39           	s32i.n	a3, a12, 0
    12e9:	0b29           	s32i.n	a2, a11, 0
    12eb:	302122        	l32i	a2, a1, 192
    12ee:	172132        	l32i	a3, a1, 92
    12f1:	aa2a           	add.n	a10, a10, a2
    12f3:	332a           	add.n	a3, a3, a2
    12f5:	176132        	s32i	a3, a1, 92
    12f8:	182132        	l32i	a3, a1, 96
    12fb:	2e61a2        	s32i	a10, a1, 184
    12fe:	ee2a           	add.n	a14, a14, a2
    1300:	2421a2        	l32i	a10, a1, 144
    1303:	2d61e2        	s32i	a14, a1, 180
    1306:	2321e2        	l32i	a14, a1, 140
    1309:	332a           	add.n	a3, a3, a2
    130b:	772a           	add.n	a7, a7, a2
    130d:	186132        	s32i	a3, a1, 96
    1310:	3a2a           	add.n	a3, a10, a2
    1312:	276172        	s32i	a7, a1, 156
    1315:	262172        	l32i	a7, a1, 152
    1318:	246132        	s32i	a3, a1, 144
    131b:	992a           	add.n	a9, a9, a2
    131d:	dd2a           	add.n	a13, a13, a2
    131f:	552a           	add.n	a5, a5, a2
    1321:	662a           	add.n	a6, a6, a2
    1323:	882a           	add.n	a8, a8, a2
    1325:	3e2a           	add.n	a3, a14, a2
    1327:	2c6192        	s32i	a9, a1, 176
    132a:	bb2a           	add.n	a11, a11, a2
    132c:	cc2a           	add.n	a12, a12, a2
    132e:	442a           	add.n	a4, a4, a2
    1330:	ff2a           	add.n	a15, a15, a2
    1332:	2861d2        	s32i	a13, a1, 160
    1335:	2a6152        	s32i	a5, a1, 168
    1338:	296162        	s32i	a6, a1, 164
    133b:	2b6182        	s32i	a8, a1, 172
    133e:	236132        	s32i	a3, a1, 140

00001341 <FFT8N+0x6dd>:
    1341:	f01d           	retw.n

00001343 <FFT8N+0x6df>:
    1343:	00000000                                 .....

00001348 <FFT4N>:
    1348:	016136        	entry	a1, 176
    134b:	5129           	s32i.n	a2, a1, 20
    134d:	0215e6        	bgei	a5, 1, 1353 <FFT4N+0xb>
    1350:	00a686        	j	15ee <FFT4N+0x2a6>
    1353:	2d2122        	l32i	a2, a1, 180
    1356:	909550        	addx2	a9, a5, a5
    1359:	d18650        	mul16s	a8, a6, a5
    135c:	11f6e0        	slli	a15, a6, 2
    135f:	5168           	l32i.n	a6, a1, 20
    1361:	11b9d0        	slli	a11, a9, 3
    1364:	11e5c0        	slli	a14, a5, 4
    1367:	f09520        	subx8	a9, a5, a2
    136a:	1177e0        	slli	a7, a7, 2
    136d:	c0ab20        	sub	a10, a11, a2
    1370:	2c21c2        	l32i	a12, a1, 176
    1373:	c02e20        	sub	a2, a14, a2
    1376:	21e9           	s32i.n	a14, a1, 8
    1378:	91f9           	s32i.n	a15, a1, 36
    137a:	8179           	s32i.n	a7, a1, 32
    137c:	a0f860        	addx4	a15, a8, a6
    137f:	907880        	addx2	a7, a8, a8
    1382:	b0d830        	addx8	a13, a8, a3
    1385:	a09940        	addx4	a9, a9, a4
    1388:	a0e240        	addx4	a14, a2, a4
    138b:	a04a40        	addx4	a4, a10, a4
    138e:	b0a860        	addx8	a10, a8, a6
    1391:	a08830        	addx4	a8, a8, a3
    1394:	7189           	s32i.n	a8, a1, 28
    1396:	1187e0        	slli	a8, a7, 2
    1399:	738a           	add.n	a7, a3, a8
    139b:	868a           	add.n	a8, a6, a8
    139d:	046d           	mov.n	a6, a4
    139f:	4cba           	add.n	a4, a12, a11
    13a1:	21b8           	l32i.n	a11, a1, 8
    13a3:	4149           	s32i.n	a4, a1, 16
    13a5:	092d           	mov.n	a2, a9
    13a7:	4cba           	add.n	a4, a12, a11
    13a9:	b095c0        	addx8	a9, a5, a12
    13ac:	3149           	s32i.n	a4, a1, 12
    13ae:	040c           	movi.n	a4, 0
    13b0:	2199           	s32i.n	a9, a1, 8
    13b2:	178576        	loop	a5, 13cd <FFT4N+0x85>
    13b5:	030150        	rsr.lend	a5
    13b8:	130050        	wsr.lbeg	a5
    13bb:	fb3351        	l32r	a5, 88 (15ee <FFT4N+0x2a6>)
    13be:	0020f0        	nop
    13c1:	130150        	wsr.lend	a5
    13c4:	002000        	isync
    13c7:	030250        	rsr.lcount	a5
    13ca:	01c552        	addi	a5, a5, 1
    13cd:	0cb8           	l32i.n	a11, a12, 0
    13cf:	1c58           	l32i.n	a5, a12, 4
    13d1:	2198           	l32i.n	a9, a1, 8
    13d3:	1d6182        	s32i	a8, a1, 116
    13d6:	218150        	srai	a8, a5, 1
    13d9:	1e6172        	s32i	a7, a1, 120
    13dc:	2171b0        	srai	a7, a11, 1
    13df:	771b           	addi.n	a7, a7, 1
    13e1:	1f61a2        	s32i	a10, a1, 124
    13e4:	09a8           	l32i.n	a10, a9, 0
    13e6:	881b           	addi.n	a8, a8, 1
    13e8:	217170        	srai	a7, a7, 1
    13eb:	21b180        	srai	a11, a8, 1
    13ee:	6179           	s32i.n	a7, a1, 24
    13f0:	236132        	s32i	a3, a1, 140
    13f3:	2261c2        	s32i	a12, a1, 136
    13f6:	2161f2        	s32i	a15, a1, 132
    13f9:	2061d2        	s32i	a13, a1, 128
    13fc:	1c6142        	s32i	a4, a1, 112
    13ff:	1b61b2        	s32i	a11, a1, 108
    1402:	1a61e2        	s32i	a14, a1, 104
    1405:	196162        	s32i	a6, a1, 100
    1408:	186122        	s32i	a2, a1, 96
    140b:	105416        	beqz	a4, 1514 <FFT4N+0x1cc>
    140e:	3158           	l32i.n	a5, a1, 12
    1410:	4198           	l32i.n	a9, a1, 16
    1412:	0e88           	l32i.n	a8, a14, 0
    1414:	0578           	l32i.n	a7, a5, 0
    1416:	1ee8           	l32i.n	a14, a14, 4
    1418:	15d8           	l32i.n	a13, a5, 4
    141a:	09f8           	l32i.n	a15, a9, 0
    141c:	16c8           	l32i.n	a12, a6, 4
    141e:	0638           	l32i.n	a3, a6, 0
    1420:	826780        	mull	a6, a7, a8
    1423:	166162        	s32i	a6, a1, 88
    1426:	b257e0        	mulsh	a5, a7, a14
    1429:	8267e0        	mull	a6, a7, a14
    142c:	b24780        	mulsh	a4, a7, a8
    142f:	146152        	s32i	a5, a1, 80
    1432:	126162        	s32i	a6, a1, 72
    1435:	827de0        	mull	a7, a13, a14
    1438:	b25de0        	mulsh	a5, a13, a14
    143b:	b2ed80        	mulsh	a14, a13, a8
    143e:	826d80        	mull	a6, a13, a8
    1441:	b2dfc0        	mulsh	a13, a15, a12
    1444:	19b8           	l32i.n	a11, a9, 4
    1446:	d1d9           	s32i.n	a13, a1, 52
    1448:	21d8           	l32i.n	a13, a1, 8
    144a:	116162        	s32i	a6, a1, 68
    144d:	828f30        	mull	a8, a15, a3
    1450:	826bc0        	mull	a6, a11, a12
    1453:	f189           	s32i.n	a8, a1, 60
    1455:	c169           	s32i.n	a6, a1, 48
    1457:	1288           	l32i.n	a8, a2, 4
    1459:	1d68           	l32i.n	a6, a13, 4
    145b:	176142        	s32i	a4, a1, 92
    145e:	0248           	l32i.n	a4, a2, 0
    1460:	156172        	s32i	a7, a1, 84
    1463:	b27f30        	mulsh	a7, a15, a3
    1466:	1361e2        	s32i	a14, a1, 76
    1469:	106172        	s32i	a7, a1, 64
    146c:	b2ebc0        	mulsh	a14, a11, a12
    146f:	b27b30        	mulsh	a7, a11, a3
    1472:	e1e9           	s32i.n	a14, a1, 56
    1474:	82eb30        	mull	a14, a11, a3
    1477:	b179           	s32i.n	a7, a1, 44
    1479:	827a80        	mull	a7, a10, a8
    147c:	82b680        	mull	a11, a6, a8
    147f:	82ffc0        	mull	a15, a15, a12
    1482:	822a40        	mull	a2, a10, a4
    1485:	b2ca80        	mulsh	a12, a10, a8
    1488:	b2d680        	mulsh	a13, a6, a8
    148b:	b23a40        	mulsh	a3, a10, a4
    148e:	05afb0        	extui	a10, a11, 31, 1
    1491:	057f70        	extui	a7, a7, 31, 1
    1494:	f1b8           	l32i.n	a11, a1, 60
    1496:	b28640        	mulsh	a8, a6, a4
    1499:	824640        	mull	a4, a6, a4
    149c:	906c70        	addx2	a6, a12, a7
    149f:	052f20        	extui	a2, a2, 31, 1
    14a2:	907da0        	addx2	a7, a13, a10
    14a5:	1021d2        	l32i	a13, a1, 64
    14a8:	903320        	addx2	a3, a3, a2
    14ab:	d128           	l32i.n	a2, a1, 52
    14ad:	054f40        	extui	a4, a4, 31, 1
    14b0:	05cfb0        	extui	a12, a11, 31, 1
    14b3:	c1b8           	l32i.n	a11, a1, 48
    14b5:	904840        	addx2	a4, a8, a4
    14b8:	908dc0        	addx2	a8, a13, a12
    14bb:	05fff0        	extui	a15, a15, 31, 1
    14be:	e1d8           	l32i.n	a13, a1, 56
    14c0:	90a2f0        	addx2	a10, a2, a15
    14c3:	b128           	l32i.n	a2, a1, 44
    14c5:	05cfb0        	extui	a12, a11, 31, 1
    14c8:	90bdc0        	addx2	a11, a13, a12
    14cb:	05ffe0        	extui	a15, a14, 31, 1
    14ce:	1221d2        	l32i	a13, a1, 72
    14d1:	90c2f0        	addx2	a12, a2, a15
    14d4:	1421f2        	l32i	a15, a1, 80
    14d7:	162122        	l32i	a2, a1, 88
    14da:	05efd0        	extui	a14, a13, 31, 1
    14dd:	a139           	s32i.n	a3, a1, 40
    14df:	90efe0        	addx2	a14, a15, a14
    14e2:	053f20        	extui	a3, a2, 31, 1
    14e5:	1721f2        	l32i	a15, a1, 92
    14e8:	112122        	l32i	a2, a1, 68
    14eb:	90df30        	addx2	a13, a15, a3
    14ee:	053f20        	extui	a3, a2, 31, 1
    14f1:	132122        	l32i	a2, a1, 76
    14f4:	90f230        	addx2	a15, a2, a3
    14f7:	152122        	l32i	a2, a1, 84
    14fa:	eefa           	add.n	a14, a14, a15
    14fc:	c0f8b0        	sub	a15, a8, a11
    14ff:	8aca           	add.n	a8, a10, a12
    1501:	a1c8           	l32i.n	a12, a1, 40
    1503:	053f20        	extui	a3, a2, 31, 1
    1506:	903530        	addx2	a3, a5, a3
    1509:	c0ac70        	sub	a10, a12, a7
    150c:	c0dd30        	sub	a13, a13, a3
    150f:	764a           	add.n	a7, a6, a4
    1511:	0003c6        	j	1524 <FFT4N+0x1dc>

00001514 <FFT4N+0x1cc>:
    1514:	3158           	l32i.n	a5, a1, 12
    1516:	4198           	l32i.n	a9, a1, 16
    1518:	2138           	l32i.n	a3, a1, 8
    151a:	05d8           	l32i.n	a13, a5, 0
    151c:	15e8           	l32i.n	a14, a5, 4
    151e:	1378           	l32i.n	a7, a3, 4
    1520:	09f8           	l32i.n	a15, a9, 0
    1522:	1988           	l32i.n	a8, a9, 4
    1524:	2161d0        	srai	a6, a13, 1
    1527:	6158           	l32i.n	a5, a1, 24
    1529:	2131a0        	srai	a3, a10, 1
    152c:	21d1f0        	srai	a13, a15, 1
    152f:	661b           	addi.n	a6, a6, 1
    1531:	ad1b           	addi.n	a10, a13, 1
    1533:	216160        	srai	a6, a6, 1
    1536:	331b           	addi.n	a3, a3, 1
    1538:	214170        	srai	a4, a7, 1
    153b:	2171e0        	srai	a7, a14, 1
    153e:	218180        	srai	a8, a8, 1
    1541:	b65a           	add.n	a11, a6, a5
    1543:	c06560        	sub	a6, a5, a6
    1546:	215130        	srai	a5, a3, 1
    1549:	21a1a0        	srai	a10, a10, 1
    154c:	5128           	l32i.n	a2, a1, 20
    154e:	1b21f2        	l32i	a15, a1, 108
    1551:	c5aa           	add.n	a12, a5, a10
    1553:	771b           	addi.n	a7, a7, 1
    1555:	441b           	addi.n	a4, a4, 1
    1557:	881b           	addi.n	a8, a8, 1
    1559:	ecba           	add.n	a14, a12, a11
    155b:	217170        	srai	a7, a7, 1
    155e:	214140        	srai	a4, a4, 1
    1561:	218180        	srai	a8, a8, 1
    1564:	232132        	l32i	a3, a1, 140
    1567:	02e9           	s32i.n	a14, a2, 0
    1569:	d7fa           	add.n	a13, a7, a15
    156b:	e48a           	add.n	a14, a4, a8
    156d:	c07f70        	sub	a7, a15, a7
    1570:	feda           	add.n	a15, a14, a13
    1572:	03f9           	s32i.n	a15, a3, 0
    1574:	c0cbc0        	sub	a12, a11, a12
    1577:	2121f2        	l32i	a15, a1, 132
    157a:	71b8           	l32i.n	a11, a1, 28
    157c:	c04840        	sub	a4, a8, a4
    157f:	c055a0        	sub	a5, a5, a10
    1582:	c08640        	sub	a8, a6, a4
    1585:	c0a750        	sub	a10, a7, a5
    1588:	0f89           	s32i.n	a8, a15, 0
    158a:	c08de0        	sub	a8, a13, a14
    158d:	0ba9           	s32i.n	a10, a11, 0
    158f:	1f21a2        	l32i	a10, a1, 124
    1592:	2021d2        	l32i	a13, a1, 128
    1595:	557a           	add.n	a5, a5, a7
    1597:	0ac9           	s32i.n	a12, a10, 0
    1599:	0d89           	s32i.n	a8, a13, 0
    159b:	1d2182        	l32i	a8, a1, 116
    159e:	1e2172        	l32i	a7, a1, 120
    15a1:	446a           	add.n	a4, a4, a6
    15a3:	31e8           	l32i.n	a14, a1, 12
    15a5:	0849           	s32i.n	a4, a8, 0
    15a7:	0759           	s32i.n	a5, a7, 0
    15a9:	998b           	addi.n	a9, a9, 8
    15ab:	2158           	l32i.n	a5, a1, 8
    15ad:	1c21c2        	l32i	a12, a1, 112
    15b0:	4199           	s32i.n	a9, a1, 16
    15b2:	222192        	l32i	a9, a1, 136
    15b5:	4e8b           	addi.n	a4, a14, 8
    15b7:	3149           	s32i.n	a4, a1, 12
    15b9:	458b           	addi.n	a4, a5, 8
    15bb:	6c1b           	addi.n	a6, a12, 1
    15bd:	2149           	s32i.n	a4, a1, 8
    15bf:	c98b           	addi.n	a12, a9, 8
    15c1:	8148           	l32i.n	a4, a1, 32
    15c3:	1921e2        	l32i	a14, a1, 100
    15c6:	1a2192        	l32i	a9, a1, 104
    15c9:	5e4a           	add.n	a5, a14, a4
    15cb:	e94a           	add.n	a14, a9, a4
    15cd:	182192        	l32i	a9, a1, 96
    15d0:	994a           	add.n	a9, a9, a4
    15d2:	9148           	l32i.n	a4, a1, 36
    15d4:	224a           	add.n	a2, a2, a4
    15d6:	bb4a           	add.n	a11, a11, a4
    15d8:	5129           	s32i.n	a2, a1, 20
    15da:	334a           	add.n	a3, a3, a4
    15dc:	ff4a           	add.n	a15, a15, a4
    15de:	774a           	add.n	a7, a7, a4
    15e0:	884a           	add.n	a8, a8, a4
    15e2:	dd4a           	add.n	a13, a13, a4
    15e4:	aa4a           	add.n	a10, a10, a4
    15e6:	064d           	mov.n	a4, a6
    15e8:	71b9           	s32i.n	a11, a1, 28
    15ea:	092d           	mov.n	a2, a9
    15ec:	056d           	mov.n	a6, a5

000015ee <FFT4N+0x2a6>:
    15ee:	f01d           	retw.n

000015f0 <fix_fft15>:
    15f0:	02e136        	entry	a1, 0x170
    15f3:	01d1d2        	addmi	a13, a1, 0x100
    15f6:	608264        	ae_lq32f.i	aeq2, a2, 24
    15f9:	60c364        	ae_lq32f.i	aeq3, a3, 24
    15fc:	632114        	ae_sq56s.i	aeq2, a1, 8
    15ff:	633124        	ae_sq56s.i	aeq3, a1, 16
    1602:	608244        	ae_lq32f.i	aeq2, a2, 16
    1605:	80cdd2        	addi	a13, a13, -128
    1608:	60c344        	ae_lq32f.i	aeq3, a3, 16
    160b:	01d1e2        	addmi	a14, a1, 0x100
    160e:	632d74        	ae_sq56s.i	aeq2, a13, 56
    1611:	633e94        	ae_sq56s.i	aeq3, a14, -56
    1614:	60c324        	ae_lq32f.i	aeq3, a3, 8
    1617:	20c272        	addi	a7, a2, 32
    161a:	20c362        	addi	a6, a3, 32
    161d:	608224        	ae_lq32f.i	aeq2, a2, 8
    1620:	78c1f2        	addi	a15, a1, 120
    1623:	632f74        	ae_sq56s.i	aeq2, a15, 56
    1626:	633e84        	ae_sq56s.i	aeq3, a14, -64
    1629:	608744        	ae_lq32f.i	aeq2, a7, 16
    162c:	60c644        	ae_lq32f.i	aeq3, a6, 16
    162f:	40c292        	addi	a9, a2, 64
    1632:	40c3b2        	addi	a11, a3, 64
    1635:	632144        	ae_sq56s.i	aeq2, a1, 32
    1638:	633134        	ae_sq56s.i	aeq3, a1, 24
    163b:	608924        	ae_lq32f.i	aeq2, a9, 8
    163e:	60cb24        	ae_lq32f.i	aeq3, a11, 8
    1641:	60c282        	addi	a8, a2, 96
    1644:	60c3a2        	addi	a10, a3, 96
    1647:	632154        	ae_sq56s.i	aeq2, a1, 40
    164a:	633164        	ae_sq56s.i	aeq3, a1, 48
    164d:	608804        	ae_lq32f.i	aeq2, a8, 0
    1650:	60ca04        	ae_lq32f.i	aeq3, a10, 0
    1653:	632174        	ae_sq56s.i	aeq2, a1, 56
    1656:	633f94        	ae_sq56s.i	aeq3, a15, -56
    1659:	608724        	ae_lq32f.i	aeq2, a7, 8
    165c:	60c624        	ae_lq32f.i	aeq3, a6, 8
    165f:	00a452        	movi	a5, 0x400
    1662:	632fa4        	ae_sq56s.i	aeq2, a15, -48
    1665:	633fb4        	ae_sq56s.i	aeq3, a15, -40
    1668:	608904        	ae_lq32f.i	aeq2, a9, 0
    166b:	60cb04        	ae_lq32f.i	aeq3, a11, 0
    166e:	632fc4        	ae_sq56s.i	aeq2, a15, -32
    1671:	633fd4        	ae_sq56s.i	aeq3, a15, -24
    1674:	608964        	ae_lq32f.i	aeq2, a9, 24
    1677:	60cb64        	ae_lq32f.i	aeq3, a11, 24
    167a:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    167d:	600204        	ae_lq32f.i	aeq0, a2, 0
    1680:	01d1c2        	addmi	a12, a1, 0x100
    1683:	d4e2ba2fef 	{ ae_sq56s.i	aeq2, a15, -16; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1688:	633ff4        	ae_sq56s.i	aeq3, a15, -8
    168b:	fc247d484f 	{ ae_lq32f.i	aeq2, a8, 16; ae_roundsq32asym	aeq0, aeq0 }
    1690:	60ca44        	ae_lq32f.i	aeq3, a10, 16
    1693:	d0ccc2        	addi	a12, a12, -48
    1696:	632f04        	ae_sq56s.i	aeq2, a15, 0
    1699:	633f14        	ae_sq56s.i	aeq3, a15, 8
    169c:	60cb44        	ae_lq32f.i	aeq3, a11, 16
    169f:	608944        	ae_lq32f.i	aeq2, a9, 16
    16a2:	0c5d           	mov.n	a5, a12
    16a4:	632f24        	ae_sq56s.i	aeq2, a15, 16
    16a7:	633f34        	ae_sq56s.i	aeq3, a15, 24
    16aa:	60ca24        	ae_lq32f.i	aeq3, a10, 8
    16ad:	608824        	ae_lq32f.i	aeq2, a8, 8
    16b0:	604304        	ae_lq32f.i	aeq1, a3, 0
    16b3:	d4e3b9c50f 	{ ae_sq32f.iu	aeq0, a5, 0; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    16b8:	632f54        	ae_sq56s.i	aeq2, a15, 40
    16bb:	fc247dc11f 	{ ae_lq56.i	aeq2, a1, 8; ae_roundsq32asym	aeq0, aeq0 }
    16c0:	d7e2ba3f6f 	{ ae_sq56s.i	aeq3, a15, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16c5:	60c704        	ae_lq32f.i	aeq3, a7, 0
    16c8:	633114        	ae_sq56s.i	aeq3, a1, 8
    16cb:	61c124        	ae_lq56.i	aeq3, a1, 16
    16ce:	d6e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    16d3:	fc347dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_roundsq32asym	aeq0, aeq2 }
    16d8:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16dd:	d7e2bda13f 	{ ae_lq56.i	aeq1, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16e2:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16e7:	fc347dc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_roundsq32asym	aeq0, aeq2 }
    16ec:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16f1:	d7e2bda16f 	{ ae_lq56.i	aeq1, a1, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16f6:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16fb:	fc347dc17f 	{ ae_lq56.i	aeq2, a1, 56; ae_roundsq32asym	aeq0, aeq2 }
    1700:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    1705:	d7e2bdaf9f 	{ ae_lq56.i	aeq1, a15, -56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    170a:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    170f:	fc347dcfaf 	{ ae_lq56.i	aeq2, a15, -48; ae_roundsq32asym	aeq0, aeq2 }
    1714:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    1719:	d7e2bdafbf 	{ ae_lq56.i	aeq1, a15, -40; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    171e:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1723:	fc347dcfcf 	{ ae_lq56.i	aeq2, a15, -32; ae_roundsq32asym	aeq0, aeq2 }
    1728:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    172d:	d7e2bdafdf 	{ ae_lq56.i	aeq1, a15, -24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1732:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1737:	fc347dcfef 	{ ae_lq56.i	aeq2, a15, -16; ae_roundsq32asym	aeq0, aeq2 }
    173c:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    1741:	d7e2bdafff 	{ ae_lq56.i	aeq1, a15, -8; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1746:	d4e3fd660f 	{ ae_lq32f.i	aeq3, a6, 0; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    174b:	fc3479c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq2 }
    1750:	618f04        	ae_lq56.i	aeq2, a15, 0
    1753:	d7e2ba312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1758:	60c764        	ae_lq32f.i	aeq3, a7, 24
    175b:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    1760:	614f14        	ae_lq56.i	aeq1, a15, 8
    1763:	d4e3fa3f4f 	{ ae_sq56s.i	aeq3, a15, 32; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1768:	61cd74        	ae_lq56.i	aeq3, a13, 56
    176b:	fc3479c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq2 }
    1770:	d7e3fdce9f 	{ ae_lq56.i	aeq2, a14, -56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1775:	fd2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq1, aeq1 }
    177a:	d7e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    177f:	fd3c7def2f 	{ ae_lq56.i	aeq3, a15, 16; ae_roundsq32asym	aeq1, aeq3 }
    1784:	fd3479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq1, aeq2 }
    1789:	d7e3fdcf3f 	{ ae_lq56.i	aeq2, a15, 24; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    178e:	d7e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1793:	fd3c7def5f 	{ ae_lq56.i	aeq3, a15, 40; ae_roundsq32asym	aeq1, aeq3 }
    1798:	fd3479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq1, aeq2 }
    179d:	d7e3fdcf6f 	{ ae_lq56.i	aeq2, a15, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    17a2:	d7e2bd8f7f 	{ ae_lq56.i	aeq0, a15, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    17a7:	d4e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    17ac:	fd3c7dee8f 	{ ae_lq56.i	aeq3, a14, -64; ae_roundsq32asym	aeq1, aeq3 }
    17b1:	d7e3f9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    17b6:	fd347dc11f 	{ ae_lq56.i	aeq2, a1, 8; ae_roundsq32asym	aeq1, aeq2 }
    17bb:	fc2479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    17c0:	d7e2bda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    17c5:	ff3c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq3, aeq3 }
    17ca:	d4e3f9f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    17cf:	fe347def4f 	{ ae_lq56.i	aeq3, a15, 32; ae_roundsq32asym	aeq2, aeq2 }
    17d4:	d7e3fd066f 	{ ae_lq32f.i	aeq0, a6, 24; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    17d9:	d4e2b9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    17de:	fd2c53a22f 	{ or	a10, a2, a2; ae_roundsq32asym	aeq1, aeq1 }
    17e3:	ff3c79d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq3, aeq3 }
    17e8:	fc2479f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    17ed:	624514        	ae_sq32f.iu	aeq0, a5, 4
    17f0:	fa2751        	l32r	a5, 8c (2ac <fix_fft15_stage>)
    17f3:	03bd           	mov.n	a11, a3
    17f5:	04dd           	mov.n	a13, a4
    17f7:	0005e0        	callx8	a5
    17fa:	f01d           	retw.n

000017fc <fix_fft20>:
    17fc:	030136        	entry	a1, 0x180
    17ff:	026d           	mov.n	a6, a2
    1801:	00a452        	movi	a5, 0x400
    1804:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    1807:	600204        	ae_lq32f.i	aeq0, a2, 0
    180a:	01d1e2        	addmi	a14, a1, 0x100
    180d:	d4e2bd230f 	{ ae_lq32f.i	aeq1, a3, 0; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1812:	d4e3c781de 	{ addi	a13, a1, 120; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1817:	fc24430eee 	{ addi	a14, a14, 48; ae_roundsq32asym	aeq0, aeq0 }
    181c:	fd2c770def 	{ ae_sp24x2s.i	aep0, a13, -16; ae_roundsq32asym	aeq1, aeq1 }
    1821:	80a0d2        	movi	a13, 128
    1824:	60a2d4        	ae_lq32f.x	aeq2, a2, a13
    1827:	d7e2935eef 	{ or	a5, a14, a14; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    182c:	60fd34        	ae_lq32f.xu	aeq3, a13, a3
    182f:	d7e3f9c50f 	{ ae_sq32f.iu	aeq0, a5, 0; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1834:	fe344602fe 	{ addi	a15, a2, 96; ae_roundsq32asym	aeq2, aeq2 }
    1839:	ff3c46037e 	{ addi	a7, a3, 96; ae_roundsq32asym	aeq3, aeq3 }
    183e:	625514        	ae_sq32f.iu	aeq1, a5, 4
    1841:	600f04        	ae_lq32f.i	aeq0, a15, 0
    1844:	d4e2bd270f 	{ ae_lq32f.i	aeq1, a7, 0; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1849:	d4e3f9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    184e:	fc244402ae 	{ addi	a10, a2, 64; ae_roundsq32asym	aeq0, aeq0 }
    1853:	21f9           	s32i.n	a15, a1, 8
    1855:	78c1f2        	addi	a15, a1, 120
    1858:	627514        	ae_sq32f.iu	aeq3, a5, 4
    185b:	608a04        	ae_lq32f.i	aeq2, a10, 0
    185e:	d7e2ba1fdf 	{ ae_sq56s.i	aeq1, a15, -24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1863:	60c784        	ae_lq32f.i	aeq3, a7, -32
    1866:	fe344403ce 	{ addi	a12, a3, 64; ae_roundsq32asym	aeq2, aeq2 }
    186b:	d7e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1870:	610fd4        	ae_lq56.i	aeq0, a15, -24
    1873:	fc247d2a8f 	{ ae_lq32f.i	aeq1, a10, -32; ae_roundsq32asym	aeq0, aeq0 }
    1878:	d4e3c2029e 	{ addi	a9, a2, 32; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    187d:	ff3c42038e 	{ addi	a8, a3, 32; ae_roundsq32asym	aeq3, aeq3 }
    1882:	fd2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq1, aeq1 }
    1887:	600804        	ae_lq32f.i	aeq0, a8, 0
    188a:	d4e2b9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    188f:	627514        	ae_sq32f.iu	aeq3, a5, 4
    1892:	fc2479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    1897:	624514        	ae_sq32f.iu	aeq0, a5, 4
    189a:	01d1b2        	addmi	a11, a1, 0x100
    189d:	f9f351        	l32r	a5, 6c (164 <fix_fft5_stage>)
    18a0:	276142        	s32i	a4, a1, 156
    18a3:	2461a2        	s32i	a10, a1, 144
    18a6:	2361c2        	s32i	a12, a1, 140
    18a9:	7cc242        	addi	a4, a2, 124
    18ac:	01d1a2        	addmi	a10, a1, 0x100
    18af:	bb4b           	addi.n	a11, a11, 4
    18b1:	0ecd           	mov.n	a12, a14
    18b3:	256172        	s32i	a7, a1, 148
    18b6:	8139           	s32i.n	a3, a1, 32
    18b8:	61d9           	s32i.n	a13, a1, 24
    18ba:	092d           	mov.n	a2, a9
    18bc:	a199           	s32i.n	a9, a1, 40
    18be:	083d           	mov.n	a3, a8
    18c0:	166142        	s32i	a4, a1, 88
    18c3:	1861a2        	s32i	a10, a1, 96
    18c6:	0e7d           	mov.n	a7, a14
    18c8:	0005e0        	callx8	a5
    18cb:	78c182        	addi	a8, a1, 120
    18ce:	600224        	ae_lq32f.i	aeq0, a2, 8
    18d1:	5408e4        	ae_lp24x2.i	aep0, a8, -16
    18d4:	d4e2f061de 	{ l32i	a13, a1, 24; ae_mulfq32sp16u.l	aeq1, aeq0, aep0 }
    18d9:	81c8           	l32i.n	a12, a1, 32
    18db:	fd2c53a77f 	{ or	a10, a7, a7; ae_roundsq32asym	aeq1, aeq1 }
    18e0:	21e8           	l32i.n	a14, a1, 8
    18e2:	625a04        	ae_sq32f.iu	aeq1, a10, 0
    18e5:	604434        	ae_lq32f.i	aeq1, a4, 12
    18e8:	2521f2        	l32i	a15, a1, 148
    18eb:	631174        	ae_sq56s.i	aeq1, a1, 56
    18ee:	604d24        	ae_lq32f.i	aeq1, a13, 8
    18f1:	600c24        	ae_lq32f.i	aeq0, a12, 8
    18f4:	631814        	ae_sq56s.i	aeq1, a8, 8
    18f7:	604e24        	ae_lq32f.i	aeq1, a14, 8
    18fa:	242122        	l32i	a2, a1, 144
    18fd:	6318a4        	ae_sq56s.i	aeq1, a8, -48
    1900:	604f24        	ae_lq32f.i	aeq1, a15, 8
    1903:	630124        	ae_sq56s.i	aeq0, a1, 16
    1906:	232142        	l32i	a4, a1, 140
    1909:	608324        	ae_lq32f.i	aeq2, a3, 8
    190c:	d6e2ba189f 	{ ae_sq56s.i	aeq1, a8, -56; ae_mulfq32sp16u.l	aeq0, aeq2, aep0 }
    1911:	614124        	ae_lq56.i	aeq1, a1, 16
    1914:	d5e3bd662f 	{ ae_lq32f.i	aeq3, a6, 8; ae_mulfq32sp16u.l	aeq2, aeq1, aep0 }
    1919:	d7e3fd222f 	{ ae_lq32f.i	aeq1, a2, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    191e:	fc247a116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_roundsq32asym	aeq0, aeq0 }
    1923:	604424        	ae_lq32f.i	aeq1, a4, 8
    1926:	631124        	ae_sq56s.i	aeq1, a1, 16
    1929:	614174        	ae_lq56.i	aeq1, a1, 56
    192c:	fc3c79ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq3 }
    1931:	d4e3fde81f 	{ ae_lq56.i	aeq3, a8, 8; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1936:	fc3479ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq2 }
    193b:	d7e3fdc8af 	{ ae_lq56.i	aeq2, a8, -48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1940:	fc2c79ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq1 }
    1945:	d7e2bda89f 	{ ae_lq56.i	aeq1, a8, -56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    194a:	d4e3f9ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    194f:	fc3c7de16f 	{ ae_lq56.i	aeq3, a1, 48; ae_roundsq32asym	aeq0, aeq3 }
    1954:	fc3479ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq2 }
    1959:	d7e3fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    195e:	d7e2b9ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1963:	fd2c53c77f 	{ or	a12, a7, a7; ae_roundsq32asym	aeq1, aeq1 }
    1968:	fd3c79da1f 	{ ae_sq32f.iu	aeq1, a10, 4; ae_roundsq32asym	aeq1, aeq3 }
    196d:	ff3479da1f 	{ ae_sq32f.iu	aeq1, a10, 4; ae_roundsq32asym	aeq3, aeq2 }
    1972:	627a14        	ae_sq32f.iu	aeq3, a10, 4
    1975:	01d1b2        	addmi	a11, a1, 0x100
    1978:	01d1a2        	addmi	a10, a1, 0x100
    197b:	d0caa2        	addi	a10, a10, -48
    197e:	d4cbb2        	addi	a11, a11, -44
    1981:	146132        	s32i	a3, a1, 80
    1984:	2061a2        	s32i	a10, a1, 128
    1987:	0005e0        	callx8	a5
    198a:	78c1a2        	addi	a10, a1, 120
    198d:	600244        	ae_lq32f.i	aeq0, a2, 16
    1990:	540ae4        	ae_lp24x2.i	aep0, a10, -16
    1993:	d4e2b081de 	{ l32i	a13, a1, 32; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1998:	604344        	ae_lq32f.i	aeq1, a3, 16
    199b:	fc2453877f 	{ or	a8, a7, a7; ae_roundsq32asym	aeq0, aeq0 }
    19a0:	d4e3f1613e 	{ l32i	a3, a1, 88; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    19a5:	a1c8           	l32i.n	a12, a1, 40
    19a7:	624804        	ae_sq32f.iu	aeq0, a8, 0
    19aa:	600644        	ae_lq32f.i	aeq0, a6, 16
    19ad:	61e8           	l32i.n	a14, a1, 24
    19af:	608444        	ae_lq32f.i	aeq2, a4, 16
    19b2:	630aa4        	ae_sq56s.i	aeq0, a10, -48
    19b5:	600d44        	ae_lq32f.i	aeq0, a13, 16
    19b8:	2148           	l32i.n	a4, a1, 8
    19ba:	d6e2ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq2, aep0 }
    19bf:	608354        	ae_lq32f.i	aeq2, a3, 20
    19c2:	fc2472512e 	{ l32i	a2, a1, 148; ae_roundsq32asym	aeq0, aeq0 }
    19c7:	60cc44        	ae_lq32f.i	aeq3, a12, 16
    19ca:	d7e3fa2a9f 	{ ae_sq56s.i	aeq2, a10, -56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    19cf:	608e44        	ae_lq32f.i	aeq2, a14, 16
    19d2:	632174        	ae_sq56s.i	aeq2, a1, 56
    19d5:	608444        	ae_lq32f.i	aeq2, a4, 16
    19d8:	632af4        	ae_sq56s.i	aeq2, a10, -8
    19db:	608244        	ae_lq32f.i	aeq2, a2, 16
    19de:	632a04        	ae_sq56s.i	aeq2, a10, 0
    19e1:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    19e6:	631164        	ae_sq56s.i	aeq1, a1, 48
    19e9:	618aa4        	ae_lq56.i	aeq2, a10, -48
    19ec:	d6e2fde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    19f1:	d7e3bde16f 	{ ae_lq56.i	aeq3, a1, 48; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    19f6:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    19fb:	61ca94        	ae_lq56.i	aeq3, a10, -56
    19fe:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1a03:	d7e3fda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1a08:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1a0d:	fc347dcaff 	{ ae_lq56.i	aeq2, a10, -8; ae_roundsq32asym	aeq0, aeq2 }
    1a12:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1a17:	fc3c7dea0f 	{ ae_lq56.i	aeq3, a10, 0; ae_roundsq32asym	aeq0, aeq3 }
    1a1c:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1a21:	fd2c53955f 	{ or	a9, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    1a26:	01d1b2        	addmi	a11, a1, 0x100
    1a29:	01d1f2        	addmi	a15, a1, 0x100
    1a2c:	fe3479d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq2, aeq2 }
    1a31:	ff3c4a0fae 	{ addi	a10, a15, -96; ae_roundsq32asym	aeq3, aeq3 }
    1a36:	626814        	ae_sq32f.iu	aeq2, a8, 4
    1a39:	a4cbb2        	addi	a11, a11, -92
    1a3c:	07cd           	mov.n	a12, a7
    1a3e:	075d           	mov.n	a5, a7
    1a40:	627814        	ae_sq32f.iu	aeq3, a8, 4
    1a43:	2661a2        	s32i	a10, a1, 152
    1a46:	097d           	mov.n	a7, a9
    1a48:	0009e0        	callx8	a9
    1a4b:	78c1b2        	addi	a11, a1, 120
    1a4e:	604464        	ae_lq32f.i	aeq1, a4, 24
    1a51:	540be4        	ae_lp24x2.i	aep0, a11, -16
    1a54:	d4e3f2318e 	{ l32i	a8, a1, 140; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1a59:	81d8           	l32i.n	a13, a1, 32
    1a5b:	079d           	mov.n	a9, a7
    1a5d:	057d           	mov.n	a7, a5
    1a5f:	fd2c7d026f 	{ ae_lq32f.i	aeq0, a2, 24; ae_roundsq32asym	aeq1, aeq1 }
    1a64:	d4e2b2414e 	{ l32i	a4, a1, 144; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1a69:	608864        	ae_lq32f.i	aeq2, a8, 24
    1a6c:	625704        	ae_sq32f.iu	aeq1, a7, 0
    1a6f:	604664        	ae_lq32f.i	aeq1, a6, 24
    1a72:	a1a8           	l32i.n	a10, a1, 40
    1a74:	632114        	ae_sq56s.i	aeq2, a1, 8
    1a77:	1421c2        	l32i	a12, a1, 80
    1a7a:	631bb4        	ae_sq56s.i	aeq1, a11, -40
    1a7d:	604d64        	ae_lq32f.i	aeq1, a13, 24
    1a80:	631144        	ae_sq56s.i	aeq1, a1, 32
    1a83:	614114        	ae_lq56.i	aeq1, a1, 8
    1a86:	61e8           	l32i.n	a14, a1, 24
    1a88:	60c464        	ae_lq32f.i	aeq3, a4, 24
    1a8b:	d4e3ba015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1a90:	d7e3fd237f 	{ ae_lq32f.i	aeq1, a3, 28; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1a95:	608a64        	ae_lq32f.i	aeq2, a10, 24
    1a98:	ff3c7a1bcf 	{ ae_sq56s.i	aeq1, a11, -32; ae_roundsq32asym	aeq3, aeq3 }
    1a9d:	614154        	ae_lq56.i	aeq1, a1, 40
    1aa0:	632124        	ae_sq56s.i	aeq2, a1, 16
    1aa3:	fc2c7a011f 	{ ae_sq56s.i	aeq0, a1, 8; ae_roundsq32asym	aeq0, aeq1 }
    1aa8:	604e64        	ae_lq32f.i	aeq1, a14, 24
    1aab:	624714        	ae_sq32f.iu	aeq0, a7, 4
    1aae:	631134        	ae_sq56s.i	aeq1, a1, 24
    1ab1:	614124        	ae_lq56.i	aeq1, a1, 16
    1ab4:	d4e3fd4c6f 	{ ae_lq32f.i	aeq2, a12, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1ab9:	d7e2b9f71f 	{ ae_sq32f.iu	aeq3, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1abe:	61c114        	ae_lq56.i	aeq3, a1, 8
    1ac1:	fc3c7debbf 	{ ae_lq56.i	aeq3, a11, -40; ae_roundsq32asym	aeq0, aeq3 }
    1ac6:	fc2c79c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_roundsq32asym	aeq0, aeq1 }
    1acb:	d7e3fda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1ad0:	d4e3f9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1ad5:	fc347dcbcf 	{ ae_lq56.i	aeq2, a11, -32; ae_roundsq32asym	aeq0, aeq2 }
    1ada:	d7e2b9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1adf:	fc3c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq0, aeq3 }
    1ae4:	d7e3f9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1ae9:	fd2c53a55f 	{ or	a10, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    1aee:	01d1f2        	addmi	a15, a1, 0x100
    1af1:	fe3479d71f 	{ ae_sq32f.iu	aeq1, a7, 4; ae_roundsq32asym	aeq2, aeq2 }
    1af6:	ff3c434fbe 	{ addi	a11, a15, 52; ae_roundsq32asym	aeq3, aeq3 }
    1afb:	626714        	ae_sq32f.iu	aeq2, a7, 4
    1afe:	05cd           	mov.n	a12, a5
    1b00:	627714        	ae_sq32f.iu	aeq3, a7, 4
    1b03:	054d           	mov.n	a4, a5
    1b05:	0009e0        	callx8	a9
    1b08:	2721b2        	l32i	a11, a1, 156
    1b0b:	182122        	l32i	a2, a1, 96
    1b0e:	262152        	l32i	a5, a1, 152
    1b11:	202132        	l32i	a3, a1, 128
    1b14:	5c2204        	ae_lp24x2f.i	aep2, a2, 0
    1b17:	5c5504        	ae_lp24x2f.i	aep5, a5, 0
    1b1a:	daa92f330f 	{ ae_lp24x2f.i	aep3, a3, 0; ae_addsp24s	aep4, aep2, aep5 }
    1b1f:	ddaaaf740f 	{ ae_lp24x2f.i	aep7, a4, 0; ae_subsp24s	aep2, aep2, aep5 }
    1b24:	daed53a44f 	{ or	a10, a4, a4; ae_addsp24s	aep5, aep3, aep7 }
    1b29:	ce3c           	movi.n	a14, 60
    1b2b:	b09bb0        	addx8	a9, a11, a11
    1b2e:	ddeeef151f 	{ ae_lp24x2f.i	aep1, a5, 8; ae_subsp24s	aep3, aep3, aep7 }
    1b33:	054d           	mov.n	a4, a5
    1b35:	5c6314        	ae_lp24x2f.i	aep6, a3, 8
    1b38:	035d           	mov.n	a5, a3
    1b3a:	cd4c           	movi.n	a13, 76
    1b3c:	0b3d           	mov.n	a3, a11
    1b3e:	a07bb0        	addx4	a7, a11, a11
    1b41:	11cbc0        	slli	a12, a11, 4
    1b44:	d1bbe0        	mul16s	a11, a11, a14
    1b47:	d1e3d0        	mul16s	a14, a3, a13
    1b4a:	11d9e0        	slli	a13, a9, 2
    1b4d:	483c           	movi.n	a8, 52
    1b4f:	5c0214        	ae_lp24x2f.i	aep0, a2, 8
    1b52:	db215481cf 	{ s32i.n	a12, a1, 32; ae_addsp24s	aep7, aep0, aep1 }
    1b57:	dc22b7511f 	{ ae_sp24x2s.i	aep5, a1, 8; ae_subsp24s	aep0, aep0, aep1 }
    1b5c:	78c1c2        	addi	a12, a1, 120
    1b5f:	2361d2        	s32i	a13, a1, 140
    1b62:	11d9d0        	slli	a13, a9, 3
    1b65:	d19380        	mul16s	a9, a3, a8
    1b68:	5c5a14        	ae_lp24x2f.i	aep5, a10, 8
    1b6b:	ddbaf73caf 	{ ae_sp24x2s.i	aep3, a12, -48; ae_subsp24s	aep3, aep6, aep5 }
    1b70:	2461d2        	s32i	a13, a1, 144
    1b73:	256192        	s32i	a9, a1, 148
    1b76:	11d3b0        	slli	a13, a3, 5
    1b79:	562134        	ae_sp24x2s.i	aep2, a1, 24
    1b7c:	dbb9777cbf 	{ ae_sp24x2s.i	aep7, a12, -40; ae_addsp24s	aep7, aep6, aep5 }
    1b81:	560124        	ae_sp24x2s.i	aep0, a1, 16
    1b84:	1661d2        	s32i	a13, a1, 88
    1b87:	5c0224        	ae_lp24x2f.i	aep0, a2, 16
    1b8a:	5c5424        	ae_lp24x2f.i	aep5, a4, 16
    1b8d:	dba137316f 	{ ae_sp24x2s.i	aep3, a1, 48; ae_addsp24s	aep6, aep0, aep5 }
    1b92:	dca2af252f 	{ ae_lp24x2f.i	aep2, a5, 16; ae_subsp24s	aep0, aep0, aep5 }
    1b97:	1139           	s32i.n	a3, a1, 4
    1b99:	f08330        	subx8	a8, a3, a3
    1b9c:	11c7d0        	slli	a12, a7, 3
    1b9f:	11f7e0        	slli	a15, a7, 2
    1ba2:	907330        	addx2	a7, a3, a3
    1ba5:	78c132        	addi	a3, a1, 120
    1ba8:	5c5a24        	ae_lp24x2f.i	aep5, a10, 16
    1bab:	dba937639f 	{ ae_sp24x2s.i	aep6, a3, -56; ae_addsp24s	aep6, aep2, aep5 }
    1bb0:	dcaab7015f 	{ ae_sp24x2s.i	aep0, a1, 40; ae_subsp24s	aep0, aep2, aep5 }
    1bb5:	5c1234        	ae_lp24x2f.i	aep1, a2, 24
    1bb8:	5c3434        	ae_lp24x2f.i	aep3, a4, 24
    1bbb:	db6537630f 	{ ae_sp24x2s.i	aep6, a3, 0; ae_addsp24s	aep6, aep1, aep3 }
    1bc0:	dc66b7017f 	{ ae_sp24x2s.i	aep0, a1, 56; ae_subsp24s	aep0, aep1, aep3 }
    1bc5:	5c5534        	ae_lp24x2f.i	aep5, a5, 24
    1bc8:	5c3a34        	ae_lp24x2f.i	aep3, a10, 24
    1bcb:	db753763ff 	{ ae_sp24x2s.i	aep6, a3, -8; ae_addsp24s	aep6, aep5, aep3 }
    1bd0:	de76f0311f 	{ ae_lp24x2.i	aep3, a1, 8; ae_subsp24s	aep5, aep5, aep3 }
    1bd5:	d9713703ef 	{ ae_sp24x2s.i	aep0, a3, -16; ae_addsp24s	aep2, aep4, aep3 }
    1bda:	dd72ef044f 	{ ae_lp24x2f.i	aep0, a4, 32; ae_subsp24s	aep3, aep4, aep3 }
    1bdf:	040c           	movi.n	a4, 0
    1be1:	5f2644        	ae_sp24x2f.x	aep2, a6, a4
    1be4:	5c1244        	ae_lp24x2f.i	aep1, a2, 32
    1be7:	da0507814e 	{ addi	a4, a1, 120; ae_addsp24s	aep4, aep1, aep0 }
    1bec:	1138           	l32i.n	a3, a1, 4
    1bee:	dc06a936cf 	{ ae_sp24x2f.x	aep3, a6, a12; ae_subsp24s	aep0, aep1, aep0 }
    1bf3:	5434a4        	ae_lp24x2.i	aep3, a4, -48
    1bf6:	fe783744df 	{ ae_sp24x2s.i	aep4, a4, -24; ae_negsp24s	aep4, aep3 }
    1bfb:	dc71f7011f 	{ ae_sp24x2s.i	aep0, a1, 8; ae_selp24.lh	aep1, aep4, aep3 }
    1c00:	540134        	ae_lp24x2.i	aep0, a1, 24
    1c03:	da212f254f 	{ ae_lp24x2f.i	aep2, a5, 32; ae_addsp24s	aep4, aep0, aep1 }
    1c08:	dc22af3a4f 	{ ae_lp24x2f.i	aep3, a10, 32; ae_subsp24s	aep0, aep0, aep1 }
    1c0d:	d8696946bf 	{ ae_sp24x2f.x	aep4, a6, a11; ae_addsp24s	aep1, aep2, aep3 }
    1c12:	dd6aa906ff 	{ ae_sp24x2f.x	aep0, a6, a15; ae_subsp24s	aep2, aep2, aep3 }
    1c17:	5404b4        	ae_lp24x2.i	aep0, a4, -40
    1c1a:	dae130815e 	{ l32i	a5, a1, 32; ae_addsp24s	aep4, aep0, aep7 }
    1c1f:	dde2f0016f 	{ ae_lp24x2.i	aep0, a1, 48; ae_subsp24s	aep3, aep0, aep7 }
    1c24:	ff187231ae 	{ l32i	a10, a1, 140; ae_negsp24s	aep7, aep0 }
    1c29:	1198d0        	slli	a9, a8, 3
    1c2c:	dc1da9465f 	{ ae_sp24x2f.x	aep4, a6, a5; ae_selp24.lh	aep0, aep7, aep0 }
    1c31:	5f3694        	ae_sp24x2f.x	aep3, a6, a9
    1c34:	543124        	ae_lp24x2.i	aep3, a1, 16
    1c37:	db0d70449f 	{ ae_lp24x2.i	aep4, a4, -56; ae_addsp24s	aep7, aep3, aep0 }
    1c3c:	dc0ea976ef 	{ ae_sp24x2f.x	aep7, a6, a14; ae_subsp24s	aep0, aep3, aep0 }
    1c41:	547404        	ae_lp24x2.i	aep7, a4, 0
    1c44:	d9f17161be 	{ l32i	a11, a1, 88; ae_addsp24s	aep3, aep4, aep7 }
    1c49:	dff2f044ff 	{ ae_lp24x2.i	aep4, a4, -8; ae_subsp24s	aep7, aep4, aep7 }
    1c4e:	2421c2        	l32i	a12, a1, 144
    1c51:	d8d12906af 	{ ae_sp24x2f.x	aep0, a6, a10; ae_addsp24s	aep0, aep4, aep6 }
    1c56:	ded2b0617f 	{ ae_lp24x2.i	aep6, a1, 56; ae_subsp24s	aep4, aep4, aep6 }
    1c5b:	fdd86936bf 	{ ae_sp24x2f.x	aep3, a6, a11; ae_negsp24s	aep3, aep6 }
    1c60:	ddcdf251ee 	{ l32i	a14, a1, 148; ae_selp24.lh	aep3, aep3, aep6 }
    1c65:	5f76c4        	ae_sp24x2f.x	aep7, a6, a12
    1c68:	547154        	ae_lp24x2.i	aep7, a1, 40
    1c6b:	07f364        	ae_addsp24s	aep6, aep7, aep3
    1c6e:	11d7e0        	slli	a13, a7, 2
    1c71:	dd7ee966df 	{ ae_sp24x2f.x	aep6, a6, a13; ae_subsp24s	aep3, aep7, aep3 }
    1c76:	ffb86936ef 	{ ae_sp24x2f.x	aep3, a6, a14; ae_negsp24s	aep7, aep5 }
    1c7b:	1127c0        	slli	a2, a7, 4
    1c7e:	11f3d0        	slli	a15, a3, 3
    1c81:	fd5869062f 	{ ae_sp24x2f.x	aep0, a6, a2; ae_negsp24s	aep3, aep2 }
    1c86:	debde946ff 	{ ae_sp24x2f.x	aep4, a6, a15; ae_selp24.lh	aep5, aep7, aep5 }
    1c8b:	dc4db064ef 	{ ae_lp24x2.i	aep6, a4, -16; ae_selp24.lh	aep0, aep3, aep2 }
    1c90:	dbb9402ccf 	{ movi	a12, 44; ae_addsp24s	aep7, aep6, aep5 }
    1c95:	ddbaf044df 	{ ae_lp24x2.i	aep4, a4, -24; ae_subsp24s	aep3, aep6, aep5 }
    1c9a:	1188e0        	slli	a8, a8, 2
    1c9d:	11b3a0        	slli	a11, a3, 6
    1ca0:	d1e3c0        	mul16s	a14, a3, a12
    1ca3:	da3170611f 	{ ae_lp24x2.i	aep6, a1, 8; ae_addsp24s	aep5, aep4, aep1 }
    1ca8:	db1969768f 	{ ae_sp24x2f.x	aep7, a6, a8; ae_addsp24s	aep7, aep6, aep0 }
    1cad:	a0d3b0        	addx4	a13, a3, a11
    1cb0:	11a3e0        	slli	a10, a3, 2
    1cb3:	1177d0        	slli	a7, a7, 3
    1cb6:	dc32e936df 	{ ae_sp24x2f.x	aep3, a6, a13; ae_subsp24s	aep1, aep4, aep1 }
    1cbb:	dc1aa956bf 	{ ae_sp24x2f.x	aep5, a6, a11; ae_subsp24s	aep0, aep6, aep0 }
    1cc0:	5f1674        	ae_sp24x2f.x	aep1, a6, a7
    1cc3:	5f76e4        	ae_sp24x2f.x	aep7, a6, a14
    1cc6:	5f06a4        	ae_sp24x2f.x	aep0, a6, a10
    1cc9:	f01d           	retw.n

00001ccb <fix_fft20+0x4cf>:
	...

00001ccc <__do_global_ctors_aux>:
    1ccc:	004136        	entry	a1, 32
    1ccf:	f8f031        	l32r	a3, 90 (20ac <__CTOR_END__>)
    1cd2:	fcc322        	addi	a2, a3, -4
    1cd5:	0228           	l32i.n	a2, a2, 0
    1cd7:	f8c332        	addi	a3, a3, -8
    1cda:	0a0226        	beqi	a2, -1, 1ce8 <__do_global_ctors_aux+0x1c>

00001cdd <__do_global_ctors_aux+0x11>:
    1cdd:	0002e0        	callx8	a2
    1ce0:	0328           	l32i.n	a2, a3, 0
    1ce2:	fcc332        	addi	a3, a3, -4
    1ce5:	f40266        	bnei	a2, -1, 1cdd <__do_global_ctors_aux+0x11>
    1ce8:	f01d           	retw.n

00001cea <__do_global_ctors_aux+0x1e>:
	...

00001cec <LC3Plus_lc3_scratch_init>:
    1cec:	004136        	entry	a1, 32
    1cef:	1f0c           	movi.n	a15, 1
    1cf1:	401400        	ssl	a4
    1cf4:	a14f00        	sll	a4, a15
    1cf7:	026d           	mov.n	a6, a2
    1cf9:	740b           	addi.n	a7, a4, -1
    1cfb:	0f0277        	bnone	a2, a7, 1d0e <LC3Plus_lc3_scratch_init+0x22>
    1cfe:	102760        	and	a2, a7, a6
    1d01:	c08420        	sub	a8, a4, a2
    1d04:	020c           	movi.n	a2, 0
    1d06:	3a3387        	bltu	a3, a8, 1d44 <LC3Plus_lc3_scratch_init+0x58>
    1d09:	686a           	add.n	a6, a8, a6
    1d0b:	c03380        	sub	a3, a3, a8

00001d0e <LC3Plus_lc3_scratch_init+0x22>:
    1d0e:	c81c           	movi.n	a8, 28
    1d10:	109780        	and	a9, a7, a8
    1d13:	c07490        	sub	a7, a4, a9
    1d16:	1cc772        	addi	a7, a7, 28
    1d19:	020c           	movi.n	a2, 0
    1d1b:	837890        	moveqz	a7, a8, a9
    1d1e:	6659           	s32i.n	a5, a6, 24
    1d20:	5629           	s32i.n	a2, a6, 20
    1d22:	4629           	s32i.n	a2, a6, 16
    1d24:	1c3377        	bltu	a3, a7, 1d44 <LC3Plus_lc3_scratch_init+0x58>
    1d27:	258c           	beqz.n	a5, 1d2d <LC3Plus_lc3_scratch_init+0x41>
    1d29:	5679           	s32i.n	a7, a6, 20
    1d2b:	4679           	s32i.n	a7, a6, 16
    1d2d:	f41b           	addi.n	a15, a4, 1
    1d2f:	603040        	neg	a3, a4
    1d32:	267a           	add.n	a2, a6, a7
    1d34:	0e0c           	movi.n	a14, 0
    1d36:	103f30        	and	a3, a15, a3
    1d39:	0629           	s32i.n	a2, a6, 0
    1d3b:	062d           	mov.n	a2, a6
    1d3d:	2649           	s32i.n	a4, a6, 8
    1d3f:	0256e2        	s16i	a14, a6, 4
    1d42:	3639           	s32i.n	a3, a6, 12
    1d44:	f01d           	retw.n

00001d46 <LC3Plus_lc3_scratch_init+0x5a>:
	...

00001d48 <LC3Plus_lc3_scratch_push>:
    1d48:	004136        	entry	a1, 32
    1d4b:	024d           	mov.n	a4, a2
    1d4d:	fe7c           	movi.n	a14, -1
    1d4f:	f420e0        	extui	a2, a14, 0, 16
    1d52:	2458           	l32i.n	a5, a4, 8
    1d54:	0468           	l32i.n	a6, a4, 0
    1d56:	021472        	l16ui	a7, a4, 4
    1d59:	232a           	add.n	a2, a3, a2
    1d5b:	3438           	l32i.n	a3, a4, 12
    1d5d:	6488           	l32i.n	a8, a4, 24
    1d5f:	252a           	add.n	a2, a5, a2
    1d61:	605050        	neg	a5, a5
    1d64:	f67a           	add.n	a15, a6, a7
    1d66:	105250        	and	a5, a2, a5
    1d69:	2f3a           	add.n	a2, a15, a3
    1d6b:	6f7d           	ae_s16i.n	a7, a15, 0
    1d6d:	025452        	s16i	a5, a4, 4
    1d70:	0429           	s32i.n	a2, a4, 0
    1d72:	f88c           	beqz.n	a8, 1d85 <LC3Plus_lc3_scratch_push+0x3d>
    1d74:	5468           	l32i.n	a6, a4, 20
    1d76:	955d           	ae_zext16	a5, a5
    1d78:	44f8           	l32i.n	a15, a4, 16
    1d7a:	335a           	add.n	a3, a3, a5
    1d7c:	336a           	add.n	a3, a3, a6
    1d7e:	5439           	s32i.n	a3, a4, 20
    1d80:	7333f0        	maxu	a3, a3, a15
    1d83:	4439           	s32i.n	a3, a4, 16

00001d85 <LC3Plus_lc3_scratch_push+0x3d>:
    1d85:	f01d           	retw.n

00001d87 <LC3Plus_lc3_scratch_push+0x3f>:
	...

00001d88 <LC3Plus_lc3_scratch_pop>:
    1d88:	004136        	entry	a1, 32
    1d8b:	023d           	mov.n	a3, a2
    1d8d:	02f8           	l32i.n	a15, a2, 0
    1d8f:	3248           	l32i.n	a4, a2, 12
    1d91:	6258           	l32i.n	a5, a2, 24
    1d93:	c02f40        	sub	a2, a15, a4
    1d96:	a58c           	beqz.n	a5, 1da4 <LC3Plus_lc3_scratch_pop+0x1c>
    1d98:	021352        	l16ui	a5, a3, 4
    1d9b:	5368           	l32i.n	a6, a3, 20
    1d9d:	445a           	add.n	a4, a4, a5
    1d9f:	c04640        	sub	a4, a6, a4
    1da2:	5349           	s32i.n	a4, a3, 20

00001da4 <LC3Plus_lc3_scratch_pop+0x1c>:
    1da4:	424d           	ae_l16ui.n	a4, a2, 0
    1da6:	025342        	s16i	a4, a3, 4
    1da9:	c04240        	sub	a4, a2, a4
    1dac:	020c           	movi.n	a2, 0
    1dae:	0349           	s32i.n	a4, a3, 0
    1db0:	f01d           	retw.n

00001db2 <LC3Plus_lc3_scratch_pop+0x2a>:
	...

00001db4 <_fini>:
    1db4:	008136        	entry	a1, 64
    1db7:	f8b781        	l32r	a8, 94 (b0 <__do_global_dtors_aux>)
    1dba:	f03d           	nop.n
    1dbc:	0008e0        	callx8	a8

00001dbf <_fini+0xb>:
    1dbf:	f01d           	retw.n
