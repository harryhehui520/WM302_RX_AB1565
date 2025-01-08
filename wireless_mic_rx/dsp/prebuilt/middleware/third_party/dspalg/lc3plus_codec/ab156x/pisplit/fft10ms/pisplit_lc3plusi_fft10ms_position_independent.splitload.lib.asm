
Build/fft10ms/pisplit_lc3plusi_fft10ms_position_independent.splitload.lib:     file format elf32-xtensa-le


Disassembly of section .text:

00000000 <_init-0xb4>:
       0:	00000100 00002ab8 00002efc 00000000     .....*..........
      10:	00002ec0 00000000 00002ee4 00002f98     ............./..
      20:	00002f2c 00000178 00002f3f 00000c8c     ,/..x...?/......
      30:	00002f4b 0000136c 00002f5b 000015f0     K/..l...[/......
      40:	00002f68 00002040 00002f78 00002510     h/..@ ..x/...%..
      50:	00002f88 0000061c 00002f10 0000322c     ./......./..,2..
      60:	b0000001 478dde64 d18053ce 9d839db0     ....d..G.S......
      70:	79bc3854 0000018c 91261468 00002b34     T8.y....h.&.4+..
      80:	5a82799a a57d8666 00002b74 00001369     .y.Zf.}.t+..i...
      90:	000018f4 cf043ab3 7641af3d 30fbc54d     .....:..=.AvM..0
      a0:	89be50c3 000002d4 00002a58 00002ec8     .P......X*......
      b0:	000000cc                                ....

000000b4 <_init>:
      b4:	008136        	entry	a1, 64
      b7:	ffd281        	l32r	a8, 0 (100 <frame_dummy>)
      ba:	f03d           	nop.n
      bc:	0008e0        	callx8	a8
      bf:	ffd181        	l32r	a8, 4 (2ab8 <__do_global_ctors_aux>)
      c2:	f03d           	nop.n
      c4:	0008e0        	callx8	a8
      c7:	f01d           	retw.n

000000c9 <_init+0x15>:
      c9:	000000                                        ...

000000cc <__do_global_dtors_aux>:
      cc:	004136        	entry	a1, 32
      cf:	ffce21        	l32r	a2, 8 (2efc <__do_global_dtors_aux.completed>)
      d2:	000232        	l8ui	a3, a2, 0
      d5:	23ec           	bnez.n	a3, fb <__do_global_dtors_aux+0x2f>

000000d7 <__do_global_dtors_aux+0xb>:
      d7:	1248           	l32i.n	a4, a2, 4
      d9:	0438           	l32i.n	a3, a4, 0
      db:	444b           	addi.n	a4, a4, 4
      dd:	738c           	beqz.n	a3, e8 <__do_global_dtors_aux+0x1c>
      df:	1249           	s32i.n	a4, a2, 4
      e1:	0003e0        	callx8	a3
      e4:	fffbc6        	j	d7 <__do_global_dtors_aux+0xb>

000000e7 <__do_global_dtors_aux+0x1b>:
	...

000000e8 <__do_global_dtors_aux+0x1c>:
      e8:	ffc931        	l32r	a3, c (0 <_text_start>)
      eb:	ffc9a1        	l32r	a10, 10 (2ec0 <__FRAME_END__>)
      ee:	438c           	beqz.n	a3, f6 <__do_global_dtors_aux+0x2a>
      f0:	ffc781        	l32r	a8, c (0 <_text_start>)
      f3:	0008e0        	callx8	a8
      f6:	130c           	movi.n	a3, 1
      f8:	004232        	s8i	a3, a2, 0
      fb:	f01d           	retw.n

000000fd <__do_global_dtors_aux+0x31>:
      fd:	000000                                        ...

00000100 <frame_dummy>:
     100:	004136        	entry	a1, 32
     103:	ffc421        	l32r	a2, 14 (0 <_text_start>)
     106:	ffc2a1        	l32r	a10, 10 (2ec0 <__FRAME_END__>)
     109:	ffc3b1        	l32r	a11, 18 (2ee4 <frame_dummy.object>)
     10c:	428c           	beqz.n	a2, 114 <frame_dummy+0x14>
     10e:	ffc181        	l32r	a8, 14 (0 <_text_start>)
     111:	0008e0        	callx8	a8

00000114 <frame_dummy+0x14>:
     114:	f01d           	retw.n

00000116 <frame_dummy+0x16>:
	...

00000118 <_start>:
     118:	004136        	entry	a1, 32
     11b:	ffc031        	l32r	a3, 1c (2f98 <printf_ptr>)
     11e:	0228           	l32i.n	a2, a2, 0
     120:	ffc0a1        	l32r	a10, 20 (2f2c <export_parameter_array+0x1c>)
     123:	ffc0b1        	l32r	a11, 24 (178 <fix_fft_Init>)
     126:	0329           	s32i.n	a2, a3, 0
     128:	0002e0        	callx8	a2
     12b:	0328           	l32i.n	a2, a3, 0
     12d:	ffbea1        	l32r	a10, 28 (2f3f <export_parameter_array+0x2f>)
     130:	ffbfb1        	l32r	a11, 2c (c8c <FFT8N>)
     133:	0002e0        	callx8	a2
     136:	0328           	l32i.n	a2, a3, 0
     138:	ffbea1        	l32r	a10, 30 (2f4b <export_parameter_array+0x3b>)
     13b:	ffbeb1        	l32r	a11, 34 (136c <fix_fft10>)
     13e:	0002e0        	callx8	a2
     141:	0328           	l32i.n	a2, a3, 0
     143:	ffbda1        	l32r	a10, 38 (2f5b <export_parameter_array+0x4b>)
     146:	ffbdb1        	l32r	a11, 3c (15f0 <FFT16N>)
     149:	0002e0        	callx8	a2
     14c:	0328           	l32i.n	a2, a3, 0
     14e:	ffbca1        	l32r	a10, 40 (2f68 <export_parameter_array+0x58>)
     151:	ffbcb1        	l32r	a11, 44 (2040 <fix_fft20>)
     154:	0002e0        	callx8	a2
     157:	0328           	l32i.n	a2, a3, 0
     159:	ffbba1        	l32r	a10, 48 (2f78 <export_parameter_array+0x68>)
     15c:	ffbcb1        	l32r	a11, 4c (2510 <fix_fft30>)
     15f:	0002e0        	callx8	a2
     162:	0328           	l32i.n	a2, a3, 0
     164:	ffbba1        	l32r	a10, 50 (2f88 <export_parameter_array+0x78>)
     167:	ffbbb1        	l32r	a11, 54 (61c <fix_fft40>)
     16a:	0002e0        	callx8	a2
     16d:	ffba21        	l32r	a2, 58 (2f10 <export_parameter_array>)
     170:	f01d           	retw.n

00000172 <_start+0x5a>:
     172:	00000000                                 ......

00000178 <fix_fft_Init>:
     178:	004136        	entry	a1, 32
     17b:	f8a032        	movi	a3, 248
     17e:	ffb741        	l32r	a4, 5c (322c <LC3Plus_RotVector_40_32>)
     181:	55d332        	addmi	a3, a3, 0x5500
     184:	223a           	add.n	a2, a2, a3
     186:	0429           	s32i.n	a2, a4, 0
     188:	f01d           	retw.n

0000018a <fix_fft_Init+0x12>:
	...

0000018c <fix_fft5_stage>:
     18c:	008136        	entry	a1, 64
     18f:	2468           	l32i.n	a6, a4, 8
     191:	8478           	l32i.n	a7, a4, 32
     193:	4488           	l32i.n	a8, a4, 16
     195:	6498           	l32i.n	a9, a4, 24
     197:	025d           	mov.n	a5, a2
     199:	ffb121        	l32r	a2, 60 (b0000001 <_end+0xafffcda9>)
     19c:	04c8           	l32i.n	a12, a4, 0
     19e:	7139           	s32i.n	a3, a1, 28
     1a0:	d76a           	add.n	a13, a7, a6
     1a2:	c0a670        	sub	a10, a6, a7
     1a5:	398a           	add.n	a3, a9, a8
     1a7:	ffaf61        	l32r	a6, 64 (478dde64 <_end+0x478dac0c>)
     1aa:	fd3a           	add.n	a15, a13, a3
     1ac:	ffaf71        	l32r	a7, 68 (d18053ce <_end+0xd1802176>)
     1af:	c0b890        	sub	a11, a8, a9
     1b2:	9fca           	add.n	a9, a15, a12
     1b4:	b2ef20        	mulsh	a14, a15, a2
     1b7:	82ff20        	mull	a15, a15, a2
     1ba:	c02d30        	sub	a2, a13, a3
     1bd:	823260        	mull	a3, a2, a6
     1c0:	b28260        	mulsh	a8, a2, a6
     1c3:	82db70        	mull	a13, a11, a7
     1c6:	05cf30        	extui	a12, a3, 31, 1
     1c9:	b22b70        	mulsh	a2, a11, a7
     1cc:	9088c0        	addx2	a8, a8, a12
     1cf:	05cfd0        	extui	a12, a13, 31, 1
     1d2:	90d2c0        	addx2	a13, a2, a12
     1d5:	ffa5c1        	l32r	a12, 6c (9d839db0 <_end+0x9d836b58>)
     1d8:	2aba           	add.n	a2, a10, a11
     1da:	0599           	s32i.n	a9, a5, 0
     1dc:	823ac0        	mull	a3, a10, a12
     1df:	b2aac0        	mulsh	a10, a10, a12
     1e2:	05bf30        	extui	a11, a3, 31, 1
     1e5:	11bbf0        	slli	a11, a11, 1
     1e8:	a0aab0        	addx4	a10, a10, a11
     1eb:	ffa1b1        	l32r	a11, 70 (79bc3854 <_end+0x79bc05fc>)
     1ee:	8232b0        	mull	a3, a2, a11
     1f1:	b222b0        	mulsh	a2, a2, a11
     1f4:	053f30        	extui	a3, a3, 31, 1
     1f7:	902230        	addx2	a2, a2, a3
     1fa:	3a2a           	add.n	a3, a10, a2
     1fc:	05aff0        	extui	a10, a15, 31, 1
     1ff:	d2da           	add.n	a13, a2, a13
     201:	112af0        	slli	a2, a10, 1
     204:	360d34        	ae_cvtq48a32s	aeq0, a13
     207:	a0ee20        	addx4	a14, a14, a2
     20a:	05ad           	mov.n	a10, a5
     20c:	54f8           	l32i.n	a15, a4, 20
     20e:	7428           	l32i.n	a2, a4, 28
     210:	34d8           	l32i.n	a13, a4, 12
     212:	9458           	l32i.n	a5, a4, 36
     214:	6139           	s32i.n	a3, a1, 24
     216:	3e9a           	add.n	a3, a14, a9
     218:	e2fa           	add.n	a14, a2, a15
     21a:	c02f20        	sub	a2, a15, a2
     21d:	f5da           	add.n	a15, a5, a13
     21f:	c09d50        	sub	a9, a13, a5
     222:	b2d9c0        	mulsh	a13, a9, a12
     225:	82c9c0        	mull	a12, a9, a12
     228:	b25270        	mulsh	a5, a2, a7
     22b:	827270        	mull	a7, a2, a7
     22e:	292a           	add.n	a2, a9, a2
     230:	c09fe0        	sub	a9, a15, a14
     233:	efea           	add.n	a14, a15, a14
     235:	c0f380        	sub	a15, a3, a8
     238:	338a           	add.n	a3, a3, a8
     23a:	364334        	ae_cvtq48a32s	aeq1, a3
     23d:	b23960        	mulsh	a3, a9, a6
     240:	826960        	mull	a6, a9, a6
     243:	b292b0        	mulsh	a9, a2, a11
     246:	8222b0        	mull	a2, a2, a11
     249:	ff8581        	l32r	a8, 60 (b0000001 <_end+0xafffcda9>)
     24c:	14b8           	l32i.n	a11, a4, 4
     24e:	057f70        	extui	a7, a7, 31, 1
     251:	052f20        	extui	a2, a2, 31, 1
     254:	905570        	addx2	a5, a5, a7
     257:	7178           	l32i.n	a7, a1, 28
     259:	902920        	addx2	a2, a9, a2
     25c:	829e80        	mull	a9, a14, a8
     25f:	525a           	add.n	a5, a2, a5
     261:	4eba           	add.n	a4, a14, a11
     263:	05cfc0        	extui	a12, a12, 31, 1
     266:	368534        	ae_cvtq48a32s	aeq2, a5
     269:	11bcf0        	slli	a11, a12, 1
     26c:	fbea14074f 	{ s32i.n	a4, a7, 0; ae_addq56	aeq3, aeq1, aeq2 }
     271:	578b           	addi.n	a5, a7, 8
     273:	7a8b           	addi.n	a7, a10, 8
     275:	b2ae80        	mulsh	a10, a14, a8
     278:	059f90        	extui	a9, a9, 31, 1
     27b:	a0bdb0        	addx4	a11, a13, a11
     27e:	056f60        	extui	a6, a6, 31, 1
     281:	11d9f0        	slli	a13, a9, 1
     284:	f9aad1336f 	{ addx2	a3, a3, a6; ae_subq56	aeq1, aeq1, aeq2 }
     289:	a06ad0        	addx4	a6, a10, a13
     28c:	2b2a           	add.n	a2, a11, a2
     28e:	627704        	ae_sq32f.iu	aeq3, a7, 0
     291:	e64a           	add.n	a14, a6, a4
     293:	630124        	ae_sq56s.i	aeq0, a1, 16
     296:	36cf34        	ae_cvtq48a32s	aeq3, a15
     299:	360234        	ae_cvtq48a32s	aeq0, a2
     29c:	fa3af9d76f 	{ ae_sq32f.iu	aeq1, a7, 24; ae_subq56	aeq2, aeq3, aeq0 }
     2a1:	4e3a           	add.n	a4, a14, a3
     2a3:	f87a39e7cf 	{ ae_sq32f.iu	aeq2, a7, -16; ae_addq56	aeq0, aeq3, aeq0 }
     2a8:	364434        	ae_cvtq48a32s	aeq1, a4
     2ab:	618124        	ae_lq56.i	aeq2, a1, 16
     2ae:	fbaaf061fe 	{ l32i	a15, a1, 24; ae_subq56	aeq3, aeq1, aeq2 }
     2b3:	f9ea152e3f 	{ sub	a2, a14, a3; ae_addq56	aeq1, aeq1, aeq2 }
     2b8:	624724        	ae_sq32f.iu	aeq0, a7, 8
     2bb:	627504        	ae_sq32f.iu	aeq3, a5, 0
     2be:	360f34        	ae_cvtq48a32s	aeq0, a15
     2c1:	368234        	ae_cvtq48a32s	aeq2, a2
     2c4:	fb7239d56f 	{ ae_sq32f.iu	aeq1, a5, 24; ae_addq56	aeq3, aeq2, aeq0 }
     2c9:	f832f9f5cf 	{ ae_sq32f.iu	aeq3, a5, -16; ae_subq56	aeq0, aeq2, aeq0 }
     2ce:	624524        	ae_sq32f.iu	aeq0, a5, 8
     2d1:	f01d           	retw.n

000002d3 <fix_fft5_stage+0x147>:
	...

000002d4 <fix_fft15_stage>:
     2d4:	00c136        	entry	a1, 96
     2d7:	ff6771        	l32r	a7, 74 (18c <fix_fft5_stage>)
     2da:	b44b           	addi.n	a11, a4, 4
     2dc:	04ad           	mov.n	a10, a4
     2de:	04cd           	mov.n	a12, a4
     2e0:	28c462        	addi	a6, a4, 40
     2e3:	50c452        	addi	a5, a4, 80
     2e6:	0007e0        	callx8	a7
     2e9:	2cc4b2        	addi	a11, a4, 44
     2ec:	06ad           	mov.n	a10, a6
     2ee:	06cd           	mov.n	a12, a6
     2f0:	0007e0        	callx8	a7
     2f3:	54c4b2        	addi	a11, a4, 84
     2f6:	05ad           	mov.n	a10, a5
     2f8:	05cd           	mov.n	a12, a5
     2fa:	0007e0        	callx8	a7
     2fd:	672c           	movi.n	a7, 38
     2ff:	91d772        	addmi	a7, a7, 0xffff9100
     302:	ff5d81        	l32r	a8, 78 (91261468 <_end+0x9125e210>)
     305:	600604        	ae_lq32f.i	aeq0, a6, 0
     308:	604504        	ae_lq32f.i	aeq1, a5, 0
     30b:	fa6603c19e 	{ addi	a9, a1, 60; ae_addq56	aeq2, aeq0, aeq1 }
     310:	300874        	ae_cvtp24a16x2.ll	aep0, a8, a7
     313:	630144        	ae_sq56s.i	aeq0, a1, 32
     316:	460904        	ae_sp16x2f.i	aep0, a9, 0
     319:	352074        	ae_sraiq56	aeq0, aeq2, 1
     31c:	60c404        	ae_lq32f.i	aeq3, a4, 0
     31f:	fafa3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     324:	610144        	ae_lq56.i	aeq0, a1, 32
     327:	f826ff2bef 	{ ae_trunca32q48	a11, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     32c:	440904        	ae_lp16x2f.i	aep0, a9, 0
     32f:	d462fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     334:	fe345402bf 	{ s32i.n	a11, a2, 0; ae_roundsq32asym	aeq2, aeq2 }
     339:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     33e:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     343:	608614        	ae_lq32f.i	aeq2, a6, 4
     346:	fd6c7d651f 	{ ae_lq32f.i	aeq3, a5, 4; ae_truncq32	aeq1, aeq1 }
     34b:	012bc4        	ae_addq56	aeq0, aeq2, aeq3
     34e:	fab6fb00df 	{ ae_sraiq56	aeq3, aeq0, 1; ae_subq56	aeq2, aeq2, aeq3 }
     353:	633134        	ae_sq56s.i	aeq3, a1, 24
     356:	632154        	ae_sq56s.i	aeq2, a1, 40
     359:	608414        	ae_lq32f.i	aeq2, a4, 4
     35c:	f8723de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_addq56	aeq0, aeq2, aeq0 }
     361:	fc3c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_roundsq32asym	aeq0, aeq3 }
     366:	61c154        	ae_lq56.i	aeq3, a1, 40
     369:	d663ba016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_mulfq32sp16u.h	aeq0, aeq3, aep0 }
     36e:	630134        	ae_sq56s.i	aeq0, a1, 24
     371:	610164        	ae_lq56.i	aeq0, a1, 48
     374:	f832fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_subq56	aeq0, aeq2, aeq0 }
     379:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     37c:	f783bde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq3, aep0 }
     381:	fb663f3cef 	{ ae_trunca32q48	a12, aeq3; ae_addq56	aeq3, aeq0, aeq1 }
     386:	f826ff3def 	{ ae_trunca32q48	a13, aeq3; ae_subq56	aeq0, aeq0, aeq1 }
     38b:	fe747f0eef 	{ ae_trunca32q48	a14, aeq0; ae_truncq32	aeq2, aeq2 }
     390:	610124        	ae_lq56.i	aeq0, a1, 16
     393:	fba2d403cf 	{ s32i.n	a12, a3, 0; ae_subq56	aeq3, aeq0, aeq2 }
     398:	f9e23f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     39d:	369a04        	ae_trunca32q48	a10, aeq1
     3a0:	1462f2        	s32i	a15, a2, 80
     3a3:	a2a9           	s32i.n	a10, a2, 40
     3a5:	1463d2        	s32i	a13, a3, 80
     3a8:	a3e9           	s32i.n	a14, a3, 40
     3aa:	60c624        	ae_lq32f.i	aeq3, a6, 8
     3ad:	604524        	ae_lq32f.i	aeq1, a5, 8
     3b0:	f87e3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     3b5:	60c424        	ae_lq32f.i	aeq3, a4, 8
     3b8:	fa7a3b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_addq56	aeq2, aeq3, aeq0 }
     3bd:	fc247a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     3c2:	618144        	ae_lq56.i	aeq2, a1, 32
     3c5:	f936fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq1, aeq2, aeq1 }
     3ca:	d563bf2bef 	{ ae_trunca32q48	a11, aeq2; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     3cf:	630124        	ae_sq56s.i	aeq0, a1, 16
     3d2:	352434        	ae_sraiq56	aeq0, aeq2, 16
     3d5:	f483bdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     3da:	fabad4c2bf 	{ s32i.n	a11, a2, 48; ae_subq56	aeq2, aeq3, aeq2 }
     3df:	632124        	ae_sq56s.i	aeq2, a1, 16
     3e2:	608634        	ae_lq32f.i	aeq2, a6, 12
     3e5:	604534        	ae_lq32f.i	aeq1, a5, 12
     3e8:	fb763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq3, aeq2, aeq1 }
     3ed:	fa36fd043f 	{ ae_lq32f.i	aeq0, a4, 12; ae_subq56	aeq2, aeq2, aeq1 }
     3f2:	fbe63b305f 	{ ae_sraiq56	aeq1, aeq3, 1; ae_addq56	aeq3, aeq0, aeq3 }
     3f7:	d762fa314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     3fc:	631134        	ae_sq56s.i	aeq1, a1, 24
     3ff:	614134        	ae_lq56.i	aeq1, a1, 24
     402:	fd2c7b34cf 	{ ae_sraiq56	aeq3, aeq3, 16; ae_roundsq32asym	aeq1, aeq1 }
     407:	f782fdc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     40c:	010dc4        	ae_subq56	aeq0, aeq0, aeq1
     40f:	fd747dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_truncq32	aeq1, aeq2 }
     414:	fa663f2cef 	{ ae_trunca32q48	a12, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     419:	f826ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     41e:	fd7c7dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_truncq32	aeq1, aeq3 }
     423:	fb36ff0eef 	{ ae_trunca32q48	a14, aeq0; ae_subq56	aeq3, aeq2, aeq1 }
     428:	f9763f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq2, aeq1 }
     42d:	369a04        	ae_trunca32q48	a10, aeq1
     430:	c3c9           	s32i.n	a12, a3, 48
     432:	22f9           	s32i.n	a15, a2, 8
     434:	1662a2        	s32i	a10, a2, 88
     437:	23d9           	s32i.n	a13, a3, 8
     439:	1663e2        	s32i	a14, a3, 88
     43c:	600644        	ae_lq32f.i	aeq0, a6, 16
     43f:	604544        	ae_lq32f.i	aeq1, a5, 16
     442:	fa663d644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_addq56	aeq2, aeq0, aeq1 }
     447:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     44c:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     451:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     456:	36ab04        	ae_trunca32q48	a11, aeq2
     459:	618144        	ae_lq56.i	aeq2, a1, 32
     45c:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     461:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     466:	1862b2        	s32i	a11, a2, 96
     469:	f482fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     46e:	608654        	ae_lq32f.i	aeq2, a6, 20
     471:	600554        	ae_lq32f.i	aeq0, a5, 20
     474:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     477:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     47c:	632134        	ae_sq56s.i	aeq2, a1, 24
     47f:	630124        	ae_sq56s.i	aeq0, a1, 16
     482:	600454        	ae_lq32f.i	aeq0, a4, 20
     485:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     48a:	ff347a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_roundsq32asym	aeq3, aeq2 }
     48f:	618124        	ae_lq56.i	aeq2, a1, 16
     492:	0382a4        	ae_mulfq32sp16u.h	aeq2, aeq2, aep0
     495:	faa6fa216f 	{ ae_sq56s.i	aeq2, a1, 48; ae_subq56	aeq2, aeq0, aeq3 }
     49a:	61c164        	ae_lq56.i	aeq3, a1, 48
     49d:	353434        	ae_sraiq56	aeq0, aeq3, 16
     4a0:	61c124        	ae_lq56.i	aeq3, a1, 16
     4a3:	f683ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulafq32sp16s.l	aeq0, aeq3, aep0 }
     4a8:	ff6c7da15f 	{ ae_lq56.i	aeq1, a1, 40; ae_truncq32	aeq3, aeq1 }
     4ad:	faf63f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq2, aeq2, aeq3 }
     4b2:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     4b7:	fa26ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq2, aeq0, aeq1 }
     4bc:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     4c1:	618134        	ae_lq56.i	aeq2, a1, 24
     4c4:	f8b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq0, aeq2, aeq3 }
     4c9:	368904        	ae_trunca32q48	a9, aeq0
     4cc:	1863c2        	s32i	a12, a3, 96
     4cf:	e2e9           	s32i.n	a14, a2, 56
     4d1:	42f9           	s32i.n	a15, a2, 16
     4d3:	e3d9           	s32i.n	a13, a3, 56
     4d5:	4399           	s32i.n	a9, a3, 16
     4d7:	60c664        	ae_lq32f.i	aeq3, a6, 24
     4da:	608564        	ae_lq32f.i	aeq2, a5, 24
     4dd:	f9fa3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq1, aeq3, aeq2 }
     4e2:	60c464        	ae_lq32f.i	aeq3, a4, 24
     4e5:	f87e0704de 	{ addi	a13, a4, 112; ae_addq56	aeq0, aeq3, aeq1 }
     4ea:	630124        	ae_sq56s.i	aeq0, a1, 16
     4ed:	610144        	ae_lq56.i	aeq0, a1, 32
     4f0:	010ec4        	ae_subq56	aeq0, aeq0, aeq2
     4f3:	630134        	ae_sq56s.i	aeq0, a1, 24
     4f6:	351074        	ae_sraiq56	aeq0, aeq1, 1
     4f9:	fc247da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     4fe:	f83aff1aef 	{ ae_trunca32q48	a10, aeq1; ae_subq56	aeq0, aeq3, aeq0 }
     503:	614134        	ae_lq56.i	aeq1, a1, 24
     506:	d5639462af 	{ s32i.n	a10, a2, 24; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     50b:	60c674        	ae_lq32f.i	aeq3, a6, 28
     50e:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     511:	f583bd257f 	{ ae_lq32f.i	aeq1, a5, 28; ae_mulafq32sp16s.l	aeq2, aeq1, aep0 }
     516:	f87e3a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     51b:	f93efd647f 	{ ae_lq32f.i	aeq3, a4, 28; ae_subq56	aeq1, aeq3, aeq1 }
     520:	631124        	ae_sq56s.i	aeq1, a1, 16
     523:	f87a3b005f 	{ ae_sraiq56	aeq1, aeq0, 1; ae_addq56	aeq0, aeq3, aeq0 }
     528:	631134        	ae_sq56s.i	aeq1, a1, 24
     52b:	614134        	ae_lq56.i	aeq1, a1, 24
     52e:	fc2c7a016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_roundsq32asym	aeq0, aeq1 }
     533:	614124        	ae_lq56.i	aeq1, a1, 16
     536:	030a64        	ae_mulfq32sp16u.h	aeq1, aeq1, aep0
     539:	f93afa115f 	{ ae_sq56s.i	aeq1, a1, 40; ae_subq56	aeq1, aeq3, aeq0 }
     53e:	61c164        	ae_lq56.i	aeq3, a1, 48
     541:	ff747f3bef 	{ ae_trunca32q48	a11, aeq3; ae_truncq32	aeq3, aeq2 }
     546:	618154        	ae_lq56.i	aeq2, a1, 40
     549:	faee3b240f 	{ ae_sraiq56	aeq0, aeq2, 16; ae_addq56	aeq2, aeq1, aeq3 }
     54e:	631134        	ae_sq56s.i	aeq1, a1, 24
     551:	614124        	ae_lq56.i	aeq1, a1, 16
     554:	f483bf2cef 	{ ae_trunca32q48	a12, aeq2; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     559:	63b9           	s32i.n	a11, a3, 24
     55b:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     560:	018dc4        	ae_subq56	aeq2, aeq0, aeq1
     563:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     568:	618134        	ae_lq56.i	aeq2, a1, 24
     56b:	f9b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq1, aeq2, aeq3 }
     570:	369904        	ae_trunca32q48	a9, aeq1
     573:	1a62e2        	s32i	a14, a2, 104
     576:	1062f2        	s32i	a15, a2, 64
     579:	1a63c2        	s32i	a12, a3, 104
     57c:	106392        	s32i	a9, a3, 64
     57f:	6005e4        	ae_lq32f.i	aeq0, a5, -8
     582:	604d04        	ae_lq32f.i	aeq1, a13, 0
     585:	fa663d66ef 	{ ae_lq32f.i	aeq3, a6, -8; ae_addq56	aeq2, aeq0, aeq1 }
     58a:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     58f:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     594:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     599:	36aa04        	ae_trunca32q48	a10, aeq2
     59c:	618144        	ae_lq56.i	aeq2, a1, 32
     59f:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     5a4:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     5a9:	1262a2        	s32i	a10, a2, 72
     5ac:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     5b1:	6085f4        	ae_lq32f.i	aeq2, a5, -4
     5b4:	fd6c7d0d1f 	{ ae_lq32f.i	aeq0, a13, 4; ae_truncq32	aeq1, aeq1 }
     5b9:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     5bc:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     5c1:	632134        	ae_sq56s.i	aeq2, a1, 24
     5c4:	630154        	ae_sq56s.i	aeq0, a1, 40
     5c7:	6006f4        	ae_lq32f.i	aeq0, a6, -4
     5ca:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     5cf:	ff347a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_roundsq32asym	aeq3, aeq2 }
     5d4:	618154        	ae_lq56.i	aeq2, a1, 40
     5d7:	d762fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     5dc:	633164        	ae_sq56s.i	aeq3, a1, 48
     5df:	61c134        	ae_lq56.i	aeq3, a1, 24
     5e2:	f8a6fde16f 	{ ae_lq56.i	aeq3, a1, 48; ae_subq56	aeq0, aeq0, aeq3 }
     5e7:	35f434        	ae_sraiq56	aeq3, aeq3, 16
     5ea:	f782fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     5ef:	fa663f2bef 	{ ae_trunca32q48	a11, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     5f4:	f826ff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     5f9:	fe7c7f0def 	{ ae_trunca32q48	a13, aeq0; ae_truncq32	aeq2, aeq3 }
     5fe:	610124        	ae_lq56.i	aeq0, a1, 16
     601:	01cec4        	ae_subq56	aeq3, aeq0, aeq2
     604:	f9e23f3eef 	{ ae_trunca32q48	a14, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     609:	369f04        	ae_trunca32q48	a15, aeq1
     60c:	1263b2        	s32i	a11, a3, 72
     60f:	82e9           	s32i.n	a14, a2, 32
     611:	1c62f2        	s32i	a15, a2, 112
     614:	83c9           	s32i.n	a12, a3, 32
     616:	1c63d2        	s32i	a13, a3, 112
     619:	f01d           	retw.n

0000061b <fix_fft15_stage+0x347>:
	...

0000061c <fix_fft40>:
     61c:	034136        	entry	a1, 0x1a0
     61f:	256122        	s32i	a2, a1, 148
     622:	fe9621        	l32r	a2, 7c (2b34 <LC3Plus_lc3_scratch_push>)
     625:	40a1b2        	movi	a11, 0x140
     628:	05ad           	mov.n	a10, a5
     62a:	326152        	s32i	a5, a1, 200
     62d:	276132        	s32i	a3, a1, 156
     630:	045d           	mov.n	a5, a4
     632:	0002e0        	callx8	a2
     635:	fe8981        	l32r	a8, 5c (322c <LC3Plus_RotVector_40_32>)
     638:	1124e0        	slli	a2, a4, 2
     63b:	2e6122        	s32i	a2, a1, 184
     63e:	08f8           	l32i.n	a15, a8, 0
     640:	1124b0        	slli	a2, a4, 5
     643:	2661a2        	s32i	a10, a1, 152
     646:	fcca82        	addi	a8, a10, -4
     649:	2521a2        	l32i	a10, a1, 148
     64c:	2e2142        	l32i	a4, a1, 184
     64f:	830c           	movi.n	a3, 8
     651:	060c           	movi.n	a6, 0
     653:	570c           	movi.n	a7, 5
     655:	2461f2        	s32i	a15, a1, 144

00000658 <fix_fft40+0x3c>:
     658:	0a9d           	mov.n	a9, a10
     65a:	603964        	ae_lq32f.xu	aeq0, a9, a6
     65d:	0b8776        	loop	a7, 66c <fix_fft40+0x50>
     660:	624814        	ae_sq32f.iu	aeq0, a8, 4
     663:	600914        	ae_lq32f.i	aeq0, a9, 4
     666:	624814        	ae_sq32f.iu	aeq0, a8, 4
     669:	603924        	ae_lq32f.xu	aeq0, a9, a2

0000066c <fix_fft40+0x50>:
     66c:	330b           	addi.n	a3, a3, -1
     66e:	664a           	add.n	a6, a6, a4
     670:	fe4356        	bnez	a3, 658 <fix_fft40+0x3c>
     673:	170c           	movi.n	a7, 1
     675:	117750        	slli	a7, a7, 11
     678:	300774        	ae_cvtp24a16x2.ll	aep0, a7, a7
     67b:	fe7e21        	l32r	a2, 74 (18c <fix_fft5_stage>)
     67e:	262172        	l32i	a7, a1, 152
     681:	830c           	movi.n	a3, 8
     683:	50c142        	addi	a4, a1, 80
     686:	560174        	ae_sp24x2s.i	aep0, a1, 56

00000689 <fix_fft40+0x6d>:
     689:	600704        	ae_lq32f.i	aeq0, a7, 0
     68c:	540174        	ae_lp24x2.i	aep0, a1, 56
     68f:	d5e2fd471f 	{ ae_lq32f.i	aeq2, a7, 4; ae_mulfq32sp16u.l	aeq3, aeq0, aep0 }
     694:	d7e293844f 	{ or	a8, a4, a4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     699:	ff3c7d273f 	{ ae_lq32f.i	aeq1, a7, 12; ae_roundsq32asym	aeq3, aeq3 }
     69e:	fe3479f80f 	{ ae_sq32f.iu	aeq3, a8, 0; ae_roundsq32asym	aeq2, aeq2 }
     6a3:	60c744        	ae_lq32f.i	aeq3, a7, 16
     6a6:	600724        	ae_lq32f.i	aeq0, a7, 8
     6a9:	d4e2ba112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     6ae:	633134        	ae_sq56s.i	aeq3, a1, 24
     6b1:	fc247de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     6b6:	d7e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     6bb:	618134        	ae_lq56.i	aeq2, a1, 24
     6be:	d7e28047be 	{ addi	a11, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     6c3:	ff3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq3 }
     6c8:	0bad           	mov.n	a10, a11
     6ca:	632124        	ae_sq56s.i	aeq2, a1, 16
     6cd:	079d           	mov.n	a9, a7
     6cf:	604754        	ae_lq32f.i	aeq1, a7, 20
     6d2:	d4e3fd1a6f 	{ ae_lq32f.iu	aeq0, a10, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     6d7:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6da:	fd2c7de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq1, aeq1 }
     6df:	ff3c7d596f 	{ ae_lq32f.iu	aeq2, a9, 24; ae_roundsq32asym	aeq3, aeq3 }
     6e4:	d7e2ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     6e9:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6ec:	fe347de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq2, aeq2 }
     6f1:	d7e3fd092f 	{ ae_lq32f.i	aeq0, a9, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     6f6:	d4e2b9d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     6fb:	ff3c7d2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_roundsq32asym	aeq3, aeq3 }
     700:	d4e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     705:	fc2479f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq0, aeq0 }
     70a:	ff2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq1 }
     70f:	07ad           	mov.n	a10, a7
     711:	04cd           	mov.n	a12, a4
     713:	627814        	ae_sq32f.iu	aeq3, a8, 4
     716:	0002e0        	callx8	a2
     719:	330b           	addi.n	a3, a3, -1
     71b:	28c772        	addi	a7, a7, 40
     71e:	f67356        	bnez	a3, 689 <fix_fft40+0x6d>
     721:	242162        	l32i	a6, a1, 144
     724:	a0f550        	addx4	a15, a5, a5
     727:	2a6142        	s32i	a4, a1, 168
     72a:	8f4d           	ae_sext16	a4, a15
     72c:	f8c692        	addi	a9, a6, -8
     72f:	252162        	l32i	a6, a1, 148
     732:	82a032        	movi	a3, 130
     735:	7da082        	movi	a8, 125
     738:	2721f2        	l32i	a15, a1, 156
     73b:	f05440        	subx8	a5, a4, a4
     73e:	fe5021        	l32r	a2, 80 (5a82799a <_end+0x5a824742>)
     741:	5ad332        	addmi	a3, a3, 0x5a00
     744:	fe5071        	l32r	a7, 84 (a57d8666 <_end+0xa57d540e>)
     747:	a5d882        	addmi	a8, a8, 0xffffa500
     74a:	a0b440        	addx4	a11, a4, a4
     74d:	90c440        	addx2	a12, a4, a4
     750:	1155e0        	slli	a5, a5, 2
     753:	301874        	ae_cvtp24a16x2.ll	aep1, a8, a7
     756:	300324        	ae_cvtp24a16x2.ll	aep0, a3, a2
     759:	1184c0        	slli	a8, a4, 4
     75c:	b0a460        	addx8	a10, a4, a6
     75f:	113be0        	slli	a3, a11, 2
     762:	11bcd0        	slli	a11, a12, 3
     765:	765a           	add.n	a7, a6, a5
     767:	11cce0        	slli	a12, a12, 2
     76a:	3161a2        	s32i	a10, a1, 196
     76d:	af8a           	add.n	a10, a15, a8
     76f:	268a           	add.n	a2, a6, a8
     771:	2f6172        	s32i	a7, a1, 188
     774:	7fca           	add.n	a7, a15, a12
     776:	3061a2        	s32i	a10, a1, 192
     779:	246122        	s32i	a2, a1, 144
     77c:	8f5a           	add.n	a8, a15, a5
     77e:	2d6172        	s32i	a7, a1, 180
     781:	56ca           	add.n	a5, a6, a12
     783:	afba           	add.n	a10, a15, a11
     785:	26ba           	add.n	a2, a6, a11
     787:	c63a           	add.n	a12, a6, a3
     789:	01d172        	addmi	a7, a1, 0x100
     78c:	bf3a           	add.n	a11, a15, a3
     78e:	2c61a2        	s32i	a10, a1, 176
     791:	296122        	s32i	a2, a1, 164
     794:	60c722        	addi	a2, a7, 96
     797:	2861c2        	s32i	a12, a1, 160
     79a:	2621c2        	l32i	a12, a1, 152
     79d:	01d1a2        	addmi	a10, a1, 0x100
     7a0:	2b61b2        	s32i	a11, a1, 172
     7a3:	386122        	s32i	a2, a1, 224
     7a6:	20ca22        	addi	a2, a10, 32
     7a9:	a0d4f0        	addx4	a13, a4, a15
     7ac:	b0e4f0        	addx8	a14, a4, a15
     7af:	a04460        	addx4	a4, a4, a6
     7b2:	01d1b2        	addmi	a11, a1, 0x100
     7b5:	e149           	s32i.n	a4, a1, 56
     7b7:	54c132        	addi	a3, a1, 84
     7ba:	58c142        	addi	a4, a1, 88
     7bd:	70c162        	addi	a6, a1, 112
     7c0:	366122        	s32i	a2, a1, 216
     7c3:	30cb22        	addi	a2, a11, 48
     7c6:	346132        	s32i	a3, a1, 208
     7c9:	336142        	s32i	a4, a1, 204
     7cc:	376162        	s32i	a6, a1, 220
     7cf:	356122        	s32i	a2, a1, 212
     7d2:	28ccc2        	addi	a12, a12, 40
     7d5:	570c           	movi.n	a7, 5
     7d7:	8a2c           	movi.n	a10, 40
     7d9:	0b2c           	movi.n	a11, 32
     7db:	011346        	j	c2c <fix_fft40+0x610>

000007de <fix_fft40+0x1c2>:
	...

000007df <fix_fft40+0x1c3>:
     7df:	093d           	mov.n	a3, a9
     7e1:	342142        	l32i	a4, a1, 208
     7e4:	2a2162        	l32i	a6, a1, 168
     7e7:	44a304        	ae_lp16x2f.iu	aep2, a3, 0
     7ea:	720c           	movi.n	a2, 7
     7ec:	60cc04        	ae_lq32f.i	aeq3, a12, 0
     7ef:	604c14        	ae_lq32f.i	aeq1, a12, 4
     7f2:	443314        	ae_lp16x2f.i	aep3, a3, 4
     7f5:	5c8276        	loop	a2, 855 <fix_fft40+0x239>
     7f8:	03a2e4        	ae_mulfq32sp16u.h	aeq2, aeq3, aep2
     7fb:	0332e4        	ae_mulfq32sp16u.h	aeq0, aeq3, aep3
     7fe:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     801:	f78bbb040f 	{ ae_sraiq56	aeq0, aeq0, 16; ae_mulafq32sp16s.l	aeq2, aeq3, aep2 }
     806:	0330d4        	ae_mulafq32sp16s.l	aeq0, aeq3, aep3
     809:	d56fba212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq2, aeq1, aep3 }
     80e:	630134        	ae_sq56s.i	aeq0, a1, 24
     811:	d56bba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16u.h	aeq2, aeq1, aep2 }
     816:	632144        	ae_sq56s.i	aeq2, a1, 32
     819:	618154        	ae_lq56.i	aeq2, a1, 40
     81c:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     81f:	f58fbde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq1, aep3 }
     824:	353434        	ae_sraiq56	aeq0, aeq3, 16
     827:	f48bbda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep2 }
     82c:	f9ea3dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq1, aeq1, aeq2 }
     831:	f8a2fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     836:	618124        	ae_lq56.i	aeq2, a1, 16
     839:	35a074        	ae_sraiq56	aeq2, aeq2, 1
     83c:	fe347b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_roundsq32asym	aeq2, aeq2 }
     841:	fc245ba3bf 	{ ae_lp16x2f.xu	aep2, a3, a11; ae_roundsq32asym	aeq0, aeq0 }
     846:	626414        	ae_sq32f.iu	aeq2, a4, 4
     849:	60fca4        	ae_lq32f.xu	aeq3, a12, a10
     84c:	604c14        	ae_lq32f.i	aeq1, a12, 4
     84f:	443314        	ae_lp16x2f.i	aep3, a3, 4
     852:	624414        	ae_sq32f.iu	aeq0, a4, 4

00000855 <fix_fft40+0x239>:
     855:	372172        	l32i	a7, a1, 220
     858:	600624        	ae_lq32f.i	aeq0, a6, 8
     85b:	630124        	ae_sq56s.i	aeq0, a1, 16
     85e:	60c724        	ae_lq32f.i	aeq3, a7, 8
     861:	633134        	ae_sq56s.i	aeq3, a1, 24
     864:	604734        	ae_lq32f.i	aeq1, a7, 12
     867:	608604        	ae_lq32f.i	aeq2, a6, 0
     86a:	631144        	ae_sq56s.i	aeq1, a1, 32
     86d:	632154        	ae_sq56s.i	aeq2, a1, 40
     870:	618124        	ae_lq56.i	aeq2, a1, 16
     873:	614134        	ae_lq56.i	aeq1, a1, 24
     876:	fa36fd663f 	{ ae_lq32f.i	aeq3, a6, 12; ae_subq56	aeq2, aeq2, aeq1 }
     87b:	614144        	ae_lq56.i	aeq1, a1, 32
     87e:	01d142        	addmi	a4, a1, 0x100
     881:	f93ec7812e 	{ addi	a2, a1, 120; ae_subq56	aeq1, aeq3, aeq1 }
     886:	40c442        	addi	a4, a4, 64
     889:	6312a4        	ae_sq56s.i	aeq1, a2, -48
     88c:	600704        	ae_lq32f.i	aeq0, a7, 0
     88f:	614154        	ae_lq56.i	aeq1, a1, 40
     892:	fa6a39a46f 	{ ae_sq32f.i	aeq2, a4, 24; ae_addq56	aeq2, aeq1, aeq0 }
     897:	f82afda2af 	{ ae_lq56.i	aeq1, a2, -48; ae_subq56	aeq0, aeq1, aeq0 }
     89c:	630164        	ae_sq56s.i	aeq0, a1, 48
     89f:	3520b4        	ae_sraiq56	aeq0, aeq2, 2
     8a2:	fd2479947f 	{ ae_sq32f.i	aeq1, a4, 28; ae_roundsq32asym	aeq1, aeq0 }
     8a7:	608614        	ae_lq32f.i	aeq2, a6, 4
     8aa:	600714        	ae_lq32f.i	aeq0, a7, 4
     8ad:	f97239940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_addq56	aeq1, aeq2, aeq0 }
     8b2:	f832fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_subq56	aeq0, aeq2, aeq0 }
     8b7:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
     8ba:	630154        	ae_sq56s.i	aeq0, a1, 40
     8bd:	fe2c7b202f 	{ ae_sraiq56	aeq0, aeq2, 2; ae_roundsq32asym	aeq2, aeq1 }
     8c2:	fc2479a41f 	{ ae_sq32f.i	aeq2, a4, 4; ae_roundsq32asym	aeq0, aeq0 }
     8c7:	614124        	ae_lq56.i	aeq1, a1, 16
     8ca:	618134        	ae_lq56.i	aeq2, a1, 24
     8cd:	f9ea3dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_addq56	aeq1, aeq1, aeq2 }
     8d2:	fbfa3dc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_addq56	aeq3, aeq3, aeq2 }
     8d7:	35a0b4        	ae_sraiq56	aeq2, aeq2, 2
     8da:	fe347b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq2 }
     8df:	ff3c79842f 	{ ae_sq32f.i	aeq0, a4, 8; ae_roundsq32asym	aeq3, aeq3 }
     8e4:	622434        	ae_sq32f.i	aeq2, a4, 12
     8e7:	600644        	ae_lq32f.i	aeq0, a6, 16
     8ea:	608744        	ae_lq32f.i	aeq2, a7, 16
     8ed:	fbe239b45f 	{ ae_sq32f.i	aeq3, a4, 20; ae_addq56	aeq3, aeq0, aeq2 }
     8f2:	faa2fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq2, aeq0, aeq2 }
     8f7:	fd2c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq1, aeq1 }
     8fc:	632134        	ae_sq56s.i	aeq2, a1, 24
     8ff:	608664        	ae_lq32f.i	aeq2, a6, 24
     902:	3821d2        	l32i	a13, a1, 224
     905:	632124        	ae_sq56s.i	aeq2, a1, 16
     908:	618134        	ae_lq56.i	aeq2, a1, 24
     90b:	fe3479944f 	{ ae_sq32f.i	aeq1, a4, 16; ae_roundsq32asym	aeq2, aeq2 }
     910:	604654        	ae_lq32f.i	aeq1, a6, 20
     913:	600754        	ae_lq32f.i	aeq0, a7, 20
     916:	fa6a39ad2f 	{ ae_sq32f.i	aeq2, a13, 8; ae_addq56	aeq2, aeq1, aeq0 }
     91b:	f82afb30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_subq56	aeq0, aeq1, aeq0 }
     920:	ff3c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq3, aeq3 }
     925:	fe347b002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_roundsq32asym	aeq2, aeq2 }
     92a:	fc2479bd0f 	{ ae_sq32f.i	aeq3, a13, 0; ae_roundsq32asym	aeq0, aeq0 }
     92f:	60c764        	ae_lq32f.i	aeq3, a7, 24
     932:	fd1c79ad1f 	{ ae_sq32f.i	aeq2, a13, 4; ae_movq56	aeq1, aeq3 }
     937:	608674        	ae_lq32f.i	aeq2, a6, 28
     93a:	630154        	ae_sq56s.i	aeq0, a1, 40
     93d:	610124        	ae_lq56.i	aeq0, a1, 16
     940:	fbe63a214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_addq56	aeq3, aeq0, aeq3 }
     945:	f826fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq0, aeq0, aeq1 }
     94a:	61c154        	ae_lq56.i	aeq3, a1, 40
     94d:	608774        	ae_lq32f.i	aeq2, a7, 28
     950:	614144        	ae_lq56.i	aeq1, a1, 32
     953:	f8aafa012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_subq56	aeq0, aeq1, aeq2 }
     958:	fbea39bd3f 	{ ae_sq32f.i	aeq3, a13, 12; ae_addq56	aeq3, aeq1, aeq2 }
     95d:	618134        	ae_lq56.i	aeq2, a1, 24
     960:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     963:	fe2c7b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq1 }
     968:	fe3c79ad4f 	{ ae_sq32f.i	aeq2, a13, 16; ae_roundsq32asym	aeq2, aeq3 }
     96d:	61c124        	ae_lq56.i	aeq3, a1, 16
     970:	622d54        	ae_sq32f.i	aeq2, a13, 20
     973:	620d74        	ae_sq32f.i	aeq0, a13, 28
     976:	623d64        	ae_sq32f.i	aeq3, a13, 24
     979:	600d04        	ae_lq32f.i	aeq0, a13, 0
     97c:	604404        	ae_lq32f.i	aeq1, a4, 0
     97f:	fb6a3d4d1f 	{ ae_lq32f.i	aeq2, a13, 4; ae_addq56	aeq3, aeq1, aeq0 }
     984:	01d132        	addmi	a3, a1, 0x100
     987:	f92afd0d3f 	{ ae_lq32f.i	aeq0, a13, 12; ae_subq56	aeq1, aeq1, aeq0 }
     98c:	623304        	ae_sq32f.i	aeq3, a3, 0
     98f:	630124        	ae_sq56s.i	aeq0, a1, 16
     992:	60c414        	ae_lq32f.i	aeq3, a4, 4
     995:	f8fa3361ae 	{ l32i	a10, a1, 216; ae_addq56	aeq0, aeq3, aeq2 }
     99a:	fabaf9934f 	{ ae_sq32f.i	aeq1, a3, 16; ae_subq56	aeq2, aeq3, aeq2 }
     99f:	604424        	ae_lq32f.i	aeq1, a4, 8
     9a2:	61c124        	ae_lq56.i	aeq3, a1, 16
     9a5:	faaef9a35f 	{ ae_sq32f.i	aeq2, a3, 20; ae_subq56	aeq2, aeq1, aeq3 }
     9aa:	f9ee39831f 	{ ae_sq32f.i	aeq0, a3, 4; ae_addq56	aeq1, aeq1, aeq3 }
     9af:	622a04        	ae_sq32f.i	aeq2, a10, 0
     9b2:	60c434        	ae_lq32f.i	aeq3, a4, 12
     9b5:	608d24        	ae_lq32f.i	aeq2, a13, 8
     9b8:	f9fa399a2f 	{ ae_sq32f.i	aeq1, a10, 8; ae_addq56	aeq1, aeq3, aeq2 }
     9bd:	fabafd046f 	{ ae_lq32f.i	aeq0, a4, 24; ae_subq56	aeq2, aeq3, aeq2 }
     9c2:	60cd64        	ae_lq32f.i	aeq3, a13, 24
     9c5:	fae63a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_addq56	aeq2, aeq0, aeq3 }
     9ca:	fba6f99a1f 	{ ae_sq32f.i	aeq1, a10, 4; ae_subq56	aeq3, aeq0, aeq3 }
     9cf:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     9d2:	fe2c7d2d5f 	{ ae_lq32f.i	aeq1, a13, 20; ae_roundsq32asym	aeq2, aeq1 }
     9d7:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
     9da:	fd3c7a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq1, aeq3 }
     9df:	600d44        	ae_lq32f.i	aeq0, a13, 16
     9e2:	621424        	ae_sq32f.i	aeq1, a4, 8
     9e5:	622414        	ae_sq32f.i	aeq2, a4, 4
     9e8:	614124        	ae_lq56.i	aeq1, a1, 16
     9eb:	608d74        	ae_lq32f.i	aeq2, a13, 28
     9ee:	60c474        	ae_lq32f.i	aeq3, a4, 28
     9f1:	f9fa399a3f 	{ ae_sq32f.i	aeq1, a10, 12; ae_addq56	aeq1, aeq3, aeq2 }
     9f6:	fabafd644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_subq56	aeq2, aeq3, aeq2 }
     9fb:	fa7a3a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_addq56	aeq2, aeq3, aeq0 }
     a00:	f83afb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq3, aeq0 }
     a05:	fd2c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq1, aeq1 }
     a0a:	630124        	ae_sq56s.i	aeq0, a1, 16
     a0d:	3530b4        	ae_sraiq56	aeq0, aeq3, 2
     a10:	ff2479940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_roundsq32asym	aeq3, aeq0 }
     a15:	600454        	ae_lq32f.i	aeq0, a4, 20
     a18:	614144        	ae_lq56.i	aeq1, a1, 32
     a1b:	622324        	ae_sq32f.i	aeq2, a3, 8
     a1e:	fb6639b43f 	{ ae_sq32f.i	aeq3, a4, 12; ae_addq56	aeq3, aeq0, aeq1 }
     a23:	f82afd440f 	{ ae_lq32f.i	aeq2, a4, 0; ae_subq56	aeq0, aeq1, aeq0 }
     a28:	632154        	ae_sq56s.i	aeq2, a1, 40
     a2b:	633134        	ae_sq56s.i	aeq3, a1, 24
     a2e:	60c424        	ae_lq32f.i	aeq3, a4, 8
     a31:	fd1c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_movq56	aeq1, aeq3 }
     a36:	610154        	ae_lq56.i	aeq0, a1, 40
     a39:	fbe63d443f 	{ ae_lq32f.i	aeq2, a4, 12; ae_addq56	aeq3, aeq0, aeq3 }
     a3e:	f826fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_subq56	aeq0, aeq0, aeq1 }
     a43:	614124        	ae_lq56.i	aeq1, a1, 16
     a46:	608414        	ae_lq32f.i	aeq2, a4, 4
     a49:	621374        	ae_sq32f.i	aeq1, a3, 28
     a4c:	614294        	ae_lq56.i	aeq1, a2, -56
     a4f:	fbaafa32af 	{ ae_sq56s.i	aeq3, a2, -48; ae_subq56	aeq3, aeq1, aeq2 }
     a54:	fa763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq2, aeq2, aeq1 }
     a59:	610134        	ae_lq56.i	aeq0, a1, 24
     a5c:	633124        	ae_sq56s.i	aeq3, a1, 16
     a5f:	61c2a4        	ae_lq56.i	aeq3, a2, -48
     a62:	d6e3b9833f 	{ ae_sq32f.i	aeq0, a3, 12; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
     a67:	614144        	ae_lq56.i	aeq1, a1, 32
     a6a:	630164        	ae_sq56s.i	aeq0, a1, 48
     a6d:	610154        	ae_lq56.i	aeq0, a1, 40
     a70:	d5e2ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
     a75:	621364        	ae_sq32f.i	aeq1, a3, 24
     a78:	614124        	ae_lq56.i	aeq1, a1, 16
     a7b:	d4e3fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     a80:	618164        	ae_lq56.i	aeq2, a1, 48
     a83:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a86:	f703ba116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_mulafq32sp16s.h	aeq2, aeq3, aep0 }
     a8b:	61c164        	ae_lq56.i	aeq3, a1, 48
     a8e:	357434        	ae_sraiq56	aeq1, aeq3, 16
     a91:	61c134        	ae_lq56.i	aeq3, a1, 24
     a94:	d7e7fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep1 }
     a99:	618294        	ae_lq56.i	aeq2, a2, -56
     a9c:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a9f:	f502b351fe 	{ l32i	a15, a1, 212; ae_mulafq32sp16s.h	aeq2, aeq0, aep0 }
     aa4:	353434        	ae_sraiq56	aeq0, aeq3, 16
     aa7:	61c124        	ae_lq56.i	aeq3, a1, 16
     aaa:	f603fde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.h	aeq1, aeq3, aep0 }
     aaf:	623f04        	ae_sq32f.i	aeq3, a15, 0
     ab2:	61c134        	ae_lq56.i	aeq3, a1, 24
     ab5:	f607b9af2f 	{ ae_sq32f.i	aeq2, a15, 8; ae_mulafq32sp16s.h	aeq0, aeq3, aep1 }
     aba:	621f14        	ae_sq32f.i	aeq1, a15, 4
     abd:	620f34        	ae_sq32f.i	aeq0, a15, 12
     ac0:	604304        	ae_lq32f.i	aeq1, a3, 0
     ac3:	608324        	ae_lq32f.i	aeq2, a3, 8
     ac6:	fbea3251be 	{ l32i	a11, a1, 148; ae_addq56	aeq3, aeq1, aeq2 }
     acb:	faaafa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq2, aeq1, aeq2 }
     ad0:	2421f2        	l32i	a15, a1, 144
     ad3:	614124        	ae_lq56.i	aeq1, a1, 16
     ad6:	369204        	ae_trunca32q48	a2, aeq1
     ad9:	60c314        	ae_lq32f.i	aeq3, a3, 4
     adc:	600334        	ae_lq32f.i	aeq0, a3, 12
     adf:	fa7a3f26ef 	{ ae_trunca32q48	a6, aeq2; ae_addq56	aeq2, aeq3, aeq0 }
     ae4:	0b29           	s32i.n	a2, a11, 0
     ae6:	0f69           	s32i.n	a6, a15, 0
     ae8:	f83afd2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_subq56	aeq0, aeq3, aeq0 }
     aed:	60ca44        	ae_lq32f.i	aeq3, a10, 16
     af0:	2721f2        	l32i	a15, a1, 156
     af3:	302122        	l32i	a2, a1, 192
     af6:	e148           	l32i.n	a4, a1, 56
     af8:	36ac04        	ae_trunca32q48	a12, aeq2
     afb:	f8ee3f08ef 	{ ae_trunca32q48	a8, aeq0; ae_addq56	aeq0, aeq1, aeq3 }
     b00:	f9aefd4a3f 	{ ae_lq32f.i	aeq2, a10, 12; ae_subq56	aeq1, aeq1, aeq3 }
     b05:	60ca54        	ae_lq32f.i	aeq3, a10, 20
     b08:	f8f63f07ef 	{ ae_trunca32q48	a7, aeq0; ae_addq56	aeq0, aeq2, aeq3 }
     b0d:	fab6ff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq2, aeq2, aeq3 }
     b12:	36ae04        	ae_trunca32q48	a14, aeq2
     b15:	0fc9           	s32i.n	a12, a15, 0
     b17:	0289           	s32i.n	a8, a2, 0
     b19:	0479           	s32i.n	a7, a4, 0
     b1b:	600344        	ae_lq32f.i	aeq0, a3, 16
     b1e:	608364        	ae_lq32f.i	aeq2, a3, 24
     b21:	282162        	l32i	a6, a1, 160
     b24:	3e2172        	l32i	a7, a1, 248
     b27:	fd047f19ef 	{ ae_trunca32q48	a9, aeq1; ae_movq56	aeq1, aeq0 }
     b2c:	f8a2fd635f 	{ ae_lq32f.i	aeq3, a3, 20; ae_subq56	aeq0, aeq0, aeq2 }
     b31:	f9ea3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq1, aeq1, aeq2 }
     b36:	0699           	s32i.n	a9, a6, 0
     b38:	633134        	ae_sq56s.i	aeq3, a1, 24
     b3b:	60c374        	ae_lq32f.i	aeq3, a3, 28
     b3e:	07d9           	s32i.n	a13, a7, 0
     b40:	07dd           	mov.n	a13, a7
     b42:	610124        	ae_lq56.i	aeq0, a1, 16
     b45:	608a04        	ae_lq32f.i	aeq2, a10, 0
     b48:	2b21b2        	l32i	a11, a1, 172
     b4b:	312162        	l32i	a6, a1, 196
     b4e:	292172        	l32i	a7, a1, 164
     b51:	fc1c7f08ef 	{ ae_trunca32q48	a8, aeq0; ae_movq56	aeq0, aeq3 }
     b56:	632144        	ae_sq56s.i	aeq2, a1, 32
     b59:	618134        	ae_lq56.i	aeq2, a1, 24
     b5c:	fbb6ff19ef 	{ ae_trunca32q48	a9, aeq1; ae_subq56	aeq3, aeq2, aeq3 }
     b61:	fa723d2a6f 	{ ae_lq32f.i	aeq1, a10, 24; ae_addq56	aeq2, aeq2, aeq0 }
     b66:	610144        	ae_lq56.i	aeq0, a1, 32
     b69:	0be9           	s32i.n	a14, a11, 0
     b6b:	633124        	ae_sq56s.i	aeq3, a1, 16
     b6e:	0689           	s32i.n	a8, a6, 0
     b70:	0799           	s32i.n	a9, a7, 0
     b72:	fe0c7f29ef 	{ ae_trunca32q48	a9, aeq2; ae_movq56	aeq2, aeq1 }
     b77:	f96633d1ee 	{ l32i	a14, a1, 244; ae_addq56	aeq1, aeq0, aeq1 }
     b7c:	f8a2fde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     b81:	631124        	ae_sq56s.i	aeq1, a1, 16
     b84:	2c2142        	l32i	a4, a1, 176
     b87:	36bc04        	ae_trunca32q48	a12, aeq3
     b8a:	60ca14        	ae_lq32f.i	aeq3, a10, 4
     b8d:	614124        	ae_lq56.i	aeq1, a1, 16
     b90:	633134        	ae_sq56s.i	aeq3, a1, 24
     b93:	0ec9           	s32i.n	a12, a14, 0
     b95:	369c04        	ae_trunca32q48	a12, aeq1
     b98:	60ca74        	ae_lq32f.i	aeq3, a10, 28
     b9b:	0499           	s32i.n	a9, a4, 0
     b9d:	618134        	ae_lq56.i	aeq2, a1, 24
     ba0:	f9f61405cf 	{ s32i.n	a12, a5, 0; ae_addq56	aeq1, aeq2, aeq3 }
     ba5:	3b6152        	s32i	a5, a1, 236
     ba8:	fbb6f2f15e 	{ l32i	a5, a1, 188; ae_subq56	aeq3, aeq2, aeq3 }
     bad:	2d21a2        	l32i	a10, a1, 180
     bb0:	368704        	ae_trunca32q48	a7, aeq0
     bb3:	369904        	ae_trunca32q48	a9, aeq1
     bb6:	0579           	s32i.n	a7, a5, 0
     bb8:	0a99           	s32i.n	a9, a10, 0
     bba:	3c2182        	l32i	a8, a1, 240
     bbd:	3a2172        	l32i	a7, a1, 232
     bc0:	392192        	l32i	a9, a1, 228
     bc3:	3f2132        	l32i	a3, a1, 252
     bc6:	36bc04        	ae_trunca32q48	a12, aeq3
     bc9:	08c9           	s32i.n	a12, a8, 0
     bcb:	c78b           	addi.n	a12, a7, 8
     bcd:	790b           	addi.n	a7, a9, -1
     bcf:	938b           	addi.n	a9, a3, 8
     bd1:	2e2132        	l32i	a3, a1, 184
     bd4:	443a           	add.n	a4, a4, a3
     bd6:	2c6142        	s32i	a4, a1, 176
     bd9:	252142        	l32i	a4, a1, 148
     bdc:	223a           	add.n	a2, a2, a3
     bde:	306122        	s32i	a2, a1, 192
     be1:	243a           	add.n	a2, a4, a3
     be3:	256122        	s32i	a2, a1, 148
     be6:	3b2122        	l32i	a2, a1, 236
     be9:	292142        	l32i	a4, a1, 164
     bec:	663a           	add.n	a6, a6, a3
     bee:	553a           	add.n	a5, a5, a3
     bf0:	316162        	s32i	a6, a1, 196
     bf3:	282162        	l32i	a6, a1, 160
     bf6:	2f6152        	s32i	a5, a1, 188
     bf9:	523a           	add.n	a5, a2, a3
     bfb:	243a           	add.n	a2, a4, a3
     bfd:	296122        	s32i	a2, a1, 164
     c00:	e128           	l32i.n	a2, a1, 56
     c02:	463a           	add.n	a4, a6, a3
     c04:	242162        	l32i	a6, a1, 144
     c07:	286142        	s32i	a4, a1, 160
     c0a:	423a           	add.n	a4, a2, a3
     c0c:	bb3a           	add.n	a11, a11, a3
     c0e:	aa3a           	add.n	a10, a10, a3
     c10:	e149           	s32i.n	a4, a1, 56
     c12:	463a           	add.n	a4, a6, a3
     c14:	2b61b2        	s32i	a11, a1, 172
     c17:	2d61a2        	s32i	a10, a1, 180
     c1a:	ff3a           	add.n	a15, a15, a3
     c1c:	dd3a           	add.n	a13, a13, a3
     c1e:	0b2c           	movi.n	a11, 32
     c20:	ee3a           	add.n	a14, a14, a3
     c22:	8a2c           	movi.n	a10, 40
     c24:	883a           	add.n	a8, a8, a3
     c26:	246142        	s32i	a4, a1, 144
     c29:	051716        	beqz	a7, c7e <fix_fft40+0x662>

00000c2c <fix_fft40+0x610>:
     c2c:	d8cc32        	addi	a3, a12, -40
     c2f:	0348           	l32i.n	a4, a3, 0
     c31:	1338           	l32i.n	a3, a3, 4
     c33:	2761f2        	s32i	a15, a1, 156
     c36:	214140        	srai	a4, a4, 1
     c39:	213130        	srai	a3, a3, 1
     c3c:	146142        	s32i	a4, a1, 80
     c3f:	156132        	s32i	a3, a1, 84
     c42:	3f6192        	s32i	a9, a1, 252
     c45:	3e61d2        	s32i	a13, a1, 248
     c48:	3d61e2        	s32i	a14, a1, 244
     c4b:	3c6182        	s32i	a8, a1, 240
     c4e:	3a61c2        	s32i	a12, a1, 232
     c51:	396172        	s32i	a7, a1, 228
     c54:	025726        	beqi	a7, 5, c5a <fix_fft40+0x63e>
     c57:	fee106        	j	7df <fix_fft40+0x1c3>
     c5a:	332142        	l32i	a4, a1, 204
     c5d:	2a2162        	l32i	a6, a1, 168
     c60:	720c           	movi.n	a2, 7
     c62:	203cc0        	or	a3, a12, a12
     c65:	128276        	loop	a2, c7b <fix_fft40+0x65f>
     c68:	03c8           	l32i.n	a12, a3, 0
     c6a:	1378           	l32i.n	a7, a3, 4
     c6c:	28c332        	addi	a3, a3, 40
     c6f:	21c1c0        	srai	a12, a12, 1
     c72:	217170        	srai	a7, a7, 1
     c75:	04c9           	s32i.n	a12, a4, 0
     c77:	1479           	s32i.n	a7, a4, 4
     c79:	448b           	addi.n	a4, a4, 8

00000c7b <fix_fft40+0x65f>:
     c7b:	fef586        	j	855 <fix_fft40+0x239>

00000c7e <fix_fft40+0x662>:
     c7e:	fd0221        	l32r	a2, 88 (2b74 <LC3Plus_lc3_scratch_pop>)
     c81:	3221a2        	l32i	a10, a1, 200
     c84:	2621b2        	l32i	a11, a1, 152
     c87:	0002e0        	callx8	a2
     c8a:	f01d           	retw.n

00000c8c <FFT8N>:
     c8c:	020136        	entry	a1, 0x100
     c8f:	186132        	s32i	a3, a1, 96
     c92:	176122        	s32i	a2, a1, 92
     c95:	0215e6        	bgei	a5, 1, c9b <FFT8N+0xf>
     c98:	01b346        	j	1369 <FFT8N+0x6dd>
     c9b:	d1e750        	mul16s	a14, a7, a5
     c9e:	412132        	l32i	a3, a1, 0x104
     ca1:	11a6e0        	slli	a10, a6, 2
     ca4:	90cee0        	addx2	a12, a14, a14
     ca7:	11b7e0        	slli	a11, a7, 2
     caa:	a08ee0        	addx4	a8, a14, a14
     cad:	3061a2        	s32i	a10, a1, 192
     cb0:	11acf0        	slli	a10, a12, 1
     cb3:	f09ee0        	subx8	a9, a14, a14
     cb6:	2f61b2        	s32i	a11, a1, 188
     cb9:	e0be30        	subx4	a11, a14, a3
     cbc:	c07c30        	sub	a7, a12, a3
     cbf:	d0ce30        	subx2	a12, a14, a3
     cc2:	c0aa30        	sub	a10, a10, a3
     cc5:	c08830        	sub	a8, a8, a3
     cc8:	c0ee30        	sub	a14, a14, a3
     ccb:	c03930        	sub	a3, a9, a3
     cce:	172192        	l32i	a9, a1, 92
     cd1:	d12650        	mul16s	a2, a6, a5
     cd4:	a06840        	addx4	a6, a8, a4
     cd7:	a08a40        	addx4	a8, a10, a4
     cda:	a0a740        	addx4	a10, a7, a4
     cdd:	182172        	l32i	a7, a1, 96
     ce0:	a0f290        	addx4	a15, a2, a9
     ce3:	a0bb40        	addx4	a11, a11, a4
     ce6:	2e61f2        	s32i	a15, a1, 184
     ce9:	a0fc40        	addx4	a15, a12, a4
     cec:	a03340        	addx4	a3, a3, a4
     cef:	a04e40        	addx4	a4, a14, a4
     cf2:	216162        	s32i	a6, a1, 132
     cf5:	206182        	s32i	a8, a1, 128
     cf8:	1c61a2        	s32i	a10, a1, 112
     cfb:	c1b9           	s32i.n	a11, a1, 48
     cfd:	a06270        	addx4	a6, a2, a7
     d00:	b08290        	addx8	a8, a2, a9
     d03:	b0a270        	addx8	a10, a2, a7
     d06:	90b220        	addx2	a11, a2, a2
     d09:	f0c220        	subx8	a12, a2, a2
     d0c:	a0e220        	addx4	a14, a2, a2
     d0f:	1122c0        	slli	a2, a2, 4
     d12:	4021d2        	l32i	a13, a1, 0x100
     d15:	226132        	s32i	a3, a1, 136
     d18:	1b61f2        	s32i	a15, a1, 108
     d1b:	1f6142        	s32i	a4, a1, 124
     d1e:	114ce0        	slli	a4, a12, 2
     d21:	f72a           	add.n	a15, a7, a2
     d23:	292a           	add.n	a2, a9, a2
     d25:	113bd0        	slli	a3, a11, 3
     d28:	2b6122        	s32i	a2, a1, 172
     d2b:	112be0        	slli	a2, a11, 2
     d2e:	b74a           	add.n	a11, a7, a4
     d30:	c94a           	add.n	a12, a9, a4
     d32:	473a           	add.n	a4, a7, a3
     d34:	393a           	add.n	a3, a9, a3
     d36:	246162        	s32i	a6, a1, 144
     d39:	116ee0        	slli	a6, a14, 2
     d3c:	e92a           	add.n	a14, a9, a2
     d3e:	286132        	s32i	a3, a1, 160
     d41:	272a           	add.n	a2, a7, a2
     d43:	f03550        	subx8	a3, a5, a5
     d46:	2d6182        	s32i	a8, a1, 180
     d49:	876a           	add.n	a8, a7, a6
     d4b:	2c61a2        	s32i	a10, a1, 176
     d4e:	a96a           	add.n	a10, a9, a6
     d50:	236122        	s32i	a2, a1, 140
     d53:	b023d0        	addx8	a2, a3, a13
     d56:	a06550        	addx4	a6, a5, a5
     d59:	1e6122        	s32i	a2, a1, 120
     d5c:	b026d0        	addx8	a2, a6, a13
     d5f:	1175b0        	slli	a7, a5, 5
     d62:	2a6182        	s32i	a8, a1, 168
     d65:	b129           	s32i.n	a2, a1, 44
     d67:	2d7a           	add.n	a2, a13, a7
     d69:	908550        	addx2	a8, a5, a5
     d6c:	2961a2        	s32i	a10, a1, 164
     d6f:	1a6122        	s32i	a2, a1, 104
     d72:	1198c0        	slli	a9, a8, 4
     d75:	b028d0        	addx8	a2, a8, a13
     d78:	11a5c0        	slli	a10, a5, 4
     d7b:	2761e2        	s32i	a14, a1, 156
     d7e:	3d9a           	add.n	a3, a13, a9
     d80:	196122        	s32i	a2, a1, 100
     d83:	2daa           	add.n	a2, a13, a10
     d85:	b0e5d0        	addx8	a14, a5, a13
     d88:	070c           	movi.n	a7, 0
     d8a:	a139           	s32i.n	a3, a1, 40
     d8c:	086122        	s32i	a2, a1, 32
     d8f:	2561d2        	s32i	a13, a1, 148
     d92:	0d61e2        	s32i	a14, a1, 52
     d95:	178576        	loop	a5, db0 <FFT8N+0x124>
     d98:	030150        	rsr.lend	a5
     d9b:	130050        	wsr.lbeg	a5
     d9e:	fcbb51        	l32r	a5, 8c (1369 <FFT8N+0x6dd>)
     da1:	0020f0        	nop
     da4:	130150        	wsr.lend	a5
     da7:	002000        	isync
     daa:	030250        	rsr.lcount	a5
     dad:	01c552        	addi	a5, a5, 1
     db0:	252122        	l32i	a2, a1, 148
     db3:	d1a8           	l32i.n	a10, a1, 52
     db5:	346142        	s32i	a4, a1, 208
     db8:	0238           	l32i.n	a3, a2, 0
     dba:	1298           	l32i.n	a9, a2, 4
     dbc:	0a68           	l32i.n	a6, a10, 0
     dbe:	331b           	addi.n	a3, a3, 1
     dc0:	491b           	addi.n	a4, a9, 1
     dc2:	21d130        	srai	a13, a3, 1
     dc5:	21e140        	srai	a14, a4, 1
     dc8:	3761f2        	s32i	a15, a1, 220
     dcb:	3661b2        	s32i	a11, a1, 216
     dce:	3561c2        	s32i	a12, a1, 212
     dd1:	266172        	s32i	a7, a1, 152
     dd4:	1d61d2        	s32i	a13, a1, 116
     dd7:	91e9           	s32i.n	a14, a1, 36
     dd9:	4169           	s32i.n	a6, a1, 16
     ddb:	213716        	beqz	a7, ff2 <FFT8N+0x366>
     dde:	8128           	l32i.n	a2, a1, 32
     de0:	1b2132        	l32i	a3, a1, 108
     de3:	c198           	l32i.n	a9, a1, 48
     de5:	0278           	l32i.n	a7, a2, 0
     de7:	0348           	l32i.n	a4, a3, 0
     de9:	192152        	l32i	a5, a1, 100
     dec:	1c2162        	l32i	a6, a1, 112
     def:	13c8           	l32i.n	a12, a3, 4
     df1:	8129           	s32i.n	a2, a1, 32
     df3:	12a8           	l32i.n	a10, a2, 4
     df5:	822740        	mull	a2, a7, a4
     df8:	05b8           	l32i.n	a11, a5, 0
     dfa:	15d8           	l32i.n	a13, a5, 4
     dfc:	0688           	l32i.n	a8, a6, 0
     dfe:	1658           	l32i.n	a5, a6, 4
     e00:	09e8           	l32i.n	a14, a9, 0
     e02:	096d           	mov.n	a6, a9
     e04:	c199           	s32i.n	a9, a1, 48
     e06:	b29740        	mulsh	a9, a7, a4
     e09:	052f20        	extui	a2, a2, 31, 1
     e0c:	902920        	addx2	a2, a9, a2
     e0f:	8297c0        	mull	a9, a7, a12
     e12:	b277c0        	mulsh	a7, a7, a12
     e15:	059f90        	extui	a9, a9, 31, 1
     e18:	909790        	addx2	a9, a7, a9
     e1b:	827ac0        	mull	a7, a10, a12
     e1e:	b2cac0        	mulsh	a12, a10, a12
     e21:	057f70        	extui	a7, a7, 31, 1
     e24:	907c70        	addx2	a7, a12, a7
     e27:	c02270        	sub	a2, a2, a7
     e2a:	7129           	s32i.n	a2, a1, 28
     e2c:	b22a40        	mulsh	a2, a10, a4
     e2f:	824a40        	mull	a4, a10, a4
     e32:	82ab50        	mull	a10, a11, a5
     e35:	054f40        	extui	a4, a4, 31, 1
     e38:	902240        	addx2	a2, a2, a4
     e3b:	824b80        	mull	a4, a11, a8
     e3e:	292a           	add.n	a2, a9, a2
     e40:	1a2132        	l32i	a3, a1, 104
     e43:	f129           	s32i.n	a2, a1, 60
     e45:	b29b80        	mulsh	a9, a11, a8
     e48:	052f40        	extui	a2, a4, 31, 1
     e4b:	054fa0        	extui	a4, a10, 31, 1
     e4e:	b2bb50        	mulsh	a11, a11, a5
     e51:	82ad50        	mull	a10, a13, a5
     e54:	b25d50        	mulsh	a5, a13, a5
     e57:	03f8           	l32i.n	a15, a3, 0
     e59:	902920        	addx2	a2, a9, a2
     e5c:	059fa0        	extui	a9, a10, 31, 1
     e5f:	904b40        	addx2	a4, a11, a4
     e62:	b2bd80        	mulsh	a11, a13, a8
     e65:	82dd80        	mull	a13, a13, a8
     e68:	16c8           	l32i.n	a12, a6, 4
     e6a:	b168           	l32i.n	a6, a1, 44
     e6c:	905590        	addx2	a5, a5, a9
     e6f:	2121a2        	l32i	a10, a1, 132
     e72:	1338           	l32i.n	a3, a3, 4
     e74:	c02250        	sub	a2, a2, a5
     e77:	055fd0        	extui	a5, a13, 31, 1
     e7a:	166122        	s32i	a2, a1, 88
     e7d:	902b50        	addx2	a2, a11, a5
     e80:	82bfe0        	mull	a11, a15, a14
     e83:	242a           	add.n	a2, a4, a2
     e85:	825fc0        	mull	a5, a15, a12
     e88:	0678           	l32i.n	a7, a6, 0
     e8a:	b169           	s32i.n	a6, a1, 44
     e8c:	1688           	l32i.n	a8, a6, 4
     e8e:	0a98           	l32i.n	a9, a10, 0
     e90:	b2dfe0        	mulsh	a13, a15, a14
     e93:	b26fc0        	mulsh	a6, a15, a12
     e96:	0afd           	mov.n	a15, a10
     e98:	82a3c0        	mull	a10, a3, a12
     e9b:	136122        	s32i	a2, a1, 76
     e9e:	052fb0        	extui	a2, a11, 31, 1
     ea1:	b2b3c0        	mulsh	a11, a3, a12
     ea4:	054f50        	extui	a4, a5, 31, 1
     ea7:	055fa0        	extui	a5, a10, 31, 1
     eaa:	b2c3e0        	mulsh	a12, a3, a14
     ead:	8233e0        	mull	a3, a3, a14
     eb0:	902d20        	addx2	a2, a13, a2
     eb3:	905b50        	addx2	a5, a11, a5
     eb6:	1fa8           	l32i.n	a10, a15, 4
     eb8:	c02250        	sub	a2, a2, a5
     ebb:	053f30        	extui	a3, a3, 31, 1
     ebe:	904640        	addx2	a4, a6, a4
     ec1:	6129           	s32i.n	a2, a1, 24
     ec3:	902c30        	addx2	a2, a12, a3
     ec6:	82d790        	mull	a13, a7, a9
     ec9:	242a           	add.n	a2, a4, a2
     ecb:	b2e790        	mulsh	a14, a7, a9
     ece:	8247a0        	mull	a4, a7, a10
     ed1:	146122        	s32i	a2, a1, 80
     ed4:	052fd0        	extui	a2, a13, 31, 1
     ed7:	a168           	l32i.n	a6, a1, 40
     ed9:	902e20        	addx2	a2, a14, a2
     edc:	b277a0        	mulsh	a7, a7, a10
     edf:	82b8a0        	mull	a11, a8, a10
     ee2:	2021e2        	l32i	a14, a1, 128
     ee5:	053f40        	extui	a3, a4, 31, 1
     ee8:	b2a8a0        	mulsh	a10, a8, a10
     eeb:	903730        	addx2	a3, a7, a3
     eee:	057fb0        	extui	a7, a11, 31, 1
     ef1:	907a70        	addx2	a7, a10, a7
     ef4:	0658           	l32i.n	a5, a6, 0
     ef6:	0ea8           	l32i.n	a10, a14, 0
     ef8:	82d890        	mull	a13, a8, a9
     efb:	b2c890        	mulsh	a12, a8, a9
     efe:	1e88           	l32i.n	a8, a14, 4
     f00:	c02270        	sub	a2, a2, a7
     f03:	057fd0        	extui	a7, a13, 31, 1
     f06:	16d8           	l32i.n	a13, a6, 4
     f08:	8245a0        	mull	a4, a5, a10
     f0b:	82b580        	mull	a11, a5, a8
     f0e:	156122        	s32i	a2, a1, 84
     f11:	902c70        	addx2	a2, a12, a7
     f14:	057f40        	extui	a7, a4, 31, 1
     f17:	b295a0        	mulsh	a9, a5, a10
     f1a:	b25580        	mulsh	a5, a5, a8
     f1d:	824d80        	mull	a4, a13, a8
     f20:	a169           	s32i.n	a6, a1, 40
     f22:	05cfb0        	extui	a12, a11, 31, 1
     f25:	b26d80        	mulsh	a6, a13, a8
     f28:	232a           	add.n	a2, a3, a2
     f2a:	9035c0        	addx2	a3, a5, a12
     f2d:	055f40        	extui	a5, a4, 31, 1
     f30:	126122        	s32i	a2, a1, 72
     f33:	902970        	addx2	a2, a9, a7
     f36:	905650        	addx2	a5, a6, a5
     f39:	222162        	l32i	a6, a1, 136
     f3c:	b27da0        	mulsh	a7, a13, a10
     f3f:	82bda0        	mull	a11, a13, a10
     f42:	1e21d2        	l32i	a13, a1, 120
     f45:	0698           	l32i.n	a9, a6, 0
     f47:	c02250        	sub	a2, a2, a5
     f4a:	0d88           	l32i.n	a8, a13, 0
     f4c:	055fb0        	extui	a5, a11, 31, 1
     f4f:	5129           	s32i.n	a2, a1, 20
     f51:	902750        	addx2	a2, a7, a5
     f54:	82c890        	mull	a12, a8, a9
     f57:	232a           	add.n	a2, a3, a2
     f59:	1638           	l32i.n	a3, a6, 4
     f5b:	e129           	s32i.n	a2, a1, 56
     f5d:	052fc0        	extui	a2, a12, 31, 1
     f60:	1dc8           	l32i.n	a12, a13, 4
     f62:	b24890        	mulsh	a4, a8, a9
     f65:	827830        	mull	a7, a8, a3
     f68:	902420        	addx2	a2, a4, a2
     f6b:	b28830        	mulsh	a8, a8, a3
     f6e:	824c30        	mull	a4, a12, a3
     f71:	05af70        	extui	a10, a7, 31, 1
     f74:	9058a0        	addx2	a5, a8, a10
     f77:	058f40        	extui	a8, a4, 31, 1
     f7a:	1f2142        	l32i	a4, a1, 124
     f7d:	b23c30        	mulsh	a3, a12, a3
     f80:	41b8           	l32i.n	a11, a1, 16
     f82:	827c90        	mull	a7, a12, a9
     f85:	b2ac90        	mulsh	a10, a12, a9
     f88:	1498           	l32i.n	a9, a4, 4
     f8a:	903380        	addx2	a3, a3, a8
     f8d:	c08230        	sub	a8, a2, a3
     f90:	052f70        	extui	a2, a7, 31, 1
     f93:	902a20        	addx2	a2, a10, a2
     f96:	82cb90        	mull	a12, a11, a9
     f99:	0478           	l32i.n	a7, a4, 0
     f9b:	d1a8           	l32i.n	a10, a1, 52
     f9d:	252a           	add.n	a2, a5, a2
     f9f:	b25b90        	mulsh	a5, a11, a9
     fa2:	053fc0        	extui	a3, a12, 31, 1
     fa5:	116122        	s32i	a2, a1, 68
     fa8:	902530        	addx2	a2, a5, a3
     fab:	1a38           	l32i.n	a3, a10, 4
     fad:	82cb70        	mull	a12, a11, a7
     fb0:	b2bb70        	mulsh	a11, a11, a7
     fb3:	05afc0        	extui	a10, a12, 31, 1
     fb6:	825370        	mull	a5, a3, a7
     fb9:	90aba0        	addx2	a10, a11, a10
     fbc:	b2b370        	mulsh	a11, a3, a7
     fbf:	827390        	mull	a7, a3, a9
     fc2:	b23390        	mulsh	a3, a3, a9
     fc5:	055f50        	extui	a5, a5, 31, 1
     fc8:	057f70        	extui	a7, a7, 31, 1
     fcb:	903370        	addx2	a3, a3, a7
     fce:	905b50        	addx2	a5, a11, a5
     fd1:	c03a30        	sub	a3, a10, a3
     fd4:	225a           	add.n	a2, a2, a5
     fd6:	04ad           	mov.n	a10, a4
     fd8:	106122        	s32i	a2, a1, 64
     fdb:	4139           	s32i.n	a3, a1, 16
     fdd:	1921c2        	l32i	a12, a1, 100
     fe0:	1b2192        	l32i	a9, a1, 108
     fe3:	1a2142        	l32i	a4, a1, 104
     fe6:	a1b8           	l32i.n	a11, a1, 40
     fe8:	b128           	l32i.n	a2, a1, 44
     fea:	c158           	l32i.n	a5, a1, 48
     fec:	1c2132        	l32i	a3, a1, 112
     fef:	0017c6        	j	1052 <FFT8N+0x3c6>

00000ff2 <FFT8N+0x366>:
     ff2:	d128           	l32i.n	a2, a1, 52
     ff4:	8158           	l32i.n	a5, a1, 32
     ff6:	1921c2        	l32i	a12, a1, 100
     ff9:	1228           	l32i.n	a2, a2, 4
     ffb:	106122        	s32i	a2, a1, 64
     ffe:	1528           	l32i.n	a2, a5, 4
    1000:	f129           	s32i.n	a2, a1, 60
    1002:	b128           	l32i.n	a2, a1, 44
    1004:	1a2142        	l32i	a4, a1, 104
    1007:	0538           	l32i.n	a3, a5, 0
    1009:	12b8           	l32i.n	a11, a2, 4
    100b:	1261b2        	s32i	a11, a1, 72
    100e:	a1b8           	l32i.n	a11, a1, 40
    1010:	0c68           	l32i.n	a6, a12, 0
    1012:	0488           	l32i.n	a8, a4, 0
    1014:	0bd8           	l32i.n	a13, a11, 0
    1016:	51d9           	s32i.n	a13, a1, 20
    1018:	1e21d2        	l32i	a13, a1, 120
    101b:	1498           	l32i.n	a9, a4, 4
    101d:	02a8           	l32i.n	a10, a2, 0
    101f:	1be8           	l32i.n	a14, a11, 4
    1021:	1df8           	l32i.n	a15, a13, 4
    1023:	7139           	s32i.n	a3, a1, 28
    1025:	8159           	s32i.n	a5, a1, 32
    1027:	166162        	s32i	a6, a1, 88
    102a:	6189           	s32i.n	a8, a1, 24
    102c:	146192        	s32i	a9, a1, 80
    102f:	1561a2        	s32i	a10, a1, 84
    1032:	e1e9           	s32i.n	a14, a1, 56
    1034:	1161f2        	s32i	a15, a1, 68
    1037:	0d88           	l32i.n	a8, a13, 0
    1039:	222162        	l32i	a6, a1, 136
    103c:	2121f2        	l32i	a15, a1, 132
    103f:	2021e2        	l32i	a14, a1, 128
    1042:	1c2132        	l32i	a3, a1, 112
    1045:	c158           	l32i.n	a5, a1, 48
    1047:	1b2192        	l32i	a9, a1, 108
    104a:	1f21a2        	l32i	a10, a1, 124
    104d:	1c78           	l32i.n	a7, a12, 4
    104f:	136172        	s32i	a7, a1, 76
    1052:	262172        	l32i	a7, a1, 152
    1055:	dd8b           	addi.n	a13, a13, 8
    1057:	bb8b           	addi.n	a11, a11, 8
    1059:	770b           	addi.n	a7, a7, -1
    105b:	266172        	s32i	a7, a1, 152
    105e:	8178           	l32i.n	a7, a1, 32
    1060:	1e61d2        	s32i	a13, a1, 120
    1063:	2f21d2        	l32i	a13, a1, 188
    1066:	a1b9           	s32i.n	a11, a1, 40
    1068:	cc8b           	addi.n	a12, a12, 8
    106a:	d1b8           	l32i.n	a11, a1, 52
    106c:	228b           	addi.n	a2, a2, 8
    106e:	448b           	addi.n	a4, a4, 8
    1070:	1961c2        	s32i	a12, a1, 100
    1073:	2521c2        	l32i	a12, a1, 148
    1076:	b129           	s32i.n	a2, a1, 44
    1078:	278b           	addi.n	a2, a7, 8
    107a:	1a6142        	s32i	a4, a1, 104
    107d:	142142        	l32i	a4, a1, 80
    1080:	8129           	s32i.n	a2, a1, 32
    1082:	2b8b           	addi.n	a2, a11, 8
    1084:	55da           	add.n	a5, a5, a13
    1086:	d129           	s32i.n	a2, a1, 52
    1088:	2c8b           	addi.n	a2, a12, 8
    108a:	66da           	add.n	a6, a6, a13
    108c:	c159           	s32i.n	a5, a1, 48
    108e:	9158           	l32i.n	a5, a1, 36
    1090:	256122        	s32i	a2, a1, 148
    1093:	241b           	addi.n	a2, a4, 1
    1095:	226162        	s32i	a6, a1, 136
    1098:	7168           	l32i.n	a6, a1, 28
    109a:	5178           	l32i.n	a7, a1, 20
    109c:	212120        	srai	a2, a2, 1
    109f:	33da           	add.n	a3, a3, a13
    10a1:	99da           	add.n	a9, a9, a13
    10a3:	b25a           	add.n	a11, a2, a5
    10a5:	c02520        	sub	a2, a5, a2
    10a8:	1c6132        	s32i	a3, a1, 112
    10ab:	371b           	addi.n	a3, a7, 1
    10ad:	1b6192        	s32i	a9, a1, 108
    10b0:	9129           	s32i.n	a2, a1, 36
    10b2:	261b           	addi.n	a2, a6, 1
    10b4:	162192        	l32i	a9, a1, 88
    10b7:	eeda           	add.n	a14, a14, a13
    10b9:	212120        	srai	a2, a2, 1
    10bc:	213130        	srai	a3, a3, 1
    10bf:	523a           	add.n	a5, a2, a3
    10c1:	2061e2        	s32i	a14, a1, 128
    10c4:	ffda           	add.n	a15, a15, a13
    10c6:	aada           	add.n	a10, a10, a13
    10c8:	c02230        	sub	a2, a2, a3
    10cb:	41d8           	l32i.n	a13, a1, 16
    10cd:	1521e2        	l32i	a14, a1, 84
    10d0:	1f61a2        	s32i	a10, a1, 124
    10d3:	7129           	s32i.n	a2, a1, 28
    10d5:	291b           	addi.n	a2, a9, 1
    10d7:	a81b           	addi.n	a10, a8, 1
    10d9:	2131a0        	srai	a3, a10, 1
    10dc:	212120        	srai	a2, a2, 1
    10df:	6168           	l32i.n	a6, a1, 24
    10e1:	c23a           	add.n	a12, a2, a3
    10e3:	c07230        	sub	a7, a2, a3
    10e6:	2d1b           	addi.n	a2, a13, 1
    10e8:	3e1b           	addi.n	a3, a14, 1
    10ea:	212120        	srai	a2, a2, 1
    10ed:	213130        	srai	a3, a3, 1
    10f0:	1d21a2        	l32i	a10, a1, 116
    10f3:	2161f2        	s32i	a15, a1, 132
    10f6:	f23a           	add.n	a15, a2, a3
    10f8:	c0e230        	sub	a14, a2, a3
    10fb:	261b           	addi.n	a2, a6, 1
    10fd:	212120        	srai	a2, a2, 1
    1100:	2181f0        	srai	a8, a15, 1
    1103:	5129           	s32i.n	a2, a1, 20
    1105:	22aa           	add.n	a2, a2, a10
    1107:	381b           	addi.n	a3, a8, 1
    1109:	212120        	srai	a2, a2, 1
    110c:	21c1c0        	srai	a12, a12, 1
    110f:	219130        	srai	a9, a3, 1
    1112:	3c1b           	addi.n	a3, a12, 1
    1114:	221b           	addi.n	a2, a2, 1
    1116:	215150        	srai	a5, a5, 1
    1119:	21d130        	srai	a13, a3, 1
    111c:	21f120        	srai	a15, a2, 1
    111f:	251b           	addi.n	a2, a5, 1
    1121:	212120        	srai	a2, a2, 1
    1124:	69da           	add.n	a6, a9, a13
    1126:	156192        	s32i	a9, a1, 84
    1129:	172182        	l32i	a8, a1, 92
    112c:	132192        	l32i	a9, a1, 76
    112f:	1121c2        	l32i	a12, a1, 68
    1132:	32fa           	add.n	a3, a2, a15
    1134:	1661d2        	s32i	a13, a1, 88
    1137:	61f9           	s32i.n	a15, a1, 24
    1139:	4129           	s32i.n	a2, a1, 16
    113b:	263a           	add.n	a2, a6, a3
    113d:	1221f2        	l32i	a15, a1, 72
    1140:	1021d2        	l32i	a13, a1, 64
    1143:	336132        	s32i	a3, a1, 204
    1146:	3c1b           	addi.n	a3, a12, 1
    1148:	0829           	s32i.n	a2, a8, 0
    114a:	291b           	addi.n	a2, a9, 1
    114c:	212120        	srai	a2, a2, 1
    114f:	213130        	srai	a3, a3, 1
    1152:	923a           	add.n	a9, a2, a3
    1154:	4f1b           	addi.n	a4, a15, 1
    1156:	c02230        	sub	a2, a2, a3
    1159:	3d1b           	addi.n	a3, a13, 1
    115b:	146162        	s32i	a6, a1, 80
    115e:	216130        	srai	a6, a3, 1
    1161:	215140        	srai	a5, a4, 1
    1164:	c03650        	sub	a3, a6, a5
    1167:	832a           	add.n	a8, a3, a2
    1169:	21c180        	srai	a12, a8, 1
    116c:	c04320        	sub	a4, a3, a2
    116f:	3c1b           	addi.n	a3, a12, 1
    1171:	c0fe70        	sub	a15, a14, a7
    1174:	21d130        	srai	a13, a3, 1
    1177:	2131f0        	srai	a3, a15, 1
    117a:	331b           	addi.n	a3, a3, 1
    117c:	fbc1c1        	l32r	a12, 80 (5a82799a <_end+0x5a824742>)
    117f:	213130        	srai	a3, a3, 1
    1182:	126132        	s32i	a3, a1, 72
    1185:	33da           	add.n	a3, a3, a13
    1187:	8223c0        	mull	a2, a3, a12
    118a:	b283c0        	mulsh	a8, a3, a12
    118d:	1361d2        	s32i	a13, a1, 76
    1190:	052f20        	extui	a2, a2, 31, 1
    1193:	de7a           	add.n	a13, a14, a7
    1195:	908820        	addx2	a8, a8, a2
    1198:	2121d0        	srai	a2, a13, 1
    119b:	221b           	addi.n	a2, a2, 1
    119d:	21f140        	srai	a15, a4, 1
    11a0:	21e120        	srai	a14, a2, 1
    11a3:	2f1b           	addi.n	a2, a15, 1
    11a5:	212120        	srai	a2, a2, 1
    11a8:	106122        	s32i	a2, a1, 64
    11ab:	c022e0        	sub	a2, a2, a14
    11ae:	8272c0        	mull	a7, a2, a12
    11b1:	b242c0        	mulsh	a4, a2, a12
    11b4:	f1c8           	l32i.n	a12, a1, 60
    11b6:	e1f8           	l32i.n	a15, a1, 56
    11b8:	057f70        	extui	a7, a7, 31, 1
    11bb:	dc1b           	addi.n	a13, a12, 1
    11bd:	2f1b           	addi.n	a2, a15, 1
    11bf:	1161e2        	s32i	a14, a1, 68
    11c2:	90e470        	addx2	a14, a4, a7
    11c5:	765a           	add.n	a7, a6, a5
    11c7:	2151d0        	srai	a5, a13, 1
    11ca:	216120        	srai	a6, a2, 1
    11cd:	214170        	srai	a4, a7, 1
    11d0:	756a           	add.n	a7, a5, a6
    11d2:	219190        	srai	a9, a9, 1
    11d5:	2131b0        	srai	a3, a11, 1
    11d8:	21b170        	srai	a11, a7, 1
    11db:	441b           	addi.n	a4, a4, 1
    11dd:	991b           	addi.n	a9, a9, 1
    11df:	c31b           	addi.n	a12, a3, 1
    11e1:	bb1b           	addi.n	a11, a11, 1
    11e3:	214140        	srai	a4, a4, 1
    11e6:	219190        	srai	a9, a9, 1
    11e9:	21c1c0        	srai	a12, a12, 1
    11ec:	21b1b0        	srai	a11, a11, 1
    11ef:	f49a           	add.n	a15, a4, a9
    11f1:	dbca           	add.n	a13, a11, a12
    11f3:	e1f9           	s32i.n	a15, a1, 56
    11f5:	3fda           	add.n	a3, a15, a13
    11f7:	182172        	l32i	a7, a1, 96
    11fa:	51f8           	l32i.n	a15, a1, 20
    11fc:	c05560        	sub	a5, a5, a6
    11ff:	0739           	s32i.n	a3, a7, 0
    1201:	c03af0        	sub	a3, a10, a15
    1204:	9178           	l32i.n	a7, a1, 36
    1206:	71f8           	l32i.n	a15, a1, 28
    1208:	216130        	srai	a6, a3, 1
    120b:	661b           	addi.n	a6, a6, 1
    120d:	215150        	srai	a5, a5, 1
    1210:	212160        	srai	a2, a6, 1
    1213:	2161f0        	srai	a6, a15, 1
    1216:	21a170        	srai	a10, a7, 1
    1219:	551b           	addi.n	a5, a5, 1
    121b:	761b           	addi.n	a7, a6, 1
    121d:	f1d9           	s32i.n	a13, a1, 60
    121f:	da1b           	addi.n	a13, a10, 1
    1221:	215150        	srai	a5, a5, 1
    1224:	21d1d0        	srai	a13, a13, 1
    1227:	217170        	srai	a7, a7, 1
    122a:	c0ad70        	sub	a10, a13, a7
    122d:	652a           	add.n	a6, a5, a2
    122f:	316182        	s32i	a8, a1, 196
    1232:	3261e2        	s32i	a14, a1, 200
    1235:	3eaa           	add.n	a3, a14, a10
    1237:	1d61a2        	s32i	a10, a1, 116
    123a:	e86a           	add.n	a14, a8, a6
    123c:	5169           	s32i.n	a6, a1, 20
    123e:	2e21a2        	l32i	a10, a1, 184
    1241:	2421f2        	l32i	a15, a1, 144
    1244:	4168           	l32i.n	a6, a1, 16
    1246:	6188           	l32i.n	a8, a1, 24
    1248:	0ae9           	s32i.n	a14, a10, 0
    124a:	77da           	add.n	a7, a7, a13
    124c:	c09940        	sub	a9, a9, a4
    124f:	0f39           	s32i.n	a3, a15, 0
    1251:	c06860        	sub	a6, a8, a6
    1254:	1321d2        	l32i	a13, a1, 76
    1257:	1221f2        	l32i	a15, a1, 72
    125a:	4199           	s32i.n	a9, a1, 16
    125c:	9169           	s32i.n	a6, a1, 36
    125e:	c09690        	sub	a9, a6, a9
    1261:	c06250        	sub	a6, a2, a5
    1264:	fb8751        	l32r	a5, 80 (5a82799a <_end+0x5a824742>)
    1267:	2d21e2        	l32i	a14, a1, 180
    126a:	c03df0        	sub	a3, a13, a15
    126d:	c04cb0        	sub	a4, a12, a11
    1270:	1621b2        	l32i	a11, a1, 88
    1273:	1521c2        	l32i	a12, a1, 84
    1276:	1121d2        	l32i	a13, a1, 68
    1279:	1021f2        	l32i	a15, a1, 64
    127c:	828350        	mull	a8, a3, a5
    127f:	0e99           	s32i.n	a9, a14, 0
    1281:	2c2192        	l32i	a9, a1, 176
    1284:	c02cb0        	sub	a2, a12, a11
    1287:	05cf80        	extui	a12, a8, 31, 1
    128a:	8dfa           	add.n	a8, a13, a15
    128c:	fb7ed1        	l32r	a13, 84 (a57d8666 <_end+0xa57d540e>)
    128f:	c0b420        	sub	a11, a4, a2
    1292:	09b9           	s32i.n	a11, a9, 0
    1294:	b2b350        	mulsh	a11, a3, a5
    1297:	82f8d0        	mull	a15, a8, a13
    129a:	90bbc0        	addx2	a11, a11, a12
    129d:	b2c8d0        	mulsh	a12, a8, a13
    12a0:	05dff0        	extui	a13, a15, 31, 1
    12a3:	90ccd0        	addx2	a12, a12, a13
    12a6:	7179           	s32i.n	a7, a1, 28
    12a8:	dc7a           	add.n	a13, a12, a7
    12aa:	272172        	l32i	a7, a1, 156
    12ad:	232152        	l32i	a5, a1, 140
    12b0:	3b6a           	add.n	a3, a11, a6
    12b2:	6169           	s32i.n	a6, a1, 24
    12b4:	0739           	s32i.n	a3, a7, 0
    12b6:	05d9           	s32i.n	a13, a5, 0
    12b8:	f168           	l32i.n	a6, a1, 60
    12ba:	e188           	l32i.n	a8, a1, 56
    12bc:	1421d2        	l32i	a13, a1, 80
    12bf:	3321f2        	l32i	a15, a1, 204
    12c2:	c03680        	sub	a3, a6, a8
    12c5:	2b2182        	l32i	a8, a1, 172
    12c8:	c05fd0        	sub	a5, a15, a13
    12cb:	322162        	l32i	a6, a1, 200
    12ce:	1d21d2        	l32i	a13, a1, 116
    12d1:	0859           	s32i.n	a5, a8, 0
    12d3:	3721f2        	l32i	a15, a1, 220
    12d6:	c0dd60        	sub	a13, a13, a6
    12d9:	312152        	l32i	a5, a1, 196
    12dc:	5168           	l32i.n	a6, a1, 20
    12de:	0f39           	s32i.n	a3, a15, 0
    12e0:	c03650        	sub	a3, a6, a5
    12e3:	292162        	l32i	a6, a1, 164
    12e6:	2a2152        	l32i	a5, a1, 168
    12e9:	0639           	s32i.n	a3, a6, 0
    12eb:	05d9           	s32i.n	a13, a5, 0
    12ed:	324a           	add.n	a3, a2, a4
    12ef:	4148           	l32i.n	a4, a1, 16
    12f1:	91d8           	l32i.n	a13, a1, 36
    12f3:	44da           	add.n	a4, a4, a13
    12f5:	2821d2        	l32i	a13, a1, 160
    12f8:	0d49           	s32i.n	a4, a13, 0
    12fa:	342142        	l32i	a4, a1, 208
    12fd:	0439           	s32i.n	a3, a4, 0
    12ff:	7138           	l32i.n	a3, a1, 28
    1301:	c023c0        	sub	a2, a3, a12
    1304:	61c8           	l32i.n	a12, a1, 24
    1306:	c03cb0        	sub	a3, a12, a11
    1309:	3521c2        	l32i	a12, a1, 212
    130c:	3621b2        	l32i	a11, a1, 216
    130f:	0c39           	s32i.n	a3, a12, 0
    1311:	0b29           	s32i.n	a2, a11, 0
    1313:	302122        	l32i	a2, a1, 192
    1316:	172132        	l32i	a3, a1, 92
    1319:	aa2a           	add.n	a10, a10, a2
    131b:	332a           	add.n	a3, a3, a2
    131d:	176132        	s32i	a3, a1, 92
    1320:	182132        	l32i	a3, a1, 96
    1323:	2e61a2        	s32i	a10, a1, 184
    1326:	ee2a           	add.n	a14, a14, a2
    1328:	2421a2        	l32i	a10, a1, 144
    132b:	2d61e2        	s32i	a14, a1, 180
    132e:	2321e2        	l32i	a14, a1, 140
    1331:	332a           	add.n	a3, a3, a2
    1333:	772a           	add.n	a7, a7, a2
    1335:	186132        	s32i	a3, a1, 96
    1338:	3a2a           	add.n	a3, a10, a2
    133a:	276172        	s32i	a7, a1, 156
    133d:	262172        	l32i	a7, a1, 152
    1340:	246132        	s32i	a3, a1, 144
    1343:	992a           	add.n	a9, a9, a2
    1345:	dd2a           	add.n	a13, a13, a2
    1347:	552a           	add.n	a5, a5, a2
    1349:	662a           	add.n	a6, a6, a2
    134b:	882a           	add.n	a8, a8, a2
    134d:	3e2a           	add.n	a3, a14, a2
    134f:	2c6192        	s32i	a9, a1, 176
    1352:	bb2a           	add.n	a11, a11, a2
    1354:	cc2a           	add.n	a12, a12, a2
    1356:	442a           	add.n	a4, a4, a2
    1358:	ff2a           	add.n	a15, a15, a2
    135a:	2861d2        	s32i	a13, a1, 160
    135d:	2a6152        	s32i	a5, a1, 168
    1360:	296162        	s32i	a6, a1, 164
    1363:	2b6182        	s32i	a8, a1, 172
    1366:	236132        	s32i	a3, a1, 140

00001369 <FFT8N+0x6dd>:
    1369:	f01d           	retw.n

0000136b <FFT8N+0x6df>:
	...

0000136c <fix_fft10>:
    136c:	01c136        	entry	a1, 224
    136f:	00a452        	movi	a5, 0x400
    1372:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    1375:	600204        	ae_lq32f.i	aeq0, a2, 0
    1378:	d5e2bd224f 	{ ae_lq32f.i	aeq1, a2, 16; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
    137d:	01d142        	addmi	a4, a1, 0x100
    1380:	d4e3c9044e 	{ addi	a4, a4, -112; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1385:	fe3442039e 	{ addi	a9, a3, 32; ae_roundsq32asym	aeq2, aeq2 }
    138a:	04ed           	mov.n	a14, a4
    138c:	40c282        	addi	a8, a2, 64
    138f:	626e04        	ae_sq32f.iu	aeq2, a14, 0
    1392:	608944        	ae_lq32f.i	aeq2, a9, 16
    1395:	60c304        	ae_lq32f.i	aeq3, a3, 0
    1398:	d7e3c4036e 	{ addi	a6, a3, 64; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    139d:	600344        	ae_lq32f.i	aeq0, a3, 16
    13a0:	ff3c7a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_roundsq32asym	aeq3, aeq3 }
    13a5:	608804        	ae_lq32f.i	aeq2, a8, 0
    13a8:	631174        	ae_sq56s.i	aeq1, a1, 56
    13ab:	604884        	ae_lq32f.i	aeq1, a8, -32
    13ae:	78c1f2        	addi	a15, a1, 120
    13b1:	630124        	ae_sq56s.i	aeq0, a1, 16
    13b4:	632164        	ae_sq56s.i	aeq2, a1, 48
    13b7:	608604        	ae_lq32f.i	aeq2, a6, 0
    13ba:	631f94        	ae_sq56s.i	aeq1, a15, -56
    13bd:	604904        	ae_lq32f.i	aeq1, a9, 0
    13c0:	6008c4        	ae_lq32f.i	aeq0, a8, -16
    13c3:	20c272        	addi	a7, a2, 32
    13c6:	d5e2ba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
    13cb:	631144        	ae_sq56s.i	aeq1, a1, 32
    13ce:	fe347da13f 	{ ae_lq56.i	aeq1, a1, 24; ae_roundsq32asym	aeq2, aeq2 }
    13d3:	d4e3b9fe1f 	{ ae_sq32f.iu	aeq3, a14, 4; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    13d8:	61c124        	ae_lq56.i	aeq3, a1, 16
    13db:	fc2479ee1f 	{ ae_sq32f.iu	aeq2, a14, 4; ae_roundsq32asym	aeq0, aeq0 }
    13e0:	d7e3fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    13e5:	d7e2bda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    13ea:	fc2c79ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_roundsq32asym	aeq0, aeq1 }
    13ef:	614154        	ae_lq56.i	aeq1, a1, 40
    13f2:	d4e3f9ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    13f7:	fc3c7def9f 	{ ae_lq56.i	aeq3, a15, -56; ae_roundsq32asym	aeq0, aeq3 }
    13fc:	fc3479ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_roundsq32asym	aeq0, aeq2 }
    1401:	d7e3fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1406:	d7e2b9ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    140b:	fd2c4641be 	{ addi	a11, a1, 100; ae_roundsq32asym	aeq1, aeq1 }
    1410:	176162        	s32i	a6, a1, 92
    1413:	fd3c79de1f 	{ ae_sq32f.iu	aeq1, a14, 4; ae_roundsq32asym	aeq1, aeq3 }
    1418:	ff3446016e 	{ addi	a6, a1, 96; ae_roundsq32asym	aeq3, aeq2 }
    141d:	fb1551        	l32r	a5, 74 (18c <fix_fft5_stage>)
    1420:	625e14        	ae_sq32f.iu	aeq1, a14, 4
    1423:	04cd           	mov.n	a12, a4
    1425:	06ad           	mov.n	a10, a6
    1427:	560fa4        	ae_sp24x2s.i	aep0, a15, -48
    142a:	166182        	s32i	a8, a1, 88
    142d:	156192        	s32i	a9, a1, 84
    1430:	627e14        	ae_sq32f.iu	aeq3, a14, 4
    1433:	0005e0        	callx8	a5
    1436:	78c1a2        	addi	a10, a1, 120
    1439:	604724        	ae_lq32f.i	aeq1, a7, 8
    143c:	540aa4        	ae_lp24x2.i	aep0, a10, -48
    143f:	d4e3f1518e 	{ l32i	a8, a1, 84; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1444:	059d           	mov.n	a9, a5
    1446:	045d           	mov.n	a5, a4
    1448:	fd2c7d082f 	{ ae_lq32f.i	aeq0, a8, 8; ae_roundsq32asym	aeq1, aeq1 }
    144d:	d4e2bd432f 	{ ae_lq32f.i	aeq2, a3, 8; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1452:	625404        	ae_sq32f.iu	aeq1, a4, 0
    1455:	604264        	ae_lq32f.i	aeq1, a2, 24
    1458:	1621e2        	l32i	a14, a1, 88
    145b:	632124        	ae_sq56s.i	aeq2, a1, 16
    145e:	631174        	ae_sq56s.i	aeq1, a1, 56
    1461:	604364        	ae_lq32f.i	aeq1, a3, 24
    1464:	631164        	ae_sq56s.i	aeq1, a1, 48
    1467:	614124        	ae_lq56.i	aeq1, a1, 16
    146a:	1721f2        	l32i	a15, a1, 92
    146d:	60c224        	ae_lq32f.i	aeq3, a2, 8
    1470:	d4e3ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1475:	d7e3fd2e2f 	{ ae_lq32f.i	aeq1, a14, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    147a:	608764        	ae_lq32f.i	aeq2, a7, 24
    147d:	ff3c7a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq3, aeq3 }
    1482:	614134        	ae_lq56.i	aeq1, a1, 24
    1485:	632154        	ae_sq56s.i	aeq2, a1, 40
    1488:	fc2c7a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_roundsq32asym	aeq0, aeq1 }
    148d:	604f24        	ae_lq32f.i	aeq1, a15, 8
    1490:	624414        	ae_sq32f.iu	aeq0, a4, 4
    1493:	631134        	ae_sq56s.i	aeq1, a1, 24
    1496:	614154        	ae_lq56.i	aeq1, a1, 40
    1499:	d4e3fd486f 	{ ae_lq32f.i	aeq2, a8, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    149e:	d7e2b9f41f 	{ ae_sq32f.iu	aeq3, a4, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    14a3:	61c124        	ae_lq56.i	aeq3, a1, 16
    14a6:	fc3c7de17f 	{ ae_lq56.i	aeq3, a1, 56; ae_roundsq32asym	aeq0, aeq3 }
    14ab:	fc2c79c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_roundsq32asym	aeq0, aeq1 }
    14b0:	d7e3fda16f 	{ ae_lq56.i	aeq1, a1, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    14b5:	d4e3f9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    14ba:	fc347dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_roundsq32asym	aeq0, aeq2 }
    14bf:	d7e2b9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    14c4:	fc3c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq0, aeq3 }
    14c9:	d7e3f9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    14ce:	fd2c53a55f 	{ or	a10, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    14d3:	01d1b2        	addmi	a11, a1, 0x100
    14d6:	fe3479d41f 	{ ae_sq32f.iu	aeq1, a4, 4; ae_roundsq32asym	aeq2, aeq2 }
    14db:	ff3c494bbe 	{ addi	a11, a11, -108; ae_roundsq32asym	aeq3, aeq3 }
    14e0:	626414        	ae_sq32f.iu	aeq2, a4, 4
    14e3:	05cd           	mov.n	a12, a5
    14e5:	627414        	ae_sq32f.iu	aeq3, a4, 4
    14e8:	0009e0        	callx8	a9
    14eb:	601604        	ae_lq32f.iu	aeq0, a6, 0
    14ee:	60d504        	ae_lq32f.iu	aeq3, a5, 0
    14f1:	fae63d361f 	{ ae_lq32f.iu	aeq1, a6, 4; ae_addq56	aeq2, aeq0, aeq3 }
    14f6:	f8a6fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_subq56	aeq0, aeq0, aeq3 }
    14fb:	609514        	ae_lq32f.iu	aeq2, a5, 4
    14fe:	f8ea3f07ef 	{ ae_trunca32q48	a7, aeq0; ae_addq56	aeq0, aeq1, aeq2 }
    1503:	f9aafde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_subq56	aeq1, aeq1, aeq2 }
    1508:	36b404        	ae_trunca32q48	a4, aeq3
    150b:	630124        	ae_sq56s.i	aeq0, a1, 16
    150e:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    1511:	601514        	ae_lq32f.iu	aeq0, a5, 4
    1514:	618124        	ae_lq56.i	aeq2, a1, 16
    1517:	f97a3f19ef 	{ ae_trunca32q48	a9, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    151c:	f83aff28ef 	{ ae_trunca32q48	a8, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
    1521:	631124        	ae_sq56s.i	aeq1, a1, 16
    1524:	609614        	ae_lq32f.iu	aeq2, a6, 4
    1527:	605514        	ae_lq32f.iu	aeq1, a5, 4
    152a:	61c124        	ae_lq56.i	aeq3, a1, 16
    152d:	f8763f0bef 	{ ae_trunca32q48	a11, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
    1532:	f936ff3aef 	{ ae_trunca32q48	a10, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
    1537:	630124        	ae_sq56s.i	aeq0, a1, 16
    153a:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    153d:	601514        	ae_lq32f.iu	aeq0, a5, 4
    1540:	618124        	ae_lq56.i	aeq2, a1, 16
    1543:	f97a3f1def 	{ ae_trunca32q48	a13, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    1548:	f83aff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
    154d:	631124        	ae_sq56s.i	aeq1, a1, 16
    1550:	609614        	ae_lq32f.iu	aeq2, a6, 4
    1553:	605514        	ae_lq32f.iu	aeq1, a5, 4
    1556:	61c124        	ae_lq56.i	aeq3, a1, 16
    1559:	f8763f0fef 	{ ae_trunca32q48	a15, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
    155e:	f936ff3eef 	{ ae_trunca32q48	a14, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
    1563:	630124        	ae_sq56s.i	aeq0, a1, 16
    1566:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    1569:	601514        	ae_lq32f.iu	aeq0, a5, 4
    156c:	0249           	s32i.n	a4, a2, 0
    156e:	a279           	s32i.n	a7, a2, 40
    1570:	0389           	s32i.n	a8, a3, 0
    1572:	f97a3f18ef 	{ ae_trunca32q48	a8, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    1577:	f83afdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq3, aeq0 }
    157c:	631124        	ae_sq56s.i	aeq1, a1, 16
    157f:	36a704        	ae_trunca32q48	a7, aeq2
    1582:	609614        	ae_lq32f.iu	aeq2, a6, 4
    1585:	61c124        	ae_lq56.i	aeq3, a1, 16
    1588:	a399           	s32i.n	a9, a3, 40
    158a:	36b904        	ae_trunca32q48	a9, aeq3
    158d:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    1590:	42a9           	s32i.n	a10, a2, 16
    1592:	fc147f0aef 	{ ae_trunca32q48	a10, aeq0; ae_movq56	aeq0, aeq2 }
    1597:	605514        	ae_lq32f.iu	aeq1, a5, 4
    159a:	fb763a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_addq56	aeq3, aeq2, aeq1 }
    159f:	f926fd551f 	{ ae_lq32f.iu	aeq2, a5, 4; ae_subq56	aeq1, aeq0, aeq1 }
    15a4:	610124        	ae_lq56.i	aeq0, a1, 16
    15a7:	e2b9           	s32i.n	a11, a2, 56
    15a9:	43c9           	s32i.n	a12, a3, 16
    15ab:	36bb04        	ae_trunca32q48	a11, aeq3
    15ae:	f9e23f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq1, aeq0, aeq2 }
    15b3:	f8a2fd761f 	{ ae_lq32f.iu	aeq3, a6, 4; ae_subq56	aeq0, aeq0, aeq2 }
    15b8:	369604        	ae_trunca32q48	a6, aeq1
    15bb:	605514        	ae_lq32f.iu	aeq1, a5, 4
    15be:	fa7e14e3df 	{ s32i.n	a13, a3, 56; ae_addq56	aeq2, aeq3, aeq1 }
    15c3:	82e9           	s32i.n	a14, a2, 32
    15c5:	1262f2        	s32i	a15, a2, 72
    15c8:	f93eff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq1, aeq3, aeq1 }
    15cd:	36ae04        	ae_trunca32q48	a14, aeq2
    15d0:	369f04        	ae_trunca32q48	a15, aeq1
    15d3:	8379           	s32i.n	a7, a3, 32
    15d5:	126382        	s32i	a8, a3, 72
    15d8:	c299           	s32i.n	a9, a2, 48
    15da:	22a9           	s32i.n	a10, a2, 8
    15dc:	c3b9           	s32i.n	a11, a3, 48
    15de:	23c9           	s32i.n	a12, a3, 8
    15e0:	106262        	s32i	a6, a2, 64
    15e3:	62d9           	s32i.n	a13, a2, 24
    15e5:	1063e2        	s32i	a14, a3, 64
    15e8:	63f9           	s32i.n	a15, a3, 24
    15ea:	f01d           	retw.n

000015ec <fix_fft10+0x280>:
    15ec:	00000000                                ....

000015f0 <FFT16N>:
    15f0:	02c136        	entry	a1, 0x160
    15f3:	3d6172        	s32i	a7, a1, 244
    15f6:	067d           	mov.n	a7, a6
    15f8:	5921e2        	l32i	a14, a1, 0x164
    15fb:	11f5f0        	slli	a15, a5, 1
    15fe:	036d           	mov.n	a6, a3
    1600:	3c6142        	s32i	a4, a1, 240
    1603:	396122        	s32i	a2, a1, 228
    1606:	386192        	s32i	a9, a1, 224
    1609:	3061e2        	s32i	a14, a1, 192
    160c:	2e6152        	s32i	a5, a1, 184
    160f:	2f61f2        	s32i	a15, a1, 188
    1612:	2217a6        	blti	a7, 1, 1638 <FFT16N+0x48>
    1615:	2f2132        	l32i	a3, a1, 188
    1618:	2e21f2        	l32i	a15, a1, 184
    161b:	302152        	l32i	a5, a1, 192
    161e:	1143e0        	slli	a4, a3, 2
    1621:	21cb           	addi.n	a2, a1, 12
    1623:	113fd0        	slli	a3, a15, 3
    1626:	c04540        	sub	a4, a5, a4
    1629:	0b8776        	loop	a7, 1638 <FFT16N+0x48>
    162c:	603434        	ae_lq32f.xu	aeq0, a4, a3
    162f:	624214        	ae_sq32f.iu	aeq0, a2, 4
    1632:	60c414        	ae_lq32f.i	aeq3, a4, 4
    1635:	627214        	ae_sq32f.iu	aeq3, a2, 4

00001638 <FFT16N+0x48>:
    1638:	fa9621        	l32r	a2, 90 (18f4 <fix_fft16>)
    163b:	14c1b2        	addi	a11, a1, 20
    163e:	10c1a2        	addi	a10, a1, 16
    1641:	4661b2        	s32i	a11, a1, 0x118
    1644:	3161a2        	s32i	a10, a1, 196
    1647:	0002e0        	callx8	a2
    164a:	2e2132        	l32i	a3, a1, 184
    164d:	3d2142        	l32i	a4, a1, 244
    1650:	392152        	l32i	a5, a1, 228
    1653:	d12340        	mul16s	a2, a3, a4
    1656:	1122e0        	slli	a2, a2, 2
    1659:	c05520        	sub	a5, a5, a2
    165c:	c02620        	sub	a2, a6, a2
    165f:	3a6122        	s32i	a2, a1, 232
    1662:	d12430        	mul16s	a2, a4, a3
    1665:	3b6152        	s32i	a5, a1, 236
    1668:	1d17a6        	blti	a7, 1, 1689 <FFT16N+0x99>
    166b:	312132        	l32i	a3, a1, 196
    166e:	3a2152        	l32i	a5, a1, 232
    1671:	3b2162        	l32i	a6, a1, 236
    1674:	1142e0        	slli	a4, a2, 2
    1677:	601304        	ae_lq32f.iu	aeq0, a3, 0
    167a:	0b8776        	loop	a7, 1689 <FFT16N+0x99>
    167d:	605314        	ae_lq32f.iu	aeq1, a3, 4
    1680:	62c644        	ae_sq32f.xu	aeq0, a6, a4
    1683:	62d544        	ae_sq32f.xu	aeq1, a5, a4
    1686:	601314        	ae_lq32f.iu	aeq0, a3, 4
    1689:	2e2132        	l32i	a3, a1, 184
    168c:	2e21f2        	l32i	a15, a1, 184
    168f:	2f21d2        	l32i	a13, a1, 188
    1692:	0223e6        	bgei	a3, 2, 1698 <FFT16N+0xa8>
    1695:	009646        	j	18f2 <FFT16N+0x302>
    1698:	5821a2        	l32i	a10, a1, 0x160
    169b:	382132        	l32i	a3, a1, 224
    169e:	904ff0        	addx2	a4, a15, a15
    16a1:	641b           	addi.n	a6, a4, 1
    16a3:	5a2192        	l32i	a9, a1, 0x168
    16a6:	20c132        	addi	a3, a1, 32
    16a9:	ed1b           	addi.n	a14, a13, 1
    16ab:	302152        	l32i	a5, a1, 192
    16ae:	11c2e0        	slli	a12, a2, 2
    16b1:	3f6132        	s32i	a3, a1, 252
    16b4:	823ea0        	mull	a3, a14, a10
    16b7:	118fc0        	slli	a8, a15, 4
    16ba:	d12af0        	mul16s	a2, a10, a15
    16bd:	8266a0        	mull	a6, a6, a10
    16c0:	3c21f2        	l32i	a15, a1, 240
    16c3:	b04450        	addx8	a4, a4, a5
    16c6:	c03390        	sub	a3, a3, a9
    16c9:	1b0c           	movi.n	a11, 1
    16cb:	496182        	s32i	a8, a1, 0x124
    16ce:	885a           	add.n	a8, a8, a5
    16d0:	416122        	s32i	a2, a1, 0x104
    16d3:	1122d0        	slli	a2, a2, 3
    16d6:	c0e690        	sub	a14, a6, a9
    16d9:	58cb           	addi.n	a5, a8, 12
    16db:	44cb           	addi.n	a4, a4, 12
    16dd:	c08b90        	sub	a8, a11, a9
    16e0:	11dae0        	slli	a13, a10, 2
    16e3:	486122        	s32i	a2, a1, 0x120
    16e6:	a033f0        	addx4	a3, a3, a15
    16e9:	a02ef0        	addx4	a2, a14, a15
    16ec:	356152        	s32i	a5, a1, 212
    16ef:	346142        	s32i	a4, a1, 208
    16f2:	426182        	s32i	a8, a1, 0x108
    16f5:	4061d2        	s32i	a13, a1, 0x100
    16f8:	4461a2        	s32i	a10, a1, 0x110
    16fb:	456192        	s32i	a9, a1, 0x114
    16fe:	336132        	s32i	a3, a1, 204
    1701:	326122        	s32i	a2, a1, 200
    1704:	3e6172        	s32i	a7, a1, 248
    1707:	4361c2        	s32i	a12, a1, 0x10c

0000170a <FFT16N+0x11a>:
    170a:	2f2132        	l32i	a3, a1, 188
    170d:	4421d2        	l32i	a13, a1, 0x110
    1710:	4121f2        	l32i	a15, a1, 0x104
    1713:	302122        	l32i	a2, a1, 192
    1716:	909b30        	addx2	a9, a11, a3
    1719:	82abd0        	mull	a10, a11, a13
    171c:	452132        	l32i	a3, a1, 0x114
    171f:	422152        	l32i	a5, a1, 0x108
    1722:	3c2162        	l32i	a6, a1, 240
    1725:	aafa           	add.n	a10, a10, a15
    1727:	b08b20        	addx8	a8, a11, a2
    172a:	c04a30        	sub	a4, a10, a3
    172d:	a5aa           	add.n	a10, a5, a10
    172f:	08e8           	l32i.n	a14, a8, 0
    1731:	a0aa60        	addx4	a10, a10, a6
    1734:	4761b2        	s32i	a11, a1, 0x11c
    1737:	a0b460        	addx4	a11, a4, a6
    173a:	1888           	l32i.n	a8, a8, 4
    173c:	a09920        	addx4	a9, a9, a2
    173f:	5189           	s32i.n	a8, a1, 20
    1741:	0988           	l32i.n	a8, a9, 0
    1743:	0aa8           	l32i.n	a10, a10, 0
    1745:	1998           	l32i.n	a9, a9, 4
    1747:	0bb8           	l32i.n	a11, a11, 0
    1749:	41e9           	s32i.n	a14, a1, 16
    174b:	b2f8a0        	mulsh	a15, a8, a10
    174e:	b2c9b0        	mulsh	a12, a9, a11
    1751:	82d9b0        	mull	a13, a9, a11
    1754:	b2e8b0        	mulsh	a14, a8, a11
    1757:	82b8b0        	mull	a11, a8, a11
    175a:	8288a0        	mull	a8, a8, a10
    175d:	8269a0        	mull	a6, a9, a10
    1760:	058f80        	extui	a8, a8, 31, 1
    1763:	b299a0        	mulsh	a9, a9, a10
    1766:	056f60        	extui	a6, a6, 31, 1
    1769:	908f80        	addx2	a8, a15, a8
    176c:	05ffd0        	extui	a15, a13, 31, 1
    176f:	05bfb0        	extui	a11, a11, 31, 1
    1772:	906960        	addx2	a6, a9, a6
    1775:	909eb0        	addx2	a9, a14, a11
    1778:	90acf0        	addx2	a10, a12, a15
    177b:	88aa           	add.n	a8, a8, a10
    177d:	c06960        	sub	a6, a9, a6
    1780:	6169           	s32i.n	a6, a1, 24
    1782:	7189           	s32i.n	a8, a1, 28
    1784:	0237e6        	bgei	a7, 3, 178a <FFT16N+0x19a>
    1787:	003e86        	j	1885 <FFT16N+0x295>
    178a:	3e2122        	l32i	a2, a1, 248
    178d:	332182        	l32i	a8, a1, 204
    1790:	3f2192        	l32i	a9, a1, 252
    1793:	620b           	addi.n	a6, a2, -1
    1795:	3521a2        	l32i	a10, a1, 212
    1798:	3221b2        	l32i	a11, a1, 200
    179b:	3421c2        	l32i	a12, a1, 208
    179e:	416160        	srli	a6, a6, 1
    17a1:	e08676        	loop	a6, 1885 <FFT16N+0x295>
    17a4:	0a68           	l32i.n	a6, a10, 0
    17a6:	18f8           	l32i.n	a15, a8, 4
    17a8:	08d8           	l32i.n	a13, a8, 0
    17aa:	fccae2        	addi	a14, a10, -4
    17ad:	b246f0        	mulsh	a4, a6, a15
    17b0:	0c58           	l32i.n	a5, a12, 0
    17b2:	1b28           	l32i.n	a2, a11, 4
    17b4:	376142        	s32i	a4, a1, 220
    17b7:	8246f0        	mull	a4, a6, a15
    17ba:	0ee8           	l32i.n	a14, a14, 0
    17bc:	4c6142        	s32i	a4, a1, 0x130
    17bf:	b246d0        	mulsh	a4, a6, a13
    17c2:	8266d0        	mull	a6, a6, a13
    17c5:	4b6162        	s32i	a6, a1, 0x12c
    17c8:	b26520        	mulsh	a6, a5, a2
    17cb:	4d6162        	s32i	a6, a1, 0x134
    17ce:	b26ed0        	mulsh	a6, a14, a13
    17d1:	fccc32        	addi	a3, a12, -4
    17d4:	396162        	s32i	a6, a1, 228
    17d7:	826ed0        	mull	a6, a14, a13
    17da:	4f6162        	s32i	a6, a1, 0x13c
    17dd:	b2def0        	mulsh	a13, a14, a15
    17e0:	826ef0        	mull	a6, a14, a15
    17e3:	0b78           	l32i.n	a7, a11, 0
    17e5:	0338           	l32i.n	a3, a3, 0
    17e7:	4c21e2        	l32i	a14, a1, 0x130
    17ea:	3721f2        	l32i	a15, a1, 220
    17ed:	3861d2        	s32i	a13, a1, 224
    17f0:	82d520        	mull	a13, a5, a2
    17f3:	366142        	s32i	a4, a1, 216
    17f6:	4e6162        	s32i	a6, a1, 0x138
    17f9:	4a61d2        	s32i	a13, a1, 0x128
    17fc:	b24570        	mulsh	a4, a5, a7
    17ff:	825570        	mull	a5, a5, a7
    1802:	b26370        	mulsh	a6, a3, a7
    1805:	827370        	mull	a7, a3, a7
    1808:	b2d320        	mulsh	a13, a3, a2
    180b:	822320        	mull	a2, a3, a2
    180e:	053fe0        	extui	a3, a14, 31, 1
    1811:	903f30        	addx2	a3, a15, a3
    1814:	4b21f2        	l32i	a15, a1, 0x12c
    1817:	055f50        	extui	a5, a5, 31, 1
    181a:	904450        	addx2	a4, a4, a5
    181d:	05eff0        	extui	a14, a15, 31, 1
    1820:	3621f2        	l32i	a15, a1, 216
    1823:	052f20        	extui	a2, a2, 31, 1
    1826:	902d20        	addx2	a2, a13, a2
    1829:	90efe0        	addx2	a14, a15, a14
    182c:	4a21f2        	l32i	a15, a1, 0x128
    182f:	3761e2        	s32i	a14, a1, 220
    1832:	4d21e2        	l32i	a14, a1, 0x134
    1835:	05fff0        	extui	a15, a15, 31, 1
    1838:	057f70        	extui	a7, a7, 31, 1
    183b:	90eef0        	addx2	a14, a14, a15
    183e:	3661e2        	s32i	a14, a1, 216
    1841:	4f21e2        	l32i	a14, a1, 0x13c
    1844:	3921f2        	l32i	a15, a1, 228
    1847:	3721d2        	l32i	a13, a1, 220
    184a:	055fe0        	extui	a5, a14, 31, 1
    184d:	905f50        	addx2	a5, a15, a5
    1850:	4e21f2        	l32i	a15, a1, 0x138
    1853:	906670        	addx2	a6, a6, a7
    1856:	482172        	l32i	a7, a1, 0x120
    1859:	05eff0        	extui	a14, a15, 31, 1
    185c:	3821f2        	l32i	a15, a1, 224
    185f:	c03530        	sub	a3, a5, a3
    1862:	224a           	add.n	a2, a2, a4
    1864:	90efe0        	addx2	a14, a15, a14
    1867:	4921f2        	l32i	a15, a1, 0x124
    186a:	5eda           	add.n	a5, a14, a13
    186c:	bb7a           	add.n	a11, a11, a7
    186e:	aafa           	add.n	a10, a10, a15
    1870:	ccfa           	add.n	a12, a12, a15
    1872:	3621f2        	l32i	a15, a1, 216
    1875:	887a           	add.n	a8, a8, a7
    1877:	0939           	s32i.n	a3, a9, 0
    1879:	c066f0        	sub	a6, a6, a15
    187c:	1959           	s32i.n	a5, a9, 4
    187e:	2969           	s32i.n	a6, a9, 8
    1880:	3929           	s32i.n	a2, a9, 12
    1882:	10c992        	addi	a9, a9, 16

00001885 <FFT16N+0x295>:
    1885:	3121a2        	l32i	a10, a1, 196
    1888:	4621b2        	l32i	a11, a1, 0x118
    188b:	fa0121        	l32r	a2, 90 (18f4 <fix_fft16>)
    188e:	0002e0        	callx8	a2
    1891:	3e2172        	l32i	a7, a1, 248
    1894:	4721b2        	l32i	a11, a1, 0x11c
    1897:	4321c2        	l32i	a12, a1, 0x10c
    189a:	2617a6        	blti	a7, 1, 18c4 <FFT16N+0x2d4>
    189d:	3d2122        	l32i	a2, a1, 244
    18a0:	312182        	l32i	a8, a1, 196
    18a3:	3a2132        	l32i	a3, a1, 232
    18a6:	3b21f2        	l32i	a15, a1, 236
    18a9:	822b20        	mull	a2, a11, a2
    18ac:	601804        	ae_lq32f.iu	aeq0, a8, 0
    18af:	a09230        	addx4	a9, a2, a3
    18b2:	a0a2f0        	addx4	a10, a2, a15
    18b5:	0b8776        	loop	a7, 18c4 <FFT16N+0x2d4>
    18b8:	605814        	ae_lq32f.iu	aeq1, a8, 4
    18bb:	62cac4        	ae_sq32f.xu	aeq0, a10, a12
    18be:	62d9c4        	ae_sq32f.xu	aeq1, a9, a12
    18c1:	601814        	ae_lq32f.iu	aeq0, a8, 4
    18c4:	402122        	l32i	a2, a1, 0x100
    18c7:	332132        	l32i	a3, a1, 204
    18ca:	3221c2        	l32i	a12, a1, 200
    18cd:	3421d2        	l32i	a13, a1, 208
    18d0:	3521e2        	l32i	a14, a1, 212
    18d3:	332a           	add.n	a3, a3, a2
    18d5:	2e21f2        	l32i	a15, a1, 184
    18d8:	336132        	s32i	a3, a1, 204
    18db:	3c2a           	add.n	a3, a12, a2
    18dd:	2d8b           	addi.n	a2, a13, 8
    18df:	bb1b           	addi.n	a11, a11, 1
    18e1:	346122        	s32i	a2, a1, 208
    18e4:	2e8b           	addi.n	a2, a14, 8
    18e6:	326132        	s32i	a3, a1, 200
    18e9:	356122        	s32i	a2, a1, 212
    18ec:	021bf7        	beq	a11, a15, 18f2 <FFT16N+0x302>
    18ef:	ff85c6        	j	170a <FFT16N+0x11a>

000018f2 <FFT16N+0x302>:
    18f2:	f01d           	retw.n

000018f4 <fix_fft16>:
    18f4:	02c136        	entry	a1, 0x160
    18f7:	070c           	movi.n	a7, 0
    18f9:	026d           	mov.n	a6, a2
    18fb:	603674        	ae_lq32f.xu	aeq0, a6, a7
    18fe:	052c           	movi.n	a5, 32
    1900:	034d           	mov.n	a4, a3
    1902:	60b654        	ae_lq32f.xu	aeq2, a6, a5
    1905:	35a174        	ae_sraiq56	aeq2, aeq2, 5
    1908:	fe347b011f 	{ ae_sraiq56	aeq0, aeq0, 5; ae_roundsq32asym	aeq2, aeq2 }
    190d:	fd247c647f 	{ ae_lq32f.xu	aeq3, a4, a7; ae_roundsq32asym	aeq1, aeq0 }
    1912:	353174        	ae_sraiq56	aeq0, aeq3, 5
    1915:	fc247c665f 	{ ae_lq32f.xu	aeq3, a6, a5; ae_roundsq32asym	aeq0, aeq0 }
    191a:	78c1e2        	addi	a14, a1, 120
    191d:	632ec4        	ae_sq56s.i	aeq2, a14, -32
    1920:	60b654        	ae_lq32f.xu	aeq2, a6, a5
    1923:	35f174        	ae_sraiq56	aeq3, aeq3, 5
    1926:	ff3c7a0e5f 	{ ae_sq56s.i	aeq0, a14, 40; ae_roundsq32asym	aeq3, aeq3 }
    192b:	352174        	ae_sraiq56	aeq0, aeq2, 5
    192e:	fe247f113f 	{ ae_movq56	aeq0, aeq1; ae_roundsq32asym	aeq2, aeq0 }
    1933:	f8a6cfa88f 	{ movi	a8, -88; ae_subq56	aeq0, aeq0, aeq3 }
    1938:	f9ee3a0e1f 	{ ae_sq56s.i	aeq0, a14, 8; ae_addq56	aeq1, aeq1, aeq3 }
    193d:	610ec4        	ae_lq56.i	aeq0, a14, -32
    1940:	fbe23a113f 	{ ae_sq56s.i	aeq1, a1, 24; ae_addq56	aeq3, aeq0, aeq2 }
    1945:	fba2fa317f 	{ ae_sq56s.i	aeq3, a1, 56; ae_subq56	aeq3, aeq0, aeq2 }
    194a:	603454        	ae_lq32f.xu	aeq0, a4, a5
    194d:	354174        	ae_sraiq56	aeq1, aeq0, 5
    1950:	fd2c7c445f 	{ ae_lq32f.xu	aeq2, a4, a5; ae_roundsq32asym	aeq1, aeq1 }
    1955:	631144        	ae_sq56s.i	aeq1, a1, 32
    1958:	356174        	ae_sraiq56	aeq1, aeq2, 5
    195b:	fd2c7d8e5f 	{ ae_lq56.i	aeq0, a14, 40; ae_roundsq32asym	aeq1, aeq1 }
    1960:	0189c4        	ae_addq56	aeq2, aeq0, aeq1
    1963:	014dc4        	ae_subq56	aeq1, aeq0, aeq1
    1966:	011fc4        	ae_subq56	aeq0, aeq1, aeq3
    1969:	f8ee3f0fef 	{ ae_trunca32q48	a15, aeq0; ae_addq56	aeq0, aeq1, aeq3 }
    196e:	01d172        	addmi	a7, a1, 0x100
    1971:	632784        	ae_sq56s.i	aeq2, a7, -64
    1974:	60b684        	ae_lq32f.xu	aeq2, a6, a8
    1977:	368904        	ae_trunca32q48	a9, aeq0
    197a:	60f654        	ae_lq32f.xu	aeq3, a6, a5
    197d:	4f6192        	s32i	a9, a1, 0x13c
    1980:	632164        	ae_sq56s.i	aeq2, a1, 48
    1983:	633e74        	ae_sq56s.i	aeq3, a14, 56
    1986:	607654        	ae_lq32f.xu	aeq1, a6, a5
    1989:	618134        	ae_lq56.i	aeq2, a1, 24
    198c:	61c174        	ae_lq56.i	aeq3, a1, 56
    198f:	f8f63c465f 	{ ae_lq32f.xu	aeq2, a6, a5; ae_addq56	aeq0, aeq2, aeq3 }
    1994:	60f684        	ae_lq32f.xu	aeq3, a6, a8
    1997:	631e04        	ae_sq56s.i	aeq1, a14, 0
    199a:	607654        	ae_lq32f.xu	aeq1, a6, a5
    199d:	632124        	ae_sq56s.i	aeq2, a1, 16
    19a0:	60b654        	ae_lq32f.xu	aeq2, a6, a5
    19a3:	633eb4        	ae_sq56s.i	aeq3, a14, -40
    19a6:	60f654        	ae_lq32f.xu	aeq3, a6, a5
    19a9:	631e24        	ae_sq56s.i	aeq1, a14, 16
    19ac:	607684        	ae_lq32f.xu	aeq1, a6, a8
    19af:	01d1a2        	addmi	a10, a1, 0x100
    19b2:	632e34        	ae_sq56s.i	aeq2, a14, 24
    19b5:	60b654        	ae_lq32f.xu	aeq2, a6, a5
    19b8:	4c6132        	s32i	a3, a1, 0x130
    19bb:	368304        	ae_trunca32q48	a3, aeq0
    19be:	351174        	ae_sraiq56	aeq0, aeq1, 5
    19c1:	fc247b215f 	{ ae_sraiq56	aeq1, aeq2, 5; ae_roundsq32asym	aeq0, aeq0 }
    19c6:	fd2c480aae 	{ addi	a10, a10, -128; ae_roundsq32asym	aeq1, aeq1 }
    19cb:	633a74        	ae_sq56s.i	aeq3, a10, 56
    19ce:	60f654        	ae_lq32f.xu	aeq3, a6, a5
    19d1:	631794        	ae_sq56s.i	aeq1, a7, -56
    19d4:	357174        	ae_sraiq56	aeq1, aeq3, 5
    19d7:	fe2c7c265f 	{ ae_lq32f.xu	aeq1, a6, a5; ae_roundsq32asym	aeq2, aeq1 }
    19dc:	fbe23b115f 	{ ae_sraiq56	aeq1, aeq1, 5; ae_addq56	aeq3, aeq0, aeq2 }
    19e1:	f8a2fc445f 	{ ae_lq32f.xu	aeq2, a4, a5; ae_subq56	aeq0, aeq0, aeq2 }
    19e6:	633ec4        	ae_sq56s.i	aeq3, a14, -32
    19e9:	fc2c7a0e5f 	{ ae_sq56s.i	aeq0, a14, 40; ae_roundsq32asym	aeq0, aeq1 }
    19ee:	632e94        	ae_sq56s.i	aeq2, a14, -56
    19f1:	618794        	ae_lq56.i	aeq2, a7, -56
    19f4:	f932fc648f 	{ ae_lq32f.xu	aeq3, a4, a8; ae_subq56	aeq1, aeq2, aeq0 }
    19f9:	f8723c445f 	{ ae_lq32f.xu	aeq2, a4, a5; ae_addq56	aeq0, aeq2, aeq0 }
    19fe:	633ef4        	ae_sq56s.i	aeq3, a14, -8
    1a01:	60f454        	ae_lq32f.xu	aeq3, a4, a5
    1a04:	632154        	ae_sq56s.i	aeq2, a1, 40
    1a07:	60b454        	ae_lq32f.xu	aeq2, a4, a5
    1a0a:	633ea4        	ae_sq56s.i	aeq3, a14, -48
    1a0d:	6327e4        	ae_sq56s.i	aeq2, a7, -16
    1a10:	60b484        	ae_lq32f.xu	aeq2, a4, a8
    1a13:	61cec4        	ae_lq56.i	aeq3, a14, -32
    1a16:	f93afa1e6f 	{ ae_sq56s.i	aeq1, a14, 48; ae_subq56	aeq1, aeq3, aeq0 }
    1a1b:	f87a3c645f 	{ ae_lq32f.xu	aeq3, a4, a5; ae_addq56	aeq0, aeq3, aeq0 }
    1a20:	369604        	ae_trunca32q48	a6, aeq1
    1a23:	607454        	ae_lq32f.xu	aeq1, a4, a5
    1a26:	6327d4        	ae_sq56s.i	aeq2, a7, -24
    1a29:	60b454        	ae_lq32f.xu	aeq2, a4, a5
    1a2c:	633ee4        	ae_sq56s.i	aeq3, a14, -16
    1a2f:	60f484        	ae_lq32f.xu	aeq3, a4, a8
    1a32:	368904        	ae_trunca32q48	a9, aeq0
    1a35:	353174        	ae_sraiq56	aeq0, aeq3, 5
    1a38:	fc247a17bf 	{ ae_sq56s.i	aeq1, a7, -40; ae_roundsq32asym	aeq0, aeq0 }
    1a3d:	607454        	ae_lq32f.xu	aeq1, a4, a5
    1a40:	6307a4        	ae_sq56s.i	aeq0, a7, -48
    1a43:	351174        	ae_sraiq56	aeq0, aeq1, 5
    1a46:	fc247c245f 	{ ae_lq32f.xu	aeq1, a4, a5; ae_roundsq32asym	aeq0, aeq0 }
    1a4b:	6327c4        	ae_sq56s.i	aeq2, a7, -32
    1a4e:	60b454        	ae_lq32f.xu	aeq2, a4, a5
    1a51:	35e174        	ae_sraiq56	aeq3, aeq2, 5
    1a54:	ff3c7b115f 	{ ae_sraiq56	aeq1, aeq1, 5; ae_roundsq32asym	aeq3, aeq3 }
    1a59:	01b8c4        	ae_addq56	aeq2, aeq3, aeq0
    1a5c:	f83afa2ecf 	{ ae_sq56s.i	aeq2, a14, -32; ae_subq56	aeq0, aeq3, aeq0 }
    1a61:	fd2c7dc7af 	{ ae_lq56.i	aeq2, a7, -48; ae_roundsq32asym	aeq1, aeq1 }
    1a66:	fb763a0e4f 	{ ae_sq56s.i	aeq0, a14, 32; ae_addq56	aeq3, aeq2, aeq1 }
    1a6b:	f836fdce6f 	{ ae_lq56.i	aeq2, a14, 48; ae_subq56	aeq0, aeq2, aeq1 }
    1a70:	f9a2fa37ff 	{ ae_sq56s.i	aeq3, a7, -8; ae_subq56	aeq1, aeq0, aeq2 }
    1a75:	f8e23f14ef 	{ ae_trunca32q48	a4, aeq1; ae_addq56	aeq0, aeq0, aeq2 }
    1a7a:	614e54        	ae_lq56.i	aeq1, a14, 40
    1a7d:	618e44        	ae_lq56.i	aeq2, a14, 32
    1a80:	f9aafdcecf 	{ ae_lq56.i	aeq2, a14, -32; ae_subq56	aeq1, aeq1, aeq2 }
    1a85:	369a04        	ae_trunca32q48	a10, aeq1
    1a88:	614e94        	ae_lq56.i	aeq1, a14, -56
    1a8b:	f8fa3a0edf 	{ ae_sq56s.i	aeq0, a14, -24; ae_addq56	aeq0, aeq3, aeq2 }
    1a90:	618134        	ae_lq56.i	aeq2, a1, 24
    1a93:	61c174        	ae_lq56.i	aeq3, a1, 56
    1a96:	fab6fb115f 	{ ae_sraiq56	aeq1, aeq1, 5; ae_subq56	aeq2, aeq2, aeq3 }
    1a9b:	fe2c7f2cef 	{ ae_trunca32q48	a12, aeq2; ae_roundsq32asym	aeq2, aeq1 }
    1aa0:	614ea4        	ae_lq56.i	aeq1, a14, -48
    1aa3:	368504        	ae_trunca32q48	a5, aeq0
    1aa6:	351174        	ae_sraiq56	aeq0, aeq1, 5
    1aa9:	614ef4        	ae_lq56.i	aeq1, a14, -8
    1aac:	61c144        	ae_lq56.i	aeq3, a1, 32
    1aaf:	fbf63a0eaf 	{ ae_sq56s.i	aeq0, a14, -48; ae_addq56	aeq3, aeq2, aeq3 }
    1ab4:	351174        	ae_sraiq56	aeq0, aeq1, 5
    1ab7:	630ef4        	ae_sq56s.i	aeq0, a14, -8
    1aba:	610784        	ae_lq56.i	aeq0, a7, -64
    1abd:	014bc4        	ae_addq56	aeq1, aeq0, aeq3
    1ac0:	f8a6fdeedf 	{ ae_lq56.i	aeq3, a14, -24; ae_subq56	aeq0, aeq0, aeq3 }
    1ac5:	36bd04        	ae_trunca32q48	a13, aeq3
    1ac8:	631134        	ae_sq56s.i	aeq1, a1, 24
    1acb:	614ea4        	ae_lq56.i	aeq1, a14, -48
    1ace:	fd2c7deeff 	{ ae_lq56.i	aeq3, a14, -8; ae_roundsq32asym	aeq1, aeq1 }
    1ad3:	fc3c7a0e9f 	{ ae_sq56s.i	aeq0, a14, -56; ae_roundsq32asym	aeq0, aeq3 }
    1ad8:	61c134        	ae_lq56.i	aeq3, a1, 24
    1adb:	2a61c2        	s32i	a12, a1, 168
    1ade:	fb663f3bef 	{ ae_trunca32q48	a11, aeq3; ae_addq56	aeq3, aeq0, aeq1 }
    1ae3:	f826fda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_subq56	aeq0, aeq0, aeq1 }
    1ae8:	f936fdce7f 	{ ae_lq56.i	aeq2, a14, 56; ae_subq56	aeq1, aeq2, aeq1 }
    1aed:	633ea4        	ae_sq56s.i	aeq3, a14, -48
    1af0:	630134        	ae_sq56s.i	aeq0, a1, 24
    1af3:	61ce94        	ae_lq56.i	aeq3, a14, -56
    1af6:	78c1c2        	addi	a12, a1, 120
    1af9:	352174        	ae_sraiq56	aeq0, aeq2, 5
    1afc:	36be04        	ae_trunca32q48	a14, aeq3
    1aff:	61c124        	ae_lq56.i	aeq3, a1, 16
    1b02:	630124        	ae_sq56s.i	aeq0, a1, 16
    1b05:	610c14        	ae_lq56.i	aeq0, a12, 8
    1b08:	fa26fb31df 	{ ae_sraiq56	aeq3, aeq3, 5; ae_subq56	aeq2, aeq0, aeq1 }
    1b0d:	4b61f2        	s32i	a15, a1, 0x12c
    1b10:	ff3c7f2fef 	{ ae_trunca32q48	a15, aeq2; ae_roundsq32asym	aeq3, aeq3 }
    1b15:	f9663dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_addq56	aeq1, aeq0, aeq1 }
    1b1a:	fe347a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_roundsq32asym	aeq2, aeq2 }
    1b1f:	326162        	s32i	a6, a1, 200
    1b22:	f8b6ff16ef 	{ ae_trunca32q48	a6, aeq1; ae_subq56	aeq0, aeq2, aeq3 }
    1b27:	614134        	ae_lq56.i	aeq1, a1, 24
    1b2a:	01dcc4        	ae_subq56	aeq3, aeq1, aeq0
    1b2d:	f86a3a3c1f 	{ ae_sq56s.i	aeq3, a12, 8; ae_addq56	aeq0, aeq1, aeq0 }
    1b32:	6147e4        	ae_lq56.i	aeq1, a7, -16
    1b35:	61c144        	ae_lq56.i	aeq3, a1, 32
    1b38:	630124        	ae_sq56s.i	aeq0, a1, 16
    1b3b:	f9f63b111f 	{ ae_sraiq56	aeq0, aeq1, 5; ae_addq56	aeq1, aeq2, aeq3 }
    1b40:	61c164        	ae_lq56.i	aeq3, a1, 48
    1b43:	ff247b319f 	{ ae_sraiq56	aeq2, aeq3, 5; ae_roundsq32asym	aeq3, aeq0 }
    1b48:	fe347a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq2, aeq2 }
    1b4d:	614154        	ae_lq56.i	aeq1, a1, 40
    1b50:	355174        	ae_sraiq56	aeq1, aeq1, 5
    1b53:	fc2c7a217f 	{ ae_sq56s.i	aeq2, a1, 56; ae_roundsq32asym	aeq0, aeq1 }
    1b58:	618c04        	ae_lq56.i	aeq2, a12, 0
    1b5b:	35a174        	ae_sraiq56	aeq2, aeq2, 5
    1b5e:	fe347dac1f 	{ ae_lq56.i	aeq1, a12, 8; ae_roundsq32asym	aeq2, aeq2 }
    1b63:	369804        	ae_trunca32q48	a8, aeq1
    1b66:	614124        	ae_lq56.i	aeq1, a1, 16
    1b69:	4961a2        	s32i	a10, a1, 0x124
    1b6c:	369a04        	ae_trunca32q48	a10, aeq1
    1b6f:	fa7a3a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_addq56	aeq2, aeq3, aeq0 }
    1b74:	614ca4        	ae_lq56.i	aeq1, a12, -48
    1b77:	fbea3a3c9f 	{ ae_sq56s.i	aeq3, a12, -56; ae_addq56	aeq3, aeq1, aeq2 }
    1b7c:	630c04        	ae_sq56s.i	aeq0, a12, 0
    1b7f:	633124        	ae_sq56s.i	aeq3, a1, 16
    1b82:	610134        	ae_lq56.i	aeq0, a1, 24
    1b85:	61c174        	ae_lq56.i	aeq3, a1, 56
    1b88:	f87a3de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_addq56	aeq0, aeq3, aeq0 }
    1b8d:	4861a2        	s32i	a10, a1, 0x120
    1b90:	36ba04        	ae_trunca32q48	a10, aeq3
    1b93:	61c144        	ae_lq56.i	aeq3, a1, 32
    1b96:	fbe63a016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_addq56	aeq3, aeq0, aeq3 }
    1b9b:	466162        	s32i	a6, a1, 0x118
    1b9e:	f8aaff36ef 	{ ae_trunca32q48	a6, aeq3; ae_subq56	aeq0, aeq1, aeq2 }
    1ba3:	618134        	ae_lq56.i	aeq2, a1, 24
    1ba6:	61c174        	ae_lq56.i	aeq3, a1, 56
    1ba9:	f9bafdcc0f 	{ ae_lq56.i	aeq2, a12, 0; ae_subq56	aeq1, aeq3, aeq2 }
    1bae:	3061d2        	s32i	a13, a1, 192
    1bb1:	368d04        	ae_trunca32q48	a13, aeq0
    1bb4:	61cc94        	ae_lq56.i	aeq3, a12, -56
    1bb7:	1261d2        	s32i	a13, a1, 72
    1bba:	01d1d2        	addmi	a13, a1, 0x100
    1bbd:	f8bafdc7df 	{ ae_lq56.i	aeq2, a7, -24; ae_subq56	aeq0, aeq3, aeq2 }
    1bc2:	35e174        	ae_sraiq56	aeq3, aeq2, 5
    1bc5:	80cdd2        	addi	a13, a13, -128
    1bc8:	fb2afa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq3, aeq1, aeq0 }
    1bcd:	f86a3dad7f 	{ ae_lq56.i	aeq1, a13, 56; ae_addq56	aeq0, aeq1, aeq0 }
    1bd2:	630124        	ae_sq56s.i	aeq0, a1, 16
    1bd5:	351174        	ae_sraiq56	aeq0, aeq1, 5
    1bd8:	fc247da14f 	{ ae_lq56.i	aeq1, a1, 32; ae_roundsq32asym	aeq0, aeq0 }
    1bdd:	618164        	ae_lq56.i	aeq2, a1, 48
    1be0:	f936fdcc2f 	{ ae_lq56.i	aeq2, a12, 16; ae_subq56	aeq1, aeq2, aeq1 }
    1be5:	4161e2        	s32i	a14, a1, 0x104
    1be8:	36be04        	ae_trunca32q48	a14, aeq3
    1beb:	631144        	ae_sq56s.i	aeq1, a1, 32
    1bee:	356174        	ae_sraiq56	aeq1, aeq2, 5
    1bf1:	6187b4        	ae_lq56.i	aeq2, a7, -40
    1bf4:	61c134        	ae_lq56.i	aeq3, a1, 24
    1bf7:	630c94        	ae_sq56s.i	aeq0, a12, -56
    1bfa:	fe2c7b211f 	{ ae_sraiq56	aeq0, aeq2, 5; ae_roundsq32asym	aeq2, aeq1 }
    1bff:	fd3c7de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq1, aeq3 }
    1c04:	2c61f2        	s32i	a15, a1, 176
    1c07:	fc247f3fef 	{ ae_trunca32q48	a15, aeq3; ae_roundsq32asym	aeq0, aeq0 }
    1c0c:	61ccb4        	ae_lq56.i	aeq3, a12, -40
    1c0f:	f92afa1c0f 	{ ae_sq56s.i	aeq1, a12, 0; ae_subq56	aeq1, aeq1, aeq0 }
    1c14:	630d74        	ae_sq56s.i	aeq0, a13, 56
    1c17:	353174        	ae_sraiq56	aeq0, aeq3, 5
    1c1a:	61cc94        	ae_lq56.i	aeq3, a12, -56
    1c1d:	f8b6fa012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_subq56	aeq0, aeq2, aeq3 }
    1c22:	632164        	ae_sq56s.i	aeq2, a1, 48
    1c25:	618c34        	ae_lq56.i	aeq2, a12, 24
    1c28:	35a174        	ae_sraiq56	aeq2, aeq2, 5
    1c2b:	fa2afa2cff 	{ ae_sq56s.i	aeq2, a12, -8; ae_subq56	aeq2, aeq1, aeq0 }
    1c30:	f86a3a215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_addq56	aeq0, aeq1, aeq0 }
    1c35:	618144        	ae_lq56.i	aeq2, a1, 32
    1c38:	614124        	ae_lq56.i	aeq1, a1, 16
    1c3b:	206182        	s32i	a8, a1, 128
    1c3e:	fd2c7f28ef 	{ ae_trunca32q48	a8, aeq2; ae_roundsq32asym	aeq1, aeq1 }
    1c43:	618cf4        	ae_lq56.i	aeq2, a12, -8
    1c46:	fc347a0cbf 	{ ae_sq56s.i	aeq0, a12, -40; ae_roundsq32asym	aeq0, aeq2 }
    1c4b:	618154        	ae_lq56.i	aeq2, a1, 40
    1c4e:	4761e2        	s32i	a14, a1, 0x11c
    1c51:	fa6a3f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq2, aeq1, aeq0 }
    1c56:	f82afdacbf 	{ ae_lq56.i	aeq1, a12, -40; ae_subq56	aeq0, aeq1, aeq0 }
    1c5b:	2261f2        	s32i	a15, a1, 136
    1c5e:	369f04        	ae_trunca32q48	a15, aeq1
    1c61:	614164        	ae_lq56.i	aeq1, a1, 48
    1c64:	f9ee3decef 	{ ae_lq56.i	aeq3, a12, -16; ae_addq56	aeq1, aeq1, aeq3 }
    1c69:	630144        	ae_sq56s.i	aeq0, a1, 32
    1c6c:	353174        	ae_sraiq56	aeq0, aeq3, 5
    1c6f:	61c7c4        	ae_lq56.i	aeq3, a7, -32
    1c72:	630cb4        	ae_sq56s.i	aeq0, a12, -40
    1c75:	fb763b311f 	{ ae_sraiq56	aeq0, aeq3, 5; ae_addq56	aeq3, aeq2, aeq1 }
    1c7a:	f9aafa316f 	{ ae_sq56s.i	aeq3, a1, 48; ae_subq56	aeq1, aeq1, aeq2 }
    1c7f:	61ccb4        	ae_lq56.i	aeq3, a12, -40
    1c82:	fc3c7a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_roundsq32asym	aeq0, aeq3 }
    1c87:	61c164        	ae_lq56.i	aeq3, a1, 48
    1c8a:	2461e2        	s32i	a14, a1, 144
    1c8d:	36be04        	ae_trunca32q48	a14, aeq3
    1c90:	61c124        	ae_lq56.i	aeq3, a1, 16
    1c93:	ff3c54618f 	{ s32i.n	a8, a1, 24; ae_roundsq32asym	aeq3, aeq3 }
    1c98:	fa3aff18ef 	{ ae_trunca32q48	a8, aeq1; ae_subq56	aeq2, aeq3, aeq0 }
    1c9d:	614144        	ae_lq56.i	aeq1, a1, 32
    1ca0:	f8aafa0cbf 	{ ae_sq56s.i	aeq0, a12, -40; ae_subq56	aeq0, aeq1, aeq2 }
    1ca5:	630164        	ae_sq56s.i	aeq0, a1, 48
    1ca8:	610d74        	ae_lq56.i	aeq0, a13, 56
    1cab:	614c04        	ae_lq56.i	aeq1, a12, 0
    1cae:	f86a3da16f 	{ ae_lq56.i	aeq1, a1, 48; ae_addq56	aeq0, aeq1, aeq0 }
    1cb3:	369d04        	ae_trunca32q48	a13, aeq1
    1cb6:	614144        	ae_lq56.i	aeq1, a1, 32
    1cb9:	f9ea3dccbf 	{ ae_lq56.i	aeq2, a12, -40; ae_addq56	aeq1, aeq1, aeq2 }
    1cbe:	fafa14e1ff 	{ s32i.n	a15, a1, 56; ae_addq56	aeq2, aeq3, aeq2 }
    1cc3:	fbe23f1fef 	{ ae_trunca32q48	a15, aeq1; ae_addq56	aeq3, aeq0, aeq2 }
    1cc8:	4561d2        	s32i	a13, a1, 0x114
    1ccb:	f8a2ff3def 	{ ae_trunca32q48	a13, aeq3; ae_subq56	aeq0, aeq0, aeq2 }
    1cd0:	368704        	ae_trunca32q48	a7, aeq0
    1cd3:	186182        	s32i	a8, a1, 96
    1cd6:	a179           	s32i.n	a7, a1, 40
    1cd8:	8dba           	add.n	a8, a13, a11
    1cda:	057d           	mov.n	a7, a5
    1cdc:	55aa           	add.n	a5, a5, a10
    1cde:	4461f2        	s32i	a15, a1, 0x110
    1ce1:	f96a           	add.n	a15, a9, a6
    1ce3:	406152        	s32i	a5, a1, 0x100
    1ce6:	c58a           	add.n	a12, a5, a8
    1ce8:	5e3a           	add.n	a5, a14, a3
    1cea:	1a6182        	s32i	a8, a1, 104
    1ced:	8f5a           	add.n	a8, a15, a5
    1cef:	4a6142        	s32i	a4, a1, 0x128
    1cf2:	034d           	mov.n	a4, a3
    1cf4:	023d           	mov.n	a3, a2
    1cf6:	0289           	s32i.n	a8, a2, 0
    1cf8:	4c2122        	l32i	a2, a1, 0x130
    1cfb:	c087a0        	sub	a8, a7, a10
    1cfe:	c0a4e0        	sub	a10, a4, a14
    1d01:	c04bd0        	sub	a4, a11, a13
    1d04:	c09690        	sub	a9, a6, a9
    1d07:	02c9           	s32i.n	a12, a2, 0
    1d09:	c07a80        	sub	a7, a10, a8
    1d0c:	c0c5f0        	sub	a12, a5, a15
    1d0f:	c0b490        	sub	a11, a4, a9
    1d12:	2a21d2        	l32i	a13, a1, 168
    1d15:	a1e8           	l32i.n	a14, a1, 40
    1d17:	8379           	s32i.n	a7, a3, 32
    1d19:	82b9           	s32i.n	a11, a2, 32
    1d1b:	1063c2        	s32i	a12, a3, 64
    1d1e:	1a21b2        	l32i	a11, a1, 104
    1d21:	4021c2        	l32i	a12, a1, 0x100
    1d24:	027d           	mov.n	a7, a2
    1d26:	c02de0        	sub	a2, a13, a14
    1d29:	feda           	add.n	a15, a14, a13
    1d2b:	d8aa           	add.n	a13, a8, a10
    1d2d:	a129           	s32i.n	a2, a1, 40
    1d2f:	c02bc0        	sub	a2, a11, a12
    1d32:	694a           	add.n	a6, a9, a4
    1d34:	4361f2        	s32i	a15, a1, 0x10c
    1d37:	106722        	s32i	a2, a7, 64
    1d3a:	1863d2        	s32i	a13, a3, 96
    1d3d:	186762        	s32i	a6, a7, 96
    1d40:	4121e2        	l32i	a14, a1, 0x104
    1d43:	1821f2        	l32i	a15, a1, 96
    1d46:	f8cf71        	l32r	a7, 84 (a57d8666 <_end+0xa57d540e>)
    1d49:	322182        	l32i	a8, a1, 200
    1d4c:	e1a8           	l32i.n	a10, a1, 56
    1d4e:	4421c2        	l32i	a12, a1, 0x110
    1d51:	4e6132        	s32i	a3, a1, 0x138
    1d54:	3fea           	add.n	a3, a15, a14
    1d56:	829870        	mull	a9, a8, a7
    1d59:	c02ef0        	sub	a2, a14, a15
    1d5c:	406132        	s32i	a3, a1, 0x100
    1d5f:	b23870        	mulsh	a3, a8, a7
    1d62:	416122        	s32i	a2, a1, 0x104
    1d65:	052f90        	extui	a2, a9, 31, 1
    1d68:	82ba70        	mull	a11, a10, a7
    1d6b:	902320        	addx2	a2, a3, a2
    1d6e:	b23a70        	mulsh	a3, a10, a7
    1d71:	82dc70        	mull	a13, a12, a7
    1d74:	186122        	s32i	a2, a1, 96
    1d77:	052fb0        	extui	a2, a11, 31, 1
    1d7a:	b24c70        	mulsh	a4, a12, a7
    1d7d:	f8c051        	l32r	a5, 80 (5a82799a <_end+0x5a824742>)
    1d80:	242182        	l32i	a8, a1, 144
    1d83:	902320        	addx2	a2, a3, a2
    1d86:	053fd0        	extui	a3, a13, 31, 1
    1d89:	4521a2        	l32i	a10, a1, 0x114
    1d8c:	4f21e2        	l32i	a14, a1, 0x13c
    1d8f:	462162        	l32i	a6, a1, 0x118
    1d92:	903430        	addx2	a3, a4, a3
    1d95:	432a           	add.n	a4, a3, a2
    1d97:	c02320        	sub	a2, a3, a2
    1d9a:	829850        	mull	a9, a8, a5
    1d9d:	f4ea           	add.n	a15, a4, a14
    1d9f:	c04e40        	sub	a4, a14, a4
    1da2:	726a           	add.n	a7, a2, a6
    1da4:	c02620        	sub	a2, a6, a2
    1da7:	b23850        	mulsh	a3, a8, a5
    1daa:	82ba50        	mull	a11, a10, a5
    1dad:	446142        	s32i	a4, a1, 0x110
    1db0:	466122        	s32i	a2, a1, 0x118
    1db3:	052f90        	extui	a2, a9, 31, 1
    1db6:	b24a50        	mulsh	a4, a10, a5
    1db9:	122162        	l32i	a6, a1, 72
    1dbc:	902320        	addx2	a2, a3, a2
    1dbf:	053fb0        	extui	a3, a11, 31, 1
    1dc2:	6188           	l32i.n	a8, a1, 24
    1dc4:	2c21e2        	l32i	a14, a1, 176
    1dc7:	903430        	addx2	a3, a4, a3
    1dca:	426172        	s32i	a7, a1, 0x108
    1dcd:	c04230        	sub	a4, a2, a3
    1dd0:	4b21c2        	l32i	a12, a1, 0x12c
    1dd3:	232a           	add.n	a2, a3, a2
    1dd5:	827650        	mull	a7, a6, a5
    1dd8:	e1f9           	s32i.n	a15, a1, 56
    1dda:	f2ea           	add.n	a15, a2, a14
    1ddc:	c02e20        	sub	a2, a14, a2
    1ddf:	b23650        	mulsh	a3, a6, a5
    1de2:	829850        	mull	a9, a8, a5
    1de5:	4d6122        	s32i	a2, a1, 0x134
    1de8:	052f70        	extui	a2, a7, 31, 1
    1deb:	2021a2        	l32i	a10, a1, 128
    1dee:	f8aae1        	l32r	a14, 98 (7641af3d <_end+0x76417ce5>)
    1df1:	d4ca           	add.n	a13, a4, a12
    1df3:	c04c40        	sub	a4, a12, a4
    1df6:	f8a771        	l32r	a7, 94 (cf043ab3 <_end+0xcf04085b>)
    1df9:	902320        	addx2	a2, a3, a2
    1dfc:	053f90        	extui	a3, a9, 31, 1
    1dff:	472192        	l32i	a9, a1, 0x11c
    1e02:	246142        	s32i	a4, a1, 144
    1e05:	b24850        	mulsh	a4, a8, a5
    1e08:	826ae0        	mull	a6, a10, a14
    1e0b:	903430        	addx2	a3, a4, a3
    1e0e:	82ba70        	mull	a11, a10, a7
    1e11:	b2ca70        	mulsh	a12, a10, a7
    1e14:	b24ae0        	mulsh	a4, a10, a14
    1e17:	82a9e0        	mull	a10, a9, a14
    1e1a:	4561d2        	s32i	a13, a1, 0x114
    1e1d:	4b61f2        	s32i	a15, a1, 0x12c
    1e20:	b259e0        	mulsh	a5, a9, a14
    1e23:	f23a           	add.n	a15, a2, a3
    1e25:	c0d230        	sub	a13, a2, a3
    1e28:	053f60        	extui	a3, a6, 31, 1
    1e2b:	052fb0        	extui	a2, a11, 31, 1
    1e2e:	908430        	addx2	a8, a4, a3
    1e31:	054fa0        	extui	a4, a10, 31, 1
    1e34:	82b970        	mull	a11, a9, a7
    1e37:	902c20        	addx2	a2, a12, a2
    1e3a:	904540        	addx2	a4, a5, a4
    1e3d:	c0a420        	sub	a10, a4, a2
    1e40:	054fb0        	extui	a4, a11, 31, 1
    1e43:	b2c970        	mulsh	a12, a9, a7
    1e46:	f89531        	l32r	a3, 9c (30fbc54d <_end+0x30fb92f5>)
    1e49:	2221e2        	l32i	a14, a1, 136
    1e4c:	f895b1        	l32r	a11, a0 (89be50c3 <_end+0x89be1e6b>)
    1e4f:	904c40        	addx2	a4, a12, a4
    1e52:	748a           	add.n	a7, a4, a8
    1e54:	826e30        	mull	a6, a14, a3
    1e57:	829eb0        	mull	a9, a14, a11
    1e5a:	b28e30        	mulsh	a8, a14, a3
    1e5d:	b2ceb0        	mulsh	a12, a14, a11
    1e60:	4821e2        	l32i	a14, a1, 0x120
    1e63:	054f60        	extui	a4, a6, 31, 1
    1e66:	904840        	addx2	a4, a8, a4
    1e69:	822eb0        	mull	a2, a14, a11
    1e6c:	b28eb0        	mulsh	a8, a14, a11
    1e6f:	056f20        	extui	a6, a2, 31, 1
    1e72:	902860        	addx2	a2, a8, a6
    1e75:	055f90        	extui	a5, a9, 31, 1
    1e78:	c08420        	sub	a8, a4, a2
    1e7b:	492142        	l32i	a4, a1, 0x124
    1e7e:	905c50        	addx2	a5, a12, a5
    1e81:	82ce30        	mull	a12, a14, a3
    1e84:	b2ee30        	mulsh	a14, a14, a3
    1e87:	052fc0        	extui	a2, a12, 31, 1
    1e8a:	826430        	mull	a6, a4, a3
    1e8d:	902e20        	addx2	a2, a14, a2
    1e90:	b2c430        	mulsh	a12, a4, a3
    1e93:	952a           	add.n	a9, a5, a2
    1e95:	055f60        	extui	a5, a6, 31, 1
    1e98:	905c50        	addx2	a5, a12, a5
    1e9b:	82e4b0        	mull	a14, a4, a11
    1e9e:	4a21c2        	l32i	a12, a1, 0x128
    1ea1:	b224b0        	mulsh	a2, a4, a11
    1ea4:	056fe0        	extui	a6, a14, 31, 1
    1ea7:	904260        	addx2	a4, a2, a6
    1eaa:	822cb0        	mull	a2, a12, a11
    1ead:	b2ecb0        	mulsh	a14, a12, a11
    1eb0:	056f20        	extui	a6, a2, 31, 1
    1eb3:	902e60        	addx2	a2, a14, a6
    1eb6:	c02520        	sub	a2, a5, a2
    1eb9:	52aa           	add.n	a5, a2, a10
    1ebb:	c0ea20        	sub	a14, a10, a2
    1ebe:	82ac30        	mull	a10, a12, a3
    1ec1:	b2cc30        	mulsh	a12, a12, a3
    1ec4:	302162        	l32i	a6, a1, 192
    1ec7:	052fa0        	extui	a2, a10, 31, 1
    1eca:	902c20        	addx2	a2, a12, a2
    1ecd:	242a           	add.n	a2, a4, a2
    1ecf:	496152        	s32i	a5, a1, 0x124
    1ed2:	824630        	mull	a4, a6, a3
    1ed5:	b25630        	mulsh	a5, a6, a3
    1ed8:	03cd           	mov.n	a12, a3
    1eda:	8236b0        	mull	a3, a6, a11
    1edd:	a27a           	add.n	a10, a2, a7
    1edf:	c07270        	sub	a7, a2, a7
    1ee2:	052f40        	extui	a2, a4, 31, 1
    1ee5:	054f30        	extui	a4, a3, 31, 1
    1ee8:	b236b0        	mulsh	a3, a6, a11
    1eeb:	78c162        	addi	a6, a1, 120
    1eee:	618654        	ae_lq56.i	aeq2, a6, 40
    1ef1:	61c644        	ae_lq56.i	aeq3, a6, 32
    1ef4:	f8f611552f 	{ addx2	a5, a5, a2; ae_addq56	aeq0, aeq2, aeq3 }
    1ef9:	368204        	ae_trunca32q48	a2, aeq0
    1efc:	906340        	addx2	a6, a3, a4
    1eff:	8232b0        	mull	a3, a2, a11
    1f02:	b2b2b0        	mulsh	a11, a2, a11
    1f05:	054f30        	extui	a4, a3, 31, 1
    1f08:	903b40        	addx2	a3, a11, a4
    1f0b:	c03350        	sub	a3, a3, a5
    1f0e:	438a           	add.n	a4, a3, a8
    1f10:	c03830        	sub	a3, a8, a3
    1f13:	b282c0        	mulsh	a8, a2, a12
    1f16:	8222c0        	mull	a2, a2, a12
    1f19:	01d1b2        	addmi	a11, a1, 0x100
    1f1c:	052f20        	extui	a2, a2, 31, 1
    1f1f:	902820        	addx2	a2, a8, a2
    1f22:	226a           	add.n	a2, a2, a6
    1f24:	529a           	add.n	a5, a2, a9
    1f26:	c02290        	sub	a2, a2, a9
    1f29:	78c192        	addi	a9, a1, 120
    1f2c:	6189c4        	ae_lq56.i	aeq2, a9, -32
    1f2f:	61cbf4        	ae_lq56.i	aeq3, a11, -8
    1f32:	013ec4        	ae_subq56	aeq0, aeq3, aeq2
    1f35:	368c04        	ae_trunca32q48	a12, aeq0
    1f38:	f85381        	l32r	a8, 84 (a57d8666 <_end+0xa57d540e>)
    1f3b:	82bc80        	mull	a11, a12, a8
    1f3e:	b26c80        	mulsh	a6, a12, a8
    1f41:	1821c2        	l32i	a12, a1, 96
    1f44:	058fb0        	extui	a8, a11, 31, 1
    1f47:	906680        	addx2	a6, a6, a8
    1f4a:	4321b2        	l32i	a11, a1, 0x10c
    1f4d:	c08c60        	sub	a8, a12, a6
    1f50:	66ca           	add.n	a6, a6, a12
    1f52:	96da           	add.n	a9, a6, a13
    1f54:	c066d0        	sub	a6, a6, a13
    1f57:	d8fa           	add.n	a13, a8, a15
    1f59:	c08f80        	sub	a8, a15, a8
    1f5c:	fdba           	add.n	a15, a13, a11
    1f5e:	c0bbd0        	sub	a11, a11, a13
    1f61:	a1d8           	l32i.n	a13, a1, 40
    1f63:	4861f2        	s32i	a15, a1, 0x120
    1f66:	4121c2        	l32i	a12, a1, 0x104
    1f69:	c0fd60        	sub	a15, a13, a6
    1f6c:	66da           	add.n	a6, a6, a13
    1f6e:	4021d2        	l32i	a13, a1, 0x100
    1f71:	2261f2        	s32i	a15, a1, 136
    1f74:	4a6162        	s32i	a6, a1, 0x128
    1f77:	f9da           	add.n	a15, a9, a13
    1f79:	c06d90        	sub	a6, a13, a9
    1f7c:	1a61f2        	s32i	a15, a1, 104
    1f7f:	c0dc80        	sub	a13, a12, a8
    1f82:	4221f2        	l32i	a15, a1, 0x108
    1f85:	2661b2        	s32i	a11, a1, 152
    1f88:	4361d2        	s32i	a13, a1, 0x10c
    1f8b:	4421b2        	l32i	a11, a1, 0x110
    1f8e:	e1d8           	l32i.n	a13, a1, 56
    1f90:	94fa           	add.n	a9, a4, a15
    1f92:	c04f40        	sub	a4, a15, a4
    1f95:	476162        	s32i	a6, a1, 0x11c
    1f98:	68ca           	add.n	a6, a8, a12
    1f9a:	a199           	s32i.n	a9, a1, 40
    1f9c:	406142        	s32i	a4, a1, 0x100
    1f9f:	c0cb30        	sub	a12, a11, a3
    1fa2:	f3ba           	add.n	a15, a3, a11
    1fa4:	95da           	add.n	a9, a5, a13
    1fa6:	c0dd50        	sub	a13, a13, a5
    1fa9:	462142        	l32i	a4, a1, 0x118
    1fac:	4d2152        	l32i	a5, a1, 0x134
    1faf:	4521b2        	l32i	a11, a1, 0x114
    1fb2:	242132        	l32i	a3, a1, 144
    1fb5:	416162        	s32i	a6, a1, 0x104
    1fb8:	4261c2        	s32i	a12, a1, 0x108
    1fbb:	c06570        	sub	a6, a5, a7
    1fbe:	775a           	add.n	a7, a7, a5
    1fc0:	c08420        	sub	a8, a4, a2
    1fc3:	c24a           	add.n	a12, a2, a4
    1fc5:	4aba           	add.n	a4, a10, a11
    1fc7:	c0aba0        	sub	a10, a11, a10
    1fca:	c053e0        	sub	a5, a3, a14
    1fcd:	be3a           	add.n	a11, a14, a3
    1fcf:	4b2132        	l32i	a3, a1, 0x12c
    1fd2:	4921e2        	l32i	a14, a1, 0x124
    1fd5:	2e3a           	add.n	a2, a14, a3
    1fd7:	c0e3e0        	sub	a14, a3, a14
    1fda:	4e2132        	l32i	a3, a1, 0x138
    1fdd:	2329           	s32i.n	a2, a3, 8
    1fdf:	4c2122        	l32i	a2, a1, 0x130
    1fe2:	2249           	s32i.n	a4, a2, 8
    1fe4:	a369           	s32i.n	a6, a3, 40
    1fe6:	a259           	s32i.n	a5, a2, 40
    1fe8:	1263e2        	s32i	a14, a3, 72
    1feb:	1262a2        	s32i	a10, a2, 72
    1fee:	1a6372        	s32i	a7, a3, 104
    1ff1:	1a62b2        	s32i	a11, a2, 104
    1ff4:	482162        	l32i	a6, a1, 0x120
    1ff7:	1a2172        	l32i	a7, a1, 104
    1ffa:	2221a2        	l32i	a10, a1, 136
    1ffd:	4321b2        	l32i	a11, a1, 0x10c
    2000:	2621e2        	l32i	a14, a1, 152
    2003:	4369           	s32i.n	a6, a3, 16
    2005:	4279           	s32i.n	a7, a2, 16
    2007:	c3a9           	s32i.n	a10, a3, 48
    2009:	c2b9           	s32i.n	a11, a2, 48
    200b:	1463e2        	s32i	a14, a3, 80
    200e:	472152        	l32i	a5, a1, 0x11c
    2011:	4a2162        	l32i	a6, a1, 0x128
    2014:	412172        	l32i	a7, a1, 0x104
    2017:	a1a8           	l32i.n	a10, a1, 40
    2019:	4221b2        	l32i	a11, a1, 0x108
    201c:	4021e2        	l32i	a14, a1, 0x100
    201f:	146252        	s32i	a5, a2, 80
    2022:	1c6362        	s32i	a6, a3, 112
    2025:	1c6272        	s32i	a7, a2, 112
    2028:	63a9           	s32i.n	a10, a3, 24
    202a:	6299           	s32i.n	a9, a2, 24
    202c:	e389           	s32i.n	a8, a3, 56
    202e:	e2b9           	s32i.n	a11, a2, 56
    2030:	1663e2        	s32i	a14, a3, 88
    2033:	1662d2        	s32i	a13, a2, 88
    2036:	1e63c2        	s32i	a12, a3, 120
    2039:	1e62f2        	s32i	a15, a2, 120
    203c:	f01d           	retw.n

0000203e <fix_fft16+0x74a>:
	...

00002040 <fix_fft20>:
    2040:	030136        	entry	a1, 0x180
    2043:	026d           	mov.n	a6, a2
    2045:	00a452        	movi	a5, 0x400
    2048:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    204b:	600204        	ae_lq32f.i	aeq0, a2, 0
    204e:	01d1e2        	addmi	a14, a1, 0x100
    2051:	d4e2bd230f 	{ ae_lq32f.i	aeq1, a3, 0; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    2056:	d4e3c781de 	{ addi	a13, a1, 120; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    205b:	fc24430eee 	{ addi	a14, a14, 48; ae_roundsq32asym	aeq0, aeq0 }
    2060:	fd2c770def 	{ ae_sp24x2s.i	aep0, a13, -16; ae_roundsq32asym	aeq1, aeq1 }
    2065:	80a0d2        	movi	a13, 128
    2068:	60a2d4        	ae_lq32f.x	aeq2, a2, a13
    206b:	d7e2935eef 	{ or	a5, a14, a14; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2070:	60fd34        	ae_lq32f.xu	aeq3, a13, a3
    2073:	d7e3f9c50f 	{ ae_sq32f.iu	aeq0, a5, 0; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2078:	fe344602fe 	{ addi	a15, a2, 96; ae_roundsq32asym	aeq2, aeq2 }
    207d:	ff3c46037e 	{ addi	a7, a3, 96; ae_roundsq32asym	aeq3, aeq3 }
    2082:	625514        	ae_sq32f.iu	aeq1, a5, 4
    2085:	600f04        	ae_lq32f.i	aeq0, a15, 0
    2088:	d4e2bd270f 	{ ae_lq32f.i	aeq1, a7, 0; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    208d:	d4e3f9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2092:	fc244402ae 	{ addi	a10, a2, 64; ae_roundsq32asym	aeq0, aeq0 }
    2097:	21f9           	s32i.n	a15, a1, 8
    2099:	78c1f2        	addi	a15, a1, 120
    209c:	627514        	ae_sq32f.iu	aeq3, a5, 4
    209f:	608a04        	ae_lq32f.i	aeq2, a10, 0
    20a2:	d7e2ba1fdf 	{ ae_sq56s.i	aeq1, a15, -24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    20a7:	60c784        	ae_lq32f.i	aeq3, a7, -32
    20aa:	fe344403ce 	{ addi	a12, a3, 64; ae_roundsq32asym	aeq2, aeq2 }
    20af:	d7e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    20b4:	610fd4        	ae_lq56.i	aeq0, a15, -24
    20b7:	fc247d2a8f 	{ ae_lq32f.i	aeq1, a10, -32; ae_roundsq32asym	aeq0, aeq0 }
    20bc:	d4e3c2029e 	{ addi	a9, a2, 32; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    20c1:	ff3c42038e 	{ addi	a8, a3, 32; ae_roundsq32asym	aeq3, aeq3 }
    20c6:	fd2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq1, aeq1 }
    20cb:	600804        	ae_lq32f.i	aeq0, a8, 0
    20ce:	d4e2b9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    20d3:	627514        	ae_sq32f.iu	aeq3, a5, 4
    20d6:	fc2479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    20db:	624514        	ae_sq32f.iu	aeq0, a5, 4
    20de:	01d1b2        	addmi	a11, a1, 0x100
    20e1:	f7e451        	l32r	a5, 74 (18c <fix_fft5_stage>)
    20e4:	276142        	s32i	a4, a1, 156
    20e7:	2461a2        	s32i	a10, a1, 144
    20ea:	2361c2        	s32i	a12, a1, 140
    20ed:	7cc242        	addi	a4, a2, 124
    20f0:	01d1a2        	addmi	a10, a1, 0x100
    20f3:	bb4b           	addi.n	a11, a11, 4
    20f5:	0ecd           	mov.n	a12, a14
    20f7:	256172        	s32i	a7, a1, 148
    20fa:	8139           	s32i.n	a3, a1, 32
    20fc:	61d9           	s32i.n	a13, a1, 24
    20fe:	092d           	mov.n	a2, a9
    2100:	a199           	s32i.n	a9, a1, 40
    2102:	083d           	mov.n	a3, a8
    2104:	166142        	s32i	a4, a1, 88
    2107:	1861a2        	s32i	a10, a1, 96
    210a:	0e7d           	mov.n	a7, a14
    210c:	0005e0        	callx8	a5
    210f:	78c182        	addi	a8, a1, 120
    2112:	600224        	ae_lq32f.i	aeq0, a2, 8
    2115:	5408e4        	ae_lp24x2.i	aep0, a8, -16
    2118:	d4e2f061de 	{ l32i	a13, a1, 24; ae_mulfq32sp16u.l	aeq1, aeq0, aep0 }
    211d:	81c8           	l32i.n	a12, a1, 32
    211f:	fd2c53a77f 	{ or	a10, a7, a7; ae_roundsq32asym	aeq1, aeq1 }
    2124:	21e8           	l32i.n	a14, a1, 8
    2126:	625a04        	ae_sq32f.iu	aeq1, a10, 0
    2129:	604434        	ae_lq32f.i	aeq1, a4, 12
    212c:	2521f2        	l32i	a15, a1, 148
    212f:	631174        	ae_sq56s.i	aeq1, a1, 56
    2132:	604d24        	ae_lq32f.i	aeq1, a13, 8
    2135:	600c24        	ae_lq32f.i	aeq0, a12, 8
    2138:	631814        	ae_sq56s.i	aeq1, a8, 8
    213b:	604e24        	ae_lq32f.i	aeq1, a14, 8
    213e:	242122        	l32i	a2, a1, 144
    2141:	6318a4        	ae_sq56s.i	aeq1, a8, -48
    2144:	604f24        	ae_lq32f.i	aeq1, a15, 8
    2147:	630124        	ae_sq56s.i	aeq0, a1, 16
    214a:	232142        	l32i	a4, a1, 140
    214d:	608324        	ae_lq32f.i	aeq2, a3, 8
    2150:	d6e2ba189f 	{ ae_sq56s.i	aeq1, a8, -56; ae_mulfq32sp16u.l	aeq0, aeq2, aep0 }
    2155:	614124        	ae_lq56.i	aeq1, a1, 16
    2158:	d5e3bd662f 	{ ae_lq32f.i	aeq3, a6, 8; ae_mulfq32sp16u.l	aeq2, aeq1, aep0 }
    215d:	d7e3fd222f 	{ ae_lq32f.i	aeq1, a2, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2162:	fc247a116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_roundsq32asym	aeq0, aeq0 }
    2167:	604424        	ae_lq32f.i	aeq1, a4, 8
    216a:	631124        	ae_sq56s.i	aeq1, a1, 16
    216d:	614174        	ae_lq56.i	aeq1, a1, 56
    2170:	fc3c79ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq3 }
    2175:	d4e3fde81f 	{ ae_lq56.i	aeq3, a8, 8; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    217a:	fc3479ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq2 }
    217f:	d7e3fdc8af 	{ ae_lq56.i	aeq2, a8, -48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2184:	fc2c79ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq1 }
    2189:	d7e2bda89f 	{ ae_lq56.i	aeq1, a8, -56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    218e:	d4e3f9ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2193:	fc3c7de16f 	{ ae_lq56.i	aeq3, a1, 48; ae_roundsq32asym	aeq0, aeq3 }
    2198:	fc3479ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_roundsq32asym	aeq0, aeq2 }
    219d:	d7e3fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    21a2:	d7e2b9ca1f 	{ ae_sq32f.iu	aeq0, a10, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    21a7:	fd2c53c77f 	{ or	a12, a7, a7; ae_roundsq32asym	aeq1, aeq1 }
    21ac:	fd3c79da1f 	{ ae_sq32f.iu	aeq1, a10, 4; ae_roundsq32asym	aeq1, aeq3 }
    21b1:	ff3479da1f 	{ ae_sq32f.iu	aeq1, a10, 4; ae_roundsq32asym	aeq3, aeq2 }
    21b6:	627a14        	ae_sq32f.iu	aeq3, a10, 4
    21b9:	01d1b2        	addmi	a11, a1, 0x100
    21bc:	01d1a2        	addmi	a10, a1, 0x100
    21bf:	d0caa2        	addi	a10, a10, -48
    21c2:	d4cbb2        	addi	a11, a11, -44
    21c5:	146132        	s32i	a3, a1, 80
    21c8:	2061a2        	s32i	a10, a1, 128
    21cb:	0005e0        	callx8	a5
    21ce:	78c1a2        	addi	a10, a1, 120
    21d1:	600244        	ae_lq32f.i	aeq0, a2, 16
    21d4:	540ae4        	ae_lp24x2.i	aep0, a10, -16
    21d7:	d4e2b081de 	{ l32i	a13, a1, 32; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    21dc:	604344        	ae_lq32f.i	aeq1, a3, 16
    21df:	fc2453877f 	{ or	a8, a7, a7; ae_roundsq32asym	aeq0, aeq0 }
    21e4:	d4e3f1613e 	{ l32i	a3, a1, 88; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    21e9:	a1c8           	l32i.n	a12, a1, 40
    21eb:	624804        	ae_sq32f.iu	aeq0, a8, 0
    21ee:	600644        	ae_lq32f.i	aeq0, a6, 16
    21f1:	61e8           	l32i.n	a14, a1, 24
    21f3:	608444        	ae_lq32f.i	aeq2, a4, 16
    21f6:	630aa4        	ae_sq56s.i	aeq0, a10, -48
    21f9:	600d44        	ae_lq32f.i	aeq0, a13, 16
    21fc:	2148           	l32i.n	a4, a1, 8
    21fe:	d6e2ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq2, aep0 }
    2203:	608354        	ae_lq32f.i	aeq2, a3, 20
    2206:	fc2472512e 	{ l32i	a2, a1, 148; ae_roundsq32asym	aeq0, aeq0 }
    220b:	60cc44        	ae_lq32f.i	aeq3, a12, 16
    220e:	d7e3fa2a9f 	{ ae_sq56s.i	aeq2, a10, -56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2213:	608e44        	ae_lq32f.i	aeq2, a14, 16
    2216:	632174        	ae_sq56s.i	aeq2, a1, 56
    2219:	608444        	ae_lq32f.i	aeq2, a4, 16
    221c:	632af4        	ae_sq56s.i	aeq2, a10, -8
    221f:	608244        	ae_lq32f.i	aeq2, a2, 16
    2222:	632a04        	ae_sq56s.i	aeq2, a10, 0
    2225:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    222a:	631164        	ae_sq56s.i	aeq1, a1, 48
    222d:	618aa4        	ae_lq56.i	aeq2, a10, -48
    2230:	d6e2fde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    2235:	d7e3bde16f 	{ ae_lq56.i	aeq3, a1, 48; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    223a:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    223f:	61ca94        	ae_lq56.i	aeq3, a10, -56
    2242:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2247:	d7e3fda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    224c:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2251:	fc347dcaff 	{ ae_lq56.i	aeq2, a10, -8; ae_roundsq32asym	aeq0, aeq2 }
    2256:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    225b:	fc3c7dea0f 	{ ae_lq56.i	aeq3, a10, 0; ae_roundsq32asym	aeq0, aeq3 }
    2260:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2265:	fd2c53955f 	{ or	a9, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    226a:	01d1b2        	addmi	a11, a1, 0x100
    226d:	01d1f2        	addmi	a15, a1, 0x100
    2270:	fe3479d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq2, aeq2 }
    2275:	ff3c4a0fae 	{ addi	a10, a15, -96; ae_roundsq32asym	aeq3, aeq3 }
    227a:	626814        	ae_sq32f.iu	aeq2, a8, 4
    227d:	a4cbb2        	addi	a11, a11, -92
    2280:	07cd           	mov.n	a12, a7
    2282:	075d           	mov.n	a5, a7
    2284:	627814        	ae_sq32f.iu	aeq3, a8, 4
    2287:	2661a2        	s32i	a10, a1, 152
    228a:	097d           	mov.n	a7, a9
    228c:	0009e0        	callx8	a9
    228f:	78c1b2        	addi	a11, a1, 120
    2292:	604464        	ae_lq32f.i	aeq1, a4, 24
    2295:	540be4        	ae_lp24x2.i	aep0, a11, -16
    2298:	d4e3f2318e 	{ l32i	a8, a1, 140; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    229d:	81d8           	l32i.n	a13, a1, 32
    229f:	079d           	mov.n	a9, a7
    22a1:	057d           	mov.n	a7, a5
    22a3:	fd2c7d026f 	{ ae_lq32f.i	aeq0, a2, 24; ae_roundsq32asym	aeq1, aeq1 }
    22a8:	d4e2b2414e 	{ l32i	a4, a1, 144; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    22ad:	608864        	ae_lq32f.i	aeq2, a8, 24
    22b0:	625704        	ae_sq32f.iu	aeq1, a7, 0
    22b3:	604664        	ae_lq32f.i	aeq1, a6, 24
    22b6:	a1a8           	l32i.n	a10, a1, 40
    22b8:	632114        	ae_sq56s.i	aeq2, a1, 8
    22bb:	1421c2        	l32i	a12, a1, 80
    22be:	631bb4        	ae_sq56s.i	aeq1, a11, -40
    22c1:	604d64        	ae_lq32f.i	aeq1, a13, 24
    22c4:	631144        	ae_sq56s.i	aeq1, a1, 32
    22c7:	614114        	ae_lq56.i	aeq1, a1, 8
    22ca:	61e8           	l32i.n	a14, a1, 24
    22cc:	60c464        	ae_lq32f.i	aeq3, a4, 24
    22cf:	d4e3ba015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    22d4:	d7e3fd237f 	{ ae_lq32f.i	aeq1, a3, 28; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    22d9:	608a64        	ae_lq32f.i	aeq2, a10, 24
    22dc:	ff3c7a1bcf 	{ ae_sq56s.i	aeq1, a11, -32; ae_roundsq32asym	aeq3, aeq3 }
    22e1:	614154        	ae_lq56.i	aeq1, a1, 40
    22e4:	632124        	ae_sq56s.i	aeq2, a1, 16
    22e7:	fc2c7a011f 	{ ae_sq56s.i	aeq0, a1, 8; ae_roundsq32asym	aeq0, aeq1 }
    22ec:	604e64        	ae_lq32f.i	aeq1, a14, 24
    22ef:	624714        	ae_sq32f.iu	aeq0, a7, 4
    22f2:	631134        	ae_sq56s.i	aeq1, a1, 24
    22f5:	614124        	ae_lq56.i	aeq1, a1, 16
    22f8:	d4e3fd4c6f 	{ ae_lq32f.i	aeq2, a12, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    22fd:	d7e2b9f71f 	{ ae_sq32f.iu	aeq3, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2302:	61c114        	ae_lq56.i	aeq3, a1, 8
    2305:	fc3c7debbf 	{ ae_lq56.i	aeq3, a11, -40; ae_roundsq32asym	aeq0, aeq3 }
    230a:	fc2c79c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_roundsq32asym	aeq0, aeq1 }
    230f:	d7e3fda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2314:	d4e3f9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2319:	fc347dcbcf 	{ ae_lq56.i	aeq2, a11, -32; ae_roundsq32asym	aeq0, aeq2 }
    231e:	d7e2b9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2323:	fc3c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq0, aeq3 }
    2328:	d7e3f9c71f 	{ ae_sq32f.iu	aeq0, a7, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    232d:	fd2c53a55f 	{ or	a10, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    2332:	01d1f2        	addmi	a15, a1, 0x100
    2335:	fe3479d71f 	{ ae_sq32f.iu	aeq1, a7, 4; ae_roundsq32asym	aeq2, aeq2 }
    233a:	ff3c434fbe 	{ addi	a11, a15, 52; ae_roundsq32asym	aeq3, aeq3 }
    233f:	626714        	ae_sq32f.iu	aeq2, a7, 4
    2342:	05cd           	mov.n	a12, a5
    2344:	627714        	ae_sq32f.iu	aeq3, a7, 4
    2347:	054d           	mov.n	a4, a5
    2349:	0009e0        	callx8	a9
    234c:	2721b2        	l32i	a11, a1, 156
    234f:	182122        	l32i	a2, a1, 96
    2352:	262152        	l32i	a5, a1, 152
    2355:	202132        	l32i	a3, a1, 128
    2358:	5c2204        	ae_lp24x2f.i	aep2, a2, 0
    235b:	5c5504        	ae_lp24x2f.i	aep5, a5, 0
    235e:	daa92f330f 	{ ae_lp24x2f.i	aep3, a3, 0; ae_addsp24s	aep4, aep2, aep5 }
    2363:	ddaaaf740f 	{ ae_lp24x2f.i	aep7, a4, 0; ae_subsp24s	aep2, aep2, aep5 }
    2368:	daed53a44f 	{ or	a10, a4, a4; ae_addsp24s	aep5, aep3, aep7 }
    236d:	ce3c           	movi.n	a14, 60
    236f:	b09bb0        	addx8	a9, a11, a11
    2372:	ddeeef151f 	{ ae_lp24x2f.i	aep1, a5, 8; ae_subsp24s	aep3, aep3, aep7 }
    2377:	054d           	mov.n	a4, a5
    2379:	5c6314        	ae_lp24x2f.i	aep6, a3, 8
    237c:	035d           	mov.n	a5, a3
    237e:	cd4c           	movi.n	a13, 76
    2380:	0b3d           	mov.n	a3, a11
    2382:	a07bb0        	addx4	a7, a11, a11
    2385:	11cbc0        	slli	a12, a11, 4
    2388:	d1bbe0        	mul16s	a11, a11, a14
    238b:	d1e3d0        	mul16s	a14, a3, a13
    238e:	11d9e0        	slli	a13, a9, 2
    2391:	483c           	movi.n	a8, 52
    2393:	5c0214        	ae_lp24x2f.i	aep0, a2, 8
    2396:	db215481cf 	{ s32i.n	a12, a1, 32; ae_addsp24s	aep7, aep0, aep1 }
    239b:	dc22b7511f 	{ ae_sp24x2s.i	aep5, a1, 8; ae_subsp24s	aep0, aep0, aep1 }
    23a0:	78c1c2        	addi	a12, a1, 120
    23a3:	2361d2        	s32i	a13, a1, 140
    23a6:	11d9d0        	slli	a13, a9, 3
    23a9:	d19380        	mul16s	a9, a3, a8
    23ac:	5c5a14        	ae_lp24x2f.i	aep5, a10, 8
    23af:	ddbaf73caf 	{ ae_sp24x2s.i	aep3, a12, -48; ae_subsp24s	aep3, aep6, aep5 }
    23b4:	2461d2        	s32i	a13, a1, 144
    23b7:	256192        	s32i	a9, a1, 148
    23ba:	11d3b0        	slli	a13, a3, 5
    23bd:	562134        	ae_sp24x2s.i	aep2, a1, 24
    23c0:	dbb9777cbf 	{ ae_sp24x2s.i	aep7, a12, -40; ae_addsp24s	aep7, aep6, aep5 }
    23c5:	560124        	ae_sp24x2s.i	aep0, a1, 16
    23c8:	1661d2        	s32i	a13, a1, 88
    23cb:	5c0224        	ae_lp24x2f.i	aep0, a2, 16
    23ce:	5c5424        	ae_lp24x2f.i	aep5, a4, 16
    23d1:	dba137316f 	{ ae_sp24x2s.i	aep3, a1, 48; ae_addsp24s	aep6, aep0, aep5 }
    23d6:	dca2af252f 	{ ae_lp24x2f.i	aep2, a5, 16; ae_subsp24s	aep0, aep0, aep5 }
    23db:	1139           	s32i.n	a3, a1, 4
    23dd:	f08330        	subx8	a8, a3, a3
    23e0:	11c7d0        	slli	a12, a7, 3
    23e3:	11f7e0        	slli	a15, a7, 2
    23e6:	907330        	addx2	a7, a3, a3
    23e9:	78c132        	addi	a3, a1, 120
    23ec:	5c5a24        	ae_lp24x2f.i	aep5, a10, 16
    23ef:	dba937639f 	{ ae_sp24x2s.i	aep6, a3, -56; ae_addsp24s	aep6, aep2, aep5 }
    23f4:	dcaab7015f 	{ ae_sp24x2s.i	aep0, a1, 40; ae_subsp24s	aep0, aep2, aep5 }
    23f9:	5c1234        	ae_lp24x2f.i	aep1, a2, 24
    23fc:	5c3434        	ae_lp24x2f.i	aep3, a4, 24
    23ff:	db6537630f 	{ ae_sp24x2s.i	aep6, a3, 0; ae_addsp24s	aep6, aep1, aep3 }
    2404:	dc66b7017f 	{ ae_sp24x2s.i	aep0, a1, 56; ae_subsp24s	aep0, aep1, aep3 }
    2409:	5c5534        	ae_lp24x2f.i	aep5, a5, 24
    240c:	5c3a34        	ae_lp24x2f.i	aep3, a10, 24
    240f:	db753763ff 	{ ae_sp24x2s.i	aep6, a3, -8; ae_addsp24s	aep6, aep5, aep3 }
    2414:	de76f0311f 	{ ae_lp24x2.i	aep3, a1, 8; ae_subsp24s	aep5, aep5, aep3 }
    2419:	d9713703ef 	{ ae_sp24x2s.i	aep0, a3, -16; ae_addsp24s	aep2, aep4, aep3 }
    241e:	dd72ef044f 	{ ae_lp24x2f.i	aep0, a4, 32; ae_subsp24s	aep3, aep4, aep3 }
    2423:	040c           	movi.n	a4, 0
    2425:	5f2644        	ae_sp24x2f.x	aep2, a6, a4
    2428:	5c1244        	ae_lp24x2f.i	aep1, a2, 32
    242b:	da0507814e 	{ addi	a4, a1, 120; ae_addsp24s	aep4, aep1, aep0 }
    2430:	1138           	l32i.n	a3, a1, 4
    2432:	dc06a936cf 	{ ae_sp24x2f.x	aep3, a6, a12; ae_subsp24s	aep0, aep1, aep0 }
    2437:	5434a4        	ae_lp24x2.i	aep3, a4, -48
    243a:	fe783744df 	{ ae_sp24x2s.i	aep4, a4, -24; ae_negsp24s	aep4, aep3 }
    243f:	dc71f7011f 	{ ae_sp24x2s.i	aep0, a1, 8; ae_selp24.lh	aep1, aep4, aep3 }
    2444:	540134        	ae_lp24x2.i	aep0, a1, 24
    2447:	da212f254f 	{ ae_lp24x2f.i	aep2, a5, 32; ae_addsp24s	aep4, aep0, aep1 }
    244c:	dc22af3a4f 	{ ae_lp24x2f.i	aep3, a10, 32; ae_subsp24s	aep0, aep0, aep1 }
    2451:	d8696946bf 	{ ae_sp24x2f.x	aep4, a6, a11; ae_addsp24s	aep1, aep2, aep3 }
    2456:	dd6aa906ff 	{ ae_sp24x2f.x	aep0, a6, a15; ae_subsp24s	aep2, aep2, aep3 }
    245b:	5404b4        	ae_lp24x2.i	aep0, a4, -40
    245e:	dae130815e 	{ l32i	a5, a1, 32; ae_addsp24s	aep4, aep0, aep7 }
    2463:	dde2f0016f 	{ ae_lp24x2.i	aep0, a1, 48; ae_subsp24s	aep3, aep0, aep7 }
    2468:	ff187231ae 	{ l32i	a10, a1, 140; ae_negsp24s	aep7, aep0 }
    246d:	1198d0        	slli	a9, a8, 3
    2470:	dc1da9465f 	{ ae_sp24x2f.x	aep4, a6, a5; ae_selp24.lh	aep0, aep7, aep0 }
    2475:	5f3694        	ae_sp24x2f.x	aep3, a6, a9
    2478:	543124        	ae_lp24x2.i	aep3, a1, 16
    247b:	db0d70449f 	{ ae_lp24x2.i	aep4, a4, -56; ae_addsp24s	aep7, aep3, aep0 }
    2480:	dc0ea976ef 	{ ae_sp24x2f.x	aep7, a6, a14; ae_subsp24s	aep0, aep3, aep0 }
    2485:	547404        	ae_lp24x2.i	aep7, a4, 0
    2488:	d9f17161be 	{ l32i	a11, a1, 88; ae_addsp24s	aep3, aep4, aep7 }
    248d:	dff2f044ff 	{ ae_lp24x2.i	aep4, a4, -8; ae_subsp24s	aep7, aep4, aep7 }
    2492:	2421c2        	l32i	a12, a1, 144
    2495:	d8d12906af 	{ ae_sp24x2f.x	aep0, a6, a10; ae_addsp24s	aep0, aep4, aep6 }
    249a:	ded2b0617f 	{ ae_lp24x2.i	aep6, a1, 56; ae_subsp24s	aep4, aep4, aep6 }
    249f:	fdd86936bf 	{ ae_sp24x2f.x	aep3, a6, a11; ae_negsp24s	aep3, aep6 }
    24a4:	ddcdf251ee 	{ l32i	a14, a1, 148; ae_selp24.lh	aep3, aep3, aep6 }
    24a9:	5f76c4        	ae_sp24x2f.x	aep7, a6, a12
    24ac:	547154        	ae_lp24x2.i	aep7, a1, 40
    24af:	07f364        	ae_addsp24s	aep6, aep7, aep3
    24b2:	11d7e0        	slli	a13, a7, 2
    24b5:	dd7ee966df 	{ ae_sp24x2f.x	aep6, a6, a13; ae_subsp24s	aep3, aep7, aep3 }
    24ba:	ffb86936ef 	{ ae_sp24x2f.x	aep3, a6, a14; ae_negsp24s	aep7, aep5 }
    24bf:	1127c0        	slli	a2, a7, 4
    24c2:	11f3d0        	slli	a15, a3, 3
    24c5:	fd5869062f 	{ ae_sp24x2f.x	aep0, a6, a2; ae_negsp24s	aep3, aep2 }
    24ca:	debde946ff 	{ ae_sp24x2f.x	aep4, a6, a15; ae_selp24.lh	aep5, aep7, aep5 }
    24cf:	dc4db064ef 	{ ae_lp24x2.i	aep6, a4, -16; ae_selp24.lh	aep0, aep3, aep2 }
    24d4:	dbb9402ccf 	{ movi	a12, 44; ae_addsp24s	aep7, aep6, aep5 }
    24d9:	ddbaf044df 	{ ae_lp24x2.i	aep4, a4, -24; ae_subsp24s	aep3, aep6, aep5 }
    24de:	1188e0        	slli	a8, a8, 2
    24e1:	11b3a0        	slli	a11, a3, 6
    24e4:	d1e3c0        	mul16s	a14, a3, a12
    24e7:	da3170611f 	{ ae_lp24x2.i	aep6, a1, 8; ae_addsp24s	aep5, aep4, aep1 }
    24ec:	db1969768f 	{ ae_sp24x2f.x	aep7, a6, a8; ae_addsp24s	aep7, aep6, aep0 }
    24f1:	a0d3b0        	addx4	a13, a3, a11
    24f4:	11a3e0        	slli	a10, a3, 2
    24f7:	1177d0        	slli	a7, a7, 3
    24fa:	dc32e936df 	{ ae_sp24x2f.x	aep3, a6, a13; ae_subsp24s	aep1, aep4, aep1 }
    24ff:	dc1aa956bf 	{ ae_sp24x2f.x	aep5, a6, a11; ae_subsp24s	aep0, aep6, aep0 }
    2504:	5f1674        	ae_sp24x2f.x	aep1, a6, a7
    2507:	5f76e4        	ae_sp24x2f.x	aep7, a6, a14
    250a:	5f06a4        	ae_sp24x2f.x	aep0, a6, a10
    250d:	f01d           	retw.n

0000250f <fix_fft20+0x4cf>:
	...

00002510 <fix_fft30>:
    2510:	04a136        	entry	a1, 0x250
    2513:	037d           	mov.n	a7, a3
    2515:	80a0f2        	movi	a15, 128
    2518:	00a432        	movi	a3, 0x400
    251b:	300334        	ae_cvtp24a16x2.ll	aep0, a3, a3
    251e:	6067f4        	ae_lq32f.x	aeq1, a7, a15
    2521:	78c192        	addi	a9, a1, 120
    2524:	60c204        	ae_lq32f.i	aeq3, a2, 0
    2527:	02d1c2        	addmi	a12, a1, 0x200
    252a:	d6e3fa199f 	{ ae_sq56s.i	aeq1, a9, -56; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    252f:	600704        	ae_lq32f.i	aeq0, a7, 0
    2532:	d4e2bbd2ff 	{ ae_lq32f.x	aeq2, a2, a15; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    2537:	01d182        	addmi	a8, a1, 0x100
    253a:	fd2c47c2ae 	{ addi	a10, a2, 124; ae_roundsq32asym	aeq1, aeq1 }
    253f:	fc244b0cce 	{ addi	a12, a12, -80; ae_roundsq32asym	aeq0, aeq0 }
    2544:	5608b4        	ae_sp24x2s.i	aep0, a8, -40
    2547:	0c8d           	mov.n	a8, a12
    2549:	632174        	ae_sq56s.i	aeq2, a1, 56
    254c:	7cc792        	addi	a9, a7, 124
    254f:	608a54        	ae_lq32f.i	aeq2, a10, 20
    2552:	d6e2f9d80f 	{ ae_sq32f.iu	aeq1, a8, 0; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    2557:	20c2f2        	addi	a15, a2, 32
    255a:	c53c           	movi.n	a5, 60
    255c:	608954        	ae_lq32f.i	aeq2, a9, 20
    255f:	d7e280c06f 	{ movi	a6, 192; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2564:	d15450        	mul16s	a5, a4, a5
    2567:	60cf44        	ae_lq32f.i	aeq3, a15, 16
    256a:	d26a           	add.n	a13, a2, a6
    256c:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2571:	d6e3c0a0ef 	{ movi	a14, 160; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    2576:	3f61d2        	s32i	a13, a1, 252
    2579:	ff3450d2ef 	{ add	a13, a2, a14; ae_roundsq32asym	aeq3, aeq2 }
    257e:	fd2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq1, aeq1 }
    2583:	4961a2        	s32i	a10, a1, 0x124
    2586:	b75a           	add.n	a11, a7, a5
    2588:	e25a           	add.n	a14, a2, a5
    258a:	025d           	mov.n	a5, a2
    258c:	c0a0a2        	movi	a10, 192
    258f:	627814        	ae_sq32f.iu	aeq3, a8, 4
    2592:	60a2a4        	ae_lq32f.x	aeq2, a2, a10
    2595:	01d262        	addmi	a6, a2, 0x100
    2598:	426122        	s32i	a2, a1, 0x108
    259b:	d7e2bc6a7f 	{ ae_lq32f.xu	aeq3, a10, a7; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    25a0:	072d           	mov.n	a2, a7
    25a2:	3e6142        	s32i	a4, a1, 248
    25a5:	625814        	ae_sq32f.iu	aeq1, a8, 4
    25a8:	446172        	s32i	a7, a1, 0x110
    25ab:	604744        	ae_lq32f.i	aeq1, a7, 16
    25ae:	e0a042        	movi	a4, 224
    25b1:	4b61b2        	s32i	a11, a1, 0x12c
    25b4:	4a61e2        	s32i	a14, a1, 0x128
    25b7:	436162        	s32i	a6, a1, 0x10c
    25ba:	486192        	s32i	a9, a1, 0x120
    25bd:	4061a2        	s32i	a10, a1, 0x100
    25c0:	631134        	ae_sq56s.i	aeq1, a1, 24
    25c3:	3061d2        	s32i	a13, a1, 192
    25c6:	4561f2        	s32i	a15, a1, 0x114
    25c9:	606544        	ae_lq32f.x	aeq1, a5, a4
    25cc:	11a9           	s32i.n	a10, a1, 4
    25ce:	78c172        	addi	a7, a1, 120
    25d1:	631754        	ae_sq56s.i	aeq1, a7, 40
    25d4:	607424        	ae_lq32f.xu	aeq1, a4, a2
    25d7:	416142        	s32i	a4, a1, 0x104
    25da:	a0a042        	movi	a4, 160
    25dd:	631144        	ae_sq56s.i	aeq1, a1, 32
    25e0:	606544        	ae_lq32f.x	aeq1, a5, a4
    25e3:	631154        	ae_sq56s.i	aeq1, a1, 40
    25e6:	607424        	ae_lq32f.xu	aeq1, a4, a2
    25e9:	60c5e2        	addi	a14, a5, 96
    25ec:	631114        	ae_sq56s.i	aeq1, a1, 8
    25ef:	604544        	ae_lq32f.i	aeq1, a5, 16
    25f2:	631124        	ae_sq56s.i	aeq1, a1, 16
    25f5:	604e04        	ae_lq32f.i	aeq1, a14, 0
    25f8:	6317d4        	ae_sq56s.i	aeq1, a7, -24
    25fb:	604e44        	ae_lq32f.i	aeq1, a14, 16
    25fe:	631734        	ae_sq56s.i	aeq1, a7, 24
    2601:	604e84        	ae_lq32f.i	aeq1, a14, -32
    2604:	6317e4        	ae_sq56s.i	aeq1, a7, -16
    2607:	604ec4        	ae_lq32f.i	aeq1, a14, -16
    260a:	40c562        	addi	a6, a5, 64
    260d:	631744        	ae_sq56s.i	aeq1, a7, 32
    2610:	604f04        	ae_lq32f.i	aeq1, a15, 0
    2613:	631164        	ae_sq56s.i	aeq1, a1, 48
    2616:	604d44        	ae_lq32f.i	aeq1, a13, 16
    2619:	3f21d2        	l32i	a13, a1, 252
    261c:	2e61e2        	s32i	a14, a1, 184
    261f:	631774        	ae_sq56s.i	aeq1, a7, 56
    2622:	1178           	l32i.n	a7, a1, 4
    2624:	20c2f2        	addi	a15, a2, 32
    2627:	604d44        	ae_lq32f.i	aeq1, a13, 16
    262a:	78c1e2        	addi	a14, a1, 120
    262d:	631e04        	ae_sq56s.i	aeq1, a14, 0
    2630:	604f04        	ae_lq32f.i	aeq1, a15, 0
    2633:	60c292        	addi	a9, a2, 96
    2636:	631e64        	ae_sq56s.i	aeq1, a14, 48
    2639:	604744        	ae_lq32f.i	aeq1, a7, 16
    263c:	631ef4        	ae_sq56s.i	aeq1, a14, -8
    263f:	604904        	ae_lq32f.i	aeq1, a9, 0
    2642:	631eb4        	ae_sq56s.i	aeq1, a14, -40
    2645:	604944        	ae_lq32f.i	aeq1, a9, 16
    2648:	d6e3fa1e1f 	{ ae_sq56s.i	aeq1, a14, 8; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    264d:	60c984        	ae_lq32f.i	aeq3, a9, -32
    2650:	633ec4        	ae_sq56s.i	aeq3, a14, -32
    2653:	61c154        	ae_lq56.i	aeq3, a1, 40
    2656:	d7e3fd0f4f 	{ ae_lq32f.i	aeq0, a15, 16; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    265b:	d4e2b3e1de 	{ l32i	a13, a1, 248; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    2660:	633ea4        	ae_sq56s.i	aeq3, a14, -48
    2663:	fc247d69cf 	{ ae_lq32f.i	aeq3, a9, -16; ae_roundsq32asym	aeq0, aeq0 }
    2668:	40c2a2        	addi	a10, a2, 64
    266b:	633e24        	ae_sq56s.i	aeq3, a14, 16
    266e:	60c444        	ae_lq32f.i	aeq3, a4, 16
    2671:	633154        	ae_sq56s.i	aeq3, a1, 40
    2674:	61c114        	ae_lq56.i	aeq3, a1, 8
    2677:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    267c:	0a2d           	mov.n	a2, a10
    267e:	fc347a311f 	{ ae_sq56s.i	aeq3, a1, 8; ae_roundsq32asym	aeq0, aeq2 }
    2683:	61ced4        	ae_lq56.i	aeq3, a14, -24
    2686:	d7e3bdeebf 	{ ae_lq56.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    268b:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2690:	d6e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    2695:	fe347de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
    269a:	d6e3b9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
    269f:	ff2c7da13f 	{ ae_lq56.i	aeq1, a1, 24; ae_roundsq32asym	aeq3, aeq1 }
    26a4:	627814        	ae_sq32f.iu	aeq3, a8, 4
    26a7:	61cea4        	ae_lq56.i	aeq3, a14, -48
    26aa:	d4e3ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    26af:	fe3c7daeef 	{ ae_lq56.i	aeq1, a14, -16; ae_roundsq32asym	aeq2, aeq3 }
    26b4:	d5e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq1, aep0 }
    26b9:	618114        	ae_lq56.i	aeq2, a1, 8
    26bc:	fe347daecf 	{ ae_lq56.i	aeq1, a14, -32; ae_roundsq32asym	aeq2, aeq2 }
    26c1:	d4e3ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    26c6:	fe3c79e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_roundsq32asym	aeq2, aeq3 }
    26cb:	fc247dee0f 	{ ae_lq56.i	aeq3, a14, 0; ae_roundsq32asym	aeq0, aeq0 }
    26d0:	d7e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    26d5:	618ef4        	ae_lq56.i	aeq2, a14, -8
    26d8:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    26dd:	fc3c7dee3f 	{ ae_lq56.i	aeq3, a14, 24; ae_roundsq32asym	aeq0, aeq3 }
    26e2:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    26e7:	d7e3fdce1f 	{ ae_lq56.i	aeq2, a14, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    26ec:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    26f1:	fc3c7dee5f 	{ ae_lq56.i	aeq3, a14, 40; ae_roundsq32asym	aeq0, aeq3 }
    26f6:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    26fb:	d7e3fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2700:	d6e2fdce4f 	{ ae_lq56.i	aeq2, a14, 32; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    2705:	624814        	ae_sq32f.iu	aeq0, a8, 4
    2708:	631144        	ae_sq56s.i	aeq1, a1, 32
    270b:	614124        	ae_lq56.i	aeq1, a1, 16
    270e:	fc2c53744f 	{ or	a7, a4, a4; ae_roundsq32asym	aeq0, aeq1 }
    2713:	d6e2fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    2718:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    271d:	618e24        	ae_lq56.i	aeq2, a14, 16
    2720:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2725:	d7e2bda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    272a:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    272f:	fc347dce9f 	{ ae_lq56.i	aeq2, a14, -56; ae_roundsq32asym	aeq0, aeq2 }
    2734:	d6e2fa117f 	{ ae_sq56s.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    2739:	fe3c7de16f 	{ ae_lq56.i	aeq3, a1, 48; ae_roundsq32asym	aeq2, aeq3 }
    273e:	624814        	ae_sq32f.iu	aeq0, a8, 4
    2741:	d6e3fa1e9f 	{ ae_sq56s.i	aeq1, a14, -56; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    2746:	626814        	ae_sq32f.iu	aeq2, a8, 4
    2749:	618144        	ae_lq56.i	aeq2, a1, 32
    274c:	fc347a116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_roundsq32asym	aeq0, aeq2 }
    2751:	614174        	ae_lq56.i	aeq1, a1, 56
    2754:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2759:	614e94        	ae_lq56.i	aeq1, a14, -56
    275c:	61ce64        	ae_lq56.i	aeq3, a14, 48
    275f:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2764:	d7e3fdce7f 	{ ae_lq56.i	aeq2, a14, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2769:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    276e:	ff3c7d816f 	{ ae_lq56.i	aeq0, a1, 48; ae_roundsq32asym	aeq3, aeq3 }
    2773:	fc247da15f 	{ ae_lq56.i	aeq1, a1, 40; ae_roundsq32asym	aeq0, aeq0 }
    2778:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    277d:	01d1b2        	addmi	a11, a1, 0x100
    2780:	4661f2        	s32i	a15, a1, 0x118
    2783:	01d1f2        	addmi	a15, a1, 0x100
    2786:	fe3479f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq2, aeq2 }
    278b:	f64631        	l32r	a3, a4 (2d4 <fix_fft15_stage>)
    278e:	fd2c430fae 	{ addi	a10, a15, 48; ae_roundsq32asym	aeq1, aeq1 }
    2793:	626814        	ae_sq32f.iu	aeq2, a8, 4
    2796:	34cbb2        	addi	a11, a11, 52
    2799:	095d           	mov.n	a5, a9
    279b:	625814        	ae_sq32f.iu	aeq1, a8, 4
    279e:	4761a2        	s32i	a10, a1, 0x11c
    27a1:	0c4d           	mov.n	a4, a12
    27a3:	0003e0        	callx8	a3
    27a6:	302182        	l32i	a8, a1, 192
    27a9:	60c724        	ae_lq32f.i	aeq3, a7, 8
    27ac:	4121b2        	l32i	a11, a1, 0x104
    27af:	608864        	ae_lq32f.i	aeq2, a8, 24
    27b2:	632174        	ae_sq56s.i	aeq2, a1, 56
    27b5:	608764        	ae_lq32f.i	aeq2, a7, 24
    27b8:	432172        	l32i	a7, a1, 0x10c
    27bb:	78c1e2        	addi	a14, a1, 120
    27be:	604824        	ae_lq32f.i	aeq1, a8, 8
    27c1:	3f21c2        	l32i	a12, a1, 252
    27c4:	4021d2        	l32i	a13, a1, 0x100
    27c7:	039d           	mov.n	a9, a3
    27c9:	2e2132        	l32i	a3, a1, 184
    27cc:	631e94        	ae_sq56s.i	aeq1, a14, -56
    27cf:	633e34        	ae_sq56s.i	aeq3, a14, 24
    27d2:	632e74        	ae_sq56s.i	aeq2, a14, 56
    27d5:	60c624        	ae_lq32f.i	aeq3, a6, 8
    27d8:	604664        	ae_lq32f.i	aeq1, a6, 24
    27db:	608224        	ae_lq32f.i	aeq2, a2, 8
    27de:	633e14        	ae_sq56s.i	aeq3, a14, 8
    27e1:	631164        	ae_sq56s.i	aeq1, a1, 48
    27e4:	6047a4        	ae_lq32f.i	aeq1, a7, -24
    27e7:	632ef4        	ae_sq56s.i	aeq2, a14, -8
    27ea:	608b24        	ae_lq32f.i	aeq2, a11, 8
    27ed:	60c264        	ae_lq32f.i	aeq3, a2, 24
    27f0:	492162        	l32i	a6, a1, 0x124
    27f3:	633e64        	ae_sq56s.i	aeq3, a14, 48
    27f6:	631144        	ae_sq56s.i	aeq1, a1, 32
    27f9:	632154        	ae_sq56s.i	aeq2, a1, 40
    27fc:	60cc64        	ae_lq32f.i	aeq3, a12, 24
    27ff:	604c24        	ae_lq32f.i	aeq1, a12, 8
    2802:	608d64        	ae_lq32f.i	aeq2, a13, 24
    2805:	048d           	mov.n	a8, a4
    2807:	04ad           	mov.n	a10, a4
    2809:	01d142        	addmi	a4, a1, 0x100
    280c:	482172        	l32i	a7, a1, 0x120
    280f:	633ed4        	ae_sq56s.i	aeq3, a14, -24
    2812:	60cd24        	ae_lq32f.i	aeq3, a13, 8
    2815:	631e54        	ae_sq56s.i	aeq1, a14, 40
    2818:	632ea4        	ae_sq56s.i	aeq2, a14, -48
    281b:	80c422        	addi	a2, a4, -128
    281e:	604324        	ae_lq32f.i	aeq1, a3, 8
    2821:	608524        	ae_lq32f.i	aeq2, a5, 8
    2824:	4521b2        	l32i	a11, a1, 0x114
    2827:	631274        	ae_sq56s.i	aeq1, a2, 56
    282a:	633e44        	ae_sq56s.i	aeq3, a14, 32
    282d:	632484        	ae_sq56s.i	aeq2, a4, -64
    2830:	60c634        	ae_lq32f.i	aeq3, a6, 12
    2833:	608674        	ae_lq32f.i	aeq2, a6, 28
    2836:	600364        	ae_lq32f.i	aeq0, a3, 24
    2839:	5404b4        	ae_lp24x2.i	aep0, a4, -40
    283c:	d4e2b4212e 	{ l32i	a2, a1, 0x108; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    2841:	4621c2        	l32i	a12, a1, 0x118
    2844:	fc247a3eef 	{ ae_sq56s.i	aeq3, a14, -16; ae_roundsq32asym	aeq0, aeq0 }
    2849:	632e24        	ae_sq56s.i	aeq2, a14, 16
    284c:	60c734        	ae_lq32f.i	aeq3, a7, 12
    284f:	608774        	ae_lq32f.i	aeq2, a7, 28
    2852:	442162        	l32i	a6, a1, 0x110
    2855:	633114        	ae_sq56s.i	aeq3, a1, 8
    2858:	632134        	ae_sq56s.i	aeq2, a1, 24
    285b:	60cb24        	ae_lq32f.i	aeq3, a11, 8
    285e:	608b64        	ae_lq32f.i	aeq2, a11, 24
    2861:	6334a4        	ae_sq56s.i	aeq3, a4, -48
    2864:	632e04        	ae_sq56s.i	aeq2, a14, 0
    2867:	608c24        	ae_lq32f.i	aeq2, a12, 8
    286a:	60c264        	ae_lq32f.i	aeq3, a2, 24
    286d:	604564        	ae_lq32f.i	aeq1, a5, 24
    2870:	d4e3f9c80f 	{ ae_sq32f.iu	aeq0, a8, 0; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2875:	d7e3ba249f 	{ ae_sq56s.i	aeq2, a4, -56; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    287a:	fd2c7d622f 	{ ae_lq32f.i	aeq3, a2, 8; ae_roundsq32asym	aeq1, aeq1 }
    287f:	600664        	ae_lq32f.i	aeq0, a6, 24
    2882:	d5e2fa3ebf 	{ ae_sq56s.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq3, aeq0, aep0 }
    2887:	600624        	ae_lq32f.i	aeq0, a6, 8
    288a:	630ec4        	ae_sq56s.i	aeq0, a14, -32
    288d:	600c64        	ae_lq32f.i	aeq0, a12, 24
    2890:	630124        	ae_sq56s.i	aeq0, a1, 16
    2893:	610e94        	ae_lq56.i	aeq0, a14, -56
    2896:	d4e2b9d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    289b:	fd347dce3f 	{ ae_lq56.i	aeq2, a14, 24; ae_roundsq32asym	aeq1, aeq2 }
    28a0:	fd3c79d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq1, aeq3 }
    28a5:	d7e2bdee1f 	{ ae_lq56.i	aeq3, a14, 8; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    28aa:	fc2479d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq0, aeq0 }
    28af:	d7e3fdaeff 	{ ae_lq56.i	aeq1, a14, -8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    28b4:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    28b9:	d4e3fdcedf 	{ ae_lq56.i	aeq2, a14, -24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    28be:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    28c3:	d7e2bdeeaf 	{ ae_lq56.i	aeq3, a14, -48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    28c8:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    28cd:	d7e3fda4af 	{ ae_lq56.i	aeq1, a4, -48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    28d2:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    28d7:	d4e3fdc49f 	{ ae_lq56.i	aeq2, a4, -56; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    28dc:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    28e1:	d7e2bde17f 	{ ae_lq56.i	aeq3, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    28e6:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    28eb:	d7e3fdae7f 	{ ae_lq56.i	aeq1, a14, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    28f0:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    28f5:	d4e3fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    28fa:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    28ff:	d7e2bdee6f 	{ ae_lq56.i	aeq3, a14, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2904:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2909:	d7e3fda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    290e:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    2913:	d4e3fdc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2918:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    291d:	d7e2bdeeef 	{ ae_lq56.i	aeq3, a14, -16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2922:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2927:	d7e3fda11f 	{ ae_lq56.i	aeq1, a1, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    292c:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    2931:	d4e3fdce5f 	{ ae_lq56.i	aeq2, a14, 40; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2936:	01d1d2        	addmi	a13, a1, 0x100
    2939:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    293e:	d7e2bdee4f 	{ ae_lq56.i	aeq3, a14, 32; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2943:	d7e3c80d3e 	{ addi	a3, a13, -128; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2948:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    294d:	614374        	ae_lq56.i	aeq1, a3, 56
    2950:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    2955:	d4e3fdc48f 	{ ae_lq56.i	aeq2, a4, -64; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    295a:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    295f:	d7e2bdeebf 	{ ae_lq56.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2964:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    2969:	d7e3fdaecf 	{ ae_lq56.i	aeq1, a14, -32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    296e:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    2973:	d4e3fdce2f 	{ ae_lq56.i	aeq2, a14, 16; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2978:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    297d:	d7e2bde13f 	{ ae_lq56.i	aeq3, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    2982:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    2987:	fc2c7dae0f 	{ ae_lq56.i	aeq1, a14, 0; ae_roundsq32asym	aeq0, aeq1 }
    298c:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    2991:	fc347dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_roundsq32asym	aeq0, aeq2 }
    2996:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    299b:	ff3c73e1de 	{ l32i	a13, a1, 248; ae_roundsq32asym	aeq3, aeq3 }
    29a0:	02d1b2        	addmi	a11, a1, 0x200
    29a3:	fd2c79f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq1, aeq1 }
    29a8:	ff344b4bbe 	{ addi	a11, a11, -76; ae_roundsq32asym	aeq3, aeq2 }
    29ad:	625814        	ae_sq32f.iu	aeq1, a8, 4
    29b0:	0acd           	mov.n	a12, a10
    29b2:	627814        	ae_sq32f.iu	aeq3, a8, 4
    29b5:	0a4d           	mov.n	a4, a10
    29b7:	0009e0        	callx8	a9
    29ba:	4a2172        	l32i	a7, a1, 0x128
    29bd:	4b2182        	l32i	a8, a1, 0x12c
    29c0:	472152        	l32i	a5, a1, 0x11c
    29c3:	3d6152        	s32i	a5, a1, 244
    29c6:	f8c852        	addi	a5, a8, -8
    29c9:	3c6142        	s32i	a4, a1, 240
    29cc:	f8c742        	addi	a4, a7, -8
    29cf:	01d172        	addmi	a7, a1, 0x100
    29d2:	f8c632        	addi	a3, a6, -8
    29d5:	01d1f2        	addmi	a15, a1, 0x100
    29d8:	01d1c2        	addmi	a12, a1, 0x100
    29db:	01d1d2        	addmi	a13, a1, 0x100
    29de:	01d1e2        	addmi	a14, a1, 0x100
    29e1:	01d1a2        	addmi	a10, a1, 0x100
    29e4:	3a6142        	s32i	a4, a1, 232
    29e7:	396132        	s32i	a3, a1, 228
    29ea:	386152        	s32i	a5, a1, 224
    29ed:	f0cc32        	addi	a3, a12, -16
    29f0:	eccd42        	addi	a4, a13, -20
    29f3:	e8ce52        	addi	a5, a14, -24
    29f6:	e4cf62        	addi	a6, a15, -28
    29f9:	e0c772        	addi	a7, a7, -32
    29fc:	f5ab81        	l32r	a8, a8 (2a58 <fix_fft2_stage>)
    29ff:	f8c222        	addi	a2, a2, -8
    2a02:	090c           	movi.n	a9, 0
    2a04:	f4caa2        	addi	a10, a10, -12
    2a07:	03bd           	mov.n	a11, a3
    2a09:	04cd           	mov.n	a12, a4
    2a0b:	05dd           	mov.n	a13, a5
    2a0d:	06ed           	mov.n	a14, a6
    2a0f:	07fd           	mov.n	a15, a7
    2a11:	3b6122        	s32i	a2, a1, 236
    2a14:	3e61a2        	s32i	a10, a1, 248
    2a17:	0199           	s32i.n	a9, a1, 0
    2a19:	0008e0        	callx8	a8
    2a1c:	220c           	movi.n	a2, 2
    2a1e:	000706        	j	2a3e <fix_fft30+0x52e>

00002a21 <fix_fft30+0x511>:
    2a21:	3e21a2        	l32i	a10, a1, 248
    2a24:	03bd           	mov.n	a11, a3
    2a26:	04cd           	mov.n	a12, a4
    2a28:	05dd           	mov.n	a13, a5
    2a2a:	06ed           	mov.n	a14, a6
    2a2c:	07fd           	mov.n	a15, a7
    2a2e:	c4af82        	movi	a8, -60
    2a31:	0189           	s32i.n	a8, a1, 0
    2a33:	f59d81        	l32r	a8, a8 (2a58 <fix_fft2_stage>)
    2a36:	0008e0        	callx8	a8
    2a39:	221b           	addi.n	a2, a2, 1
    2a3b:	14b226        	beqi	a2, 16, 2a53 <fix_fft30+0x543>
    2a3e:	dfe207        	bbsi	a2, 0, 2a21 <fix_fft30+0x511>
    2a41:	3e21a2        	l32i	a10, a1, 248
    2a44:	03bd           	mov.n	a11, a3
    2a46:	05cd           	mov.n	a12, a5
    2a48:	04dd           	mov.n	a13, a4
    2a4a:	07ed           	mov.n	a14, a7
    2a4c:	06fd           	mov.n	a15, a6
    2a4e:	c83c           	movi.n	a8, 60
    2a50:	fff746        	j	2a31 <fix_fft30+0x521>

00002a53 <fix_fft30+0x543>:
    2a53:	f01d           	retw.n

00002a55 <fix_fft30+0x545>:
    2a55:	000000                                        ...

00002a58 <fix_fft2_stage>:
    2a58:	004136        	entry	a1, 32
    2a5b:	8188           	l32i.n	a8, a1, 32
    2a5d:	0298           	l32i.n	a9, a2, 0
    2a5f:	603984        	ae_lq32f.xu	aeq0, a9, a8
    2a62:	0299           	s32i.n	a9, a2, 0
    2a64:	0398           	l32i.n	a9, a3, 0
    2a66:	350074        	ae_sraiq56	aeq0, aeq0, 1
    2a69:	fc247c298f 	{ ae_lq32f.xu	aeq1, a9, a8; ae_roundsq32asym	aeq0, aeq0 }
    2a6e:	0399           	s32i.n	a9, a3, 0
    2a70:	355074        	ae_sraiq56	aeq1, aeq1, 1
    2a73:	fd2c7004fe 	{ l32i	a15, a4, 0; ae_roundsq32asym	aeq1, aeq1 }
    2a78:	0189c4        	ae_addq56	aeq2, aeq0, aeq1
    2a7b:	f826f9ef2f 	{ ae_sq32f.iu	aeq2, a15, 8; ae_subq56	aeq0, aeq0, aeq1 }
    2a80:	04f9           	s32i.n	a15, a4, 0
    2a82:	0548           	l32i.n	a4, a5, 0
    2a84:	624424        	ae_sq32f.iu	aeq0, a4, 8
    2a87:	0549           	s32i.n	a4, a5, 0
    2a89:	0248           	l32i.n	a4, a2, 0
    2a8b:	601414        	ae_lq32f.iu	aeq0, a4, 4
    2a8e:	0249           	s32i.n	a4, a2, 0
    2a90:	0328           	l32i.n	a2, a3, 0
    2a92:	350074        	ae_sraiq56	aeq0, aeq0, 1
    2a95:	fc247d521f 	{ ae_lq32f.iu	aeq2, a2, 4; ae_roundsq32asym	aeq0, aeq0 }
    2a9a:	0329           	s32i.n	a2, a3, 0
    2a9c:	356074        	ae_sraiq56	aeq1, aeq2, 1
    2a9f:	fd2c70062e 	{ l32i	a2, a6, 0; ae_roundsq32asym	aeq1, aeq1 }
    2aa4:	01c9c4        	ae_addq56	aeq3, aeq0, aeq1
    2aa7:	f826f9f22f 	{ ae_sq32f.iu	aeq3, a2, 8; ae_subq56	aeq0, aeq0, aeq1 }
    2aac:	0629           	s32i.n	a2, a6, 0
    2aae:	0728           	l32i.n	a2, a7, 0
    2ab0:	624224        	ae_sq32f.iu	aeq0, a2, 8
    2ab3:	0729           	s32i.n	a2, a7, 0
    2ab5:	f01d           	retw.n

00002ab7 <fix_fft2_stage+0x5f>:
	...

00002ab8 <__do_global_ctors_aux>:
    2ab8:	004136        	entry	a1, 32
    2abb:	f57c31        	l32r	a3, ac (2ec8 <__CTOR_END__>)
    2abe:	fcc322        	addi	a2, a3, -4
    2ac1:	0228           	l32i.n	a2, a2, 0
    2ac3:	f8c332        	addi	a3, a3, -8
    2ac6:	0a0226        	beqi	a2, -1, 2ad4 <__do_global_ctors_aux+0x1c>

00002ac9 <__do_global_ctors_aux+0x11>:
    2ac9:	0002e0        	callx8	a2
    2acc:	0328           	l32i.n	a2, a3, 0
    2ace:	fcc332        	addi	a3, a3, -4
    2ad1:	f40266        	bnei	a2, -1, 2ac9 <__do_global_ctors_aux+0x11>
    2ad4:	f01d           	retw.n

00002ad6 <__do_global_ctors_aux+0x1e>:
	...

00002ad8 <LC3Plus_lc3_scratch_init>:
    2ad8:	004136        	entry	a1, 32
    2adb:	1f0c           	movi.n	a15, 1
    2add:	401400        	ssl	a4
    2ae0:	a14f00        	sll	a4, a15
    2ae3:	026d           	mov.n	a6, a2
    2ae5:	740b           	addi.n	a7, a4, -1
    2ae7:	0f0277        	bnone	a2, a7, 2afa <LC3Plus_lc3_scratch_init+0x22>
    2aea:	102760        	and	a2, a7, a6
    2aed:	c08420        	sub	a8, a4, a2
    2af0:	020c           	movi.n	a2, 0
    2af2:	3a3387        	bltu	a3, a8, 2b30 <LC3Plus_lc3_scratch_init+0x58>
    2af5:	686a           	add.n	a6, a8, a6
    2af7:	c03380        	sub	a3, a3, a8

00002afa <LC3Plus_lc3_scratch_init+0x22>:
    2afa:	c81c           	movi.n	a8, 28
    2afc:	109780        	and	a9, a7, a8
    2aff:	c07490        	sub	a7, a4, a9
    2b02:	1cc772        	addi	a7, a7, 28
    2b05:	020c           	movi.n	a2, 0
    2b07:	837890        	moveqz	a7, a8, a9
    2b0a:	6659           	s32i.n	a5, a6, 24
    2b0c:	5629           	s32i.n	a2, a6, 20
    2b0e:	4629           	s32i.n	a2, a6, 16
    2b10:	1c3377        	bltu	a3, a7, 2b30 <LC3Plus_lc3_scratch_init+0x58>
    2b13:	258c           	beqz.n	a5, 2b19 <LC3Plus_lc3_scratch_init+0x41>
    2b15:	5679           	s32i.n	a7, a6, 20
    2b17:	4679           	s32i.n	a7, a6, 16
    2b19:	f41b           	addi.n	a15, a4, 1
    2b1b:	603040        	neg	a3, a4
    2b1e:	267a           	add.n	a2, a6, a7
    2b20:	0e0c           	movi.n	a14, 0
    2b22:	103f30        	and	a3, a15, a3
    2b25:	0629           	s32i.n	a2, a6, 0
    2b27:	062d           	mov.n	a2, a6
    2b29:	2649           	s32i.n	a4, a6, 8
    2b2b:	0256e2        	s16i	a14, a6, 4
    2b2e:	3639           	s32i.n	a3, a6, 12
    2b30:	f01d           	retw.n

00002b32 <LC3Plus_lc3_scratch_init+0x5a>:
	...

00002b34 <LC3Plus_lc3_scratch_push>:
    2b34:	004136        	entry	a1, 32
    2b37:	024d           	mov.n	a4, a2
    2b39:	fe7c           	movi.n	a14, -1
    2b3b:	f420e0        	extui	a2, a14, 0, 16
    2b3e:	2458           	l32i.n	a5, a4, 8
    2b40:	0468           	l32i.n	a6, a4, 0
    2b42:	021472        	l16ui	a7, a4, 4
    2b45:	232a           	add.n	a2, a3, a2
    2b47:	3438           	l32i.n	a3, a4, 12
    2b49:	6488           	l32i.n	a8, a4, 24
    2b4b:	252a           	add.n	a2, a5, a2
    2b4d:	605050        	neg	a5, a5
    2b50:	f67a           	add.n	a15, a6, a7
    2b52:	105250        	and	a5, a2, a5
    2b55:	2f3a           	add.n	a2, a15, a3
    2b57:	6f7d           	ae_s16i.n	a7, a15, 0
    2b59:	025452        	s16i	a5, a4, 4
    2b5c:	0429           	s32i.n	a2, a4, 0
    2b5e:	f88c           	beqz.n	a8, 2b71 <LC3Plus_lc3_scratch_push+0x3d>
    2b60:	5468           	l32i.n	a6, a4, 20
    2b62:	955d           	ae_zext16	a5, a5
    2b64:	44f8           	l32i.n	a15, a4, 16
    2b66:	335a           	add.n	a3, a3, a5
    2b68:	336a           	add.n	a3, a3, a6
    2b6a:	5439           	s32i.n	a3, a4, 20
    2b6c:	7333f0        	maxu	a3, a3, a15
    2b6f:	4439           	s32i.n	a3, a4, 16

00002b71 <LC3Plus_lc3_scratch_push+0x3d>:
    2b71:	f01d           	retw.n

00002b73 <LC3Plus_lc3_scratch_push+0x3f>:
	...

00002b74 <LC3Plus_lc3_scratch_pop>:
    2b74:	004136        	entry	a1, 32
    2b77:	023d           	mov.n	a3, a2
    2b79:	02f8           	l32i.n	a15, a2, 0
    2b7b:	3248           	l32i.n	a4, a2, 12
    2b7d:	6258           	l32i.n	a5, a2, 24
    2b7f:	c02f40        	sub	a2, a15, a4
    2b82:	a58c           	beqz.n	a5, 2b90 <LC3Plus_lc3_scratch_pop+0x1c>
    2b84:	021352        	l16ui	a5, a3, 4
    2b87:	5368           	l32i.n	a6, a3, 20
    2b89:	445a           	add.n	a4, a4, a5
    2b8b:	c04640        	sub	a4, a6, a4
    2b8e:	5349           	s32i.n	a4, a3, 20

00002b90 <LC3Plus_lc3_scratch_pop+0x1c>:
    2b90:	424d           	ae_l16ui.n	a4, a2, 0
    2b92:	025342        	s16i	a4, a3, 4
    2b95:	c04240        	sub	a4, a2, a4
    2b98:	020c           	movi.n	a2, 0
    2b9a:	0349           	s32i.n	a4, a3, 0
    2b9c:	f01d           	retw.n

00002b9e <LC3Plus_lc3_scratch_pop+0x2a>:
	...

00002ba0 <_fini>:
    2ba0:	008136        	entry	a1, 64
    2ba3:	f54381        	l32r	a8, b0 (cc <__do_global_dtors_aux>)
    2ba6:	f03d           	nop.n
    2ba8:	0008e0        	callx8	a8

00002bab <_fini+0xb>:
    2bab:	f01d           	retw.n
