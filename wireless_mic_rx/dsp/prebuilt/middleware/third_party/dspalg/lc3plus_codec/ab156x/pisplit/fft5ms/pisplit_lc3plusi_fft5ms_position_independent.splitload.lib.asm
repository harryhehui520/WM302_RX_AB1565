
Build/fft5ms/pisplit_lc3plusi_fft5ms_position_independent.splitload.lib:     file format elf32-xtensa-le


Disassembly of section .text:

00000000 <_init-0x90>:
       0:	000000dc 00001d70 0000216c 00000000     ....p...l!......
      10:	00002130 00000000 00002154 000021e8     0!......T!...!..
      20:	00002198 00000148 000021ab 00000c5c     .!..H....!..\...
      30:	000021b7 0000133c 000021c7 000015bc     .!..<....!......
      40:	000021d7 000017c8 00002180 0000247c     .!.......!..|$..
      50:	b0000001 478dde64 d18053ce 9d839db0     ....d..G.S......
      60:	79bc3854 0000015c 91261468 00001dec     T8.y\...h.&.....
      70:	5a82799a a57d8666 00001e2c 00001339     .y.Zf.}.,...9...
      80:	000002a4 00001d10 00002138 000000a8     ........8!......

00000090 <_init>:
      90:	008136        	entry	a1, 64
      93:	ffdb81        	l32r	a8, 0 (dc <frame_dummy>)
      96:	f03d           	nop.n
      98:	0008e0        	callx8	a8
      9b:	ffda81        	l32r	a8, 4 (1d70 <__do_global_ctors_aux>)
      9e:	f03d           	nop.n
      a0:	0008e0        	callx8	a8
      a3:	f01d           	retw.n

000000a5 <_init+0x15>:
      a5:	000000                                        ...

000000a8 <__do_global_dtors_aux>:
      a8:	004136        	entry	a1, 32
      ab:	ffd721        	l32r	a2, 8 (216c <__do_global_dtors_aux.completed>)
      ae:	000232        	l8ui	a3, a2, 0
      b1:	23ec           	bnez.n	a3, d7 <__do_global_dtors_aux+0x2f>

000000b3 <__do_global_dtors_aux+0xb>:
      b3:	1248           	l32i.n	a4, a2, 4
      b5:	0438           	l32i.n	a3, a4, 0
      b7:	444b           	addi.n	a4, a4, 4
      b9:	738c           	beqz.n	a3, c4 <__do_global_dtors_aux+0x1c>
      bb:	1249           	s32i.n	a4, a2, 4
      bd:	0003e0        	callx8	a3
      c0:	fffbc6        	j	b3 <__do_global_dtors_aux+0xb>

000000c3 <__do_global_dtors_aux+0x1b>:
	...

000000c4 <__do_global_dtors_aux+0x1c>:
      c4:	ffd231        	l32r	a3, c (0 <_text_start>)
      c7:	ffd2a1        	l32r	a10, 10 (2130 <__FRAME_END__>)
      ca:	438c           	beqz.n	a3, d2 <__do_global_dtors_aux+0x2a>
      cc:	ffd081        	l32r	a8, c (0 <_text_start>)
      cf:	0008e0        	callx8	a8
      d2:	130c           	movi.n	a3, 1
      d4:	004232        	s8i	a3, a2, 0
      d7:	f01d           	retw.n

000000d9 <__do_global_dtors_aux+0x31>:
      d9:	000000                                        ...

000000dc <frame_dummy>:
      dc:	004136        	entry	a1, 32
      df:	ffcd21        	l32r	a2, 14 (0 <_text_start>)
      e2:	ffcba1        	l32r	a10, 10 (2130 <__FRAME_END__>)
      e5:	ffccb1        	l32r	a11, 18 (2154 <frame_dummy.object>)
      e8:	428c           	beqz.n	a2, f0 <frame_dummy+0x14>
      ea:	ffca81        	l32r	a8, 14 (0 <_text_start>)
      ed:	0008e0        	callx8	a8

000000f0 <frame_dummy+0x14>:
      f0:	f01d           	retw.n

000000f2 <frame_dummy+0x16>:
	...

000000f4 <_start>:
      f4:	004136        	entry	a1, 32
      f7:	ffc941        	l32r	a4, 1c (21e8 <printf_ptr>)
      fa:	0228           	l32i.n	a2, a2, 0
      fc:	ffc9a1        	l32r	a10, 20 (2198 <export_parameter_array+0x18>)
      ff:	ffc9b1        	l32r	a11, 24 (148 <fix_fft_Init>)
     102:	0429           	s32i.n	a2, a4, 0
     104:	0002e0        	callx8	a2
     107:	0428           	l32i.n	a2, a4, 0
     109:	ffc7a1        	l32r	a10, 28 (21ab <export_parameter_array+0x2b>)
     10c:	ffc8b1        	l32r	a11, 2c (c5c <FFT8N>)
     10f:	0002e0        	callx8	a2
     112:	0428           	l32i.n	a2, a4, 0
     114:	ffc7a1        	l32r	a10, 30 (21b7 <export_parameter_array+0x37>)
     117:	ffc7b1        	l32r	a11, 34 (133c <fix_fft10>)
     11a:	0002e0        	callx8	a2
     11d:	0428           	l32i.n	a2, a4, 0
     11f:	ffc6a1        	l32r	a10, 38 (21c7 <export_parameter_array+0x47>)
     122:	ffc6b1        	l32r	a11, 3c (15bc <fix_fft15>)
     125:	0002e0        	callx8	a2
     128:	ffc621        	l32r	a2, 40 (21d7 <export_parameter_array+0x57>)
     12b:	ffc631        	l32r	a3, 44 (17c8 <fix_fft30>)
     12e:	0458           	l32i.n	a5, a4, 0
     130:	02ad           	mov.n	a10, a2
     132:	03bd           	mov.n	a11, a3
     134:	0005e0        	callx8	a5
     137:	0448           	l32i.n	a4, a4, 0
     139:	02ad           	mov.n	a10, a2
     13b:	03bd           	mov.n	a11, a3
     13d:	0004e0        	callx8	a4
     140:	ffc221        	l32r	a2, 48 (2180 <export_parameter_array>)
     143:	f01d           	retw.n

00000145 <_start+0x51>:
     145:	000000                                        ...

00000148 <fix_fft_Init>:
     148:	004136        	entry	a1, 32
     14b:	f8a032        	movi	a3, 248
     14e:	ffbf41        	l32r	a4, 4c (247c <LC3Plus_RotVector_40_32>)
     151:	55d332        	addmi	a3, a3, 0x5500
     154:	223a           	add.n	a2, a2, a3
     156:	0429           	s32i.n	a2, a4, 0
     158:	f01d           	retw.n

0000015a <fix_fft_Init+0x12>:
	...

0000015c <fix_fft5_stage>:
     15c:	008136        	entry	a1, 64
     15f:	2468           	l32i.n	a6, a4, 8
     161:	8478           	l32i.n	a7, a4, 32
     163:	4488           	l32i.n	a8, a4, 16
     165:	6498           	l32i.n	a9, a4, 24
     167:	025d           	mov.n	a5, a2
     169:	ffb921        	l32r	a2, 50 (b0000001 <_end+0xafffdb59>)
     16c:	04c8           	l32i.n	a12, a4, 0
     16e:	7139           	s32i.n	a3, a1, 28
     170:	d76a           	add.n	a13, a7, a6
     172:	c0a670        	sub	a10, a6, a7
     175:	398a           	add.n	a3, a9, a8
     177:	ffb761        	l32r	a6, 54 (478dde64 <_end+0x478db9bc>)
     17a:	fd3a           	add.n	a15, a13, a3
     17c:	ffb771        	l32r	a7, 58 (d18053ce <_end+0xd1802f26>)
     17f:	c0b890        	sub	a11, a8, a9
     182:	9fca           	add.n	a9, a15, a12
     184:	b2ef20        	mulsh	a14, a15, a2
     187:	82ff20        	mull	a15, a15, a2
     18a:	c02d30        	sub	a2, a13, a3
     18d:	823260        	mull	a3, a2, a6
     190:	b28260        	mulsh	a8, a2, a6
     193:	82db70        	mull	a13, a11, a7
     196:	05cf30        	extui	a12, a3, 31, 1
     199:	b22b70        	mulsh	a2, a11, a7
     19c:	9088c0        	addx2	a8, a8, a12
     19f:	05cfd0        	extui	a12, a13, 31, 1
     1a2:	90d2c0        	addx2	a13, a2, a12
     1a5:	ffadc1        	l32r	a12, 5c (9d839db0 <_end+0x9d837908>)
     1a8:	2aba           	add.n	a2, a10, a11
     1aa:	0599           	s32i.n	a9, a5, 0
     1ac:	823ac0        	mull	a3, a10, a12
     1af:	b2aac0        	mulsh	a10, a10, a12
     1b2:	05bf30        	extui	a11, a3, 31, 1
     1b5:	11bbf0        	slli	a11, a11, 1
     1b8:	a0aab0        	addx4	a10, a10, a11
     1bb:	ffa9b1        	l32r	a11, 60 (79bc3854 <_end+0x79bc13ac>)
     1be:	8232b0        	mull	a3, a2, a11
     1c1:	b222b0        	mulsh	a2, a2, a11
     1c4:	053f30        	extui	a3, a3, 31, 1
     1c7:	902230        	addx2	a2, a2, a3
     1ca:	3a2a           	add.n	a3, a10, a2
     1cc:	05aff0        	extui	a10, a15, 31, 1
     1cf:	d2da           	add.n	a13, a2, a13
     1d1:	112af0        	slli	a2, a10, 1
     1d4:	360d34        	ae_cvtq48a32s	aeq0, a13
     1d7:	a0ee20        	addx4	a14, a14, a2
     1da:	05ad           	mov.n	a10, a5
     1dc:	54f8           	l32i.n	a15, a4, 20
     1de:	7428           	l32i.n	a2, a4, 28
     1e0:	34d8           	l32i.n	a13, a4, 12
     1e2:	9458           	l32i.n	a5, a4, 36
     1e4:	6139           	s32i.n	a3, a1, 24
     1e6:	3e9a           	add.n	a3, a14, a9
     1e8:	e2fa           	add.n	a14, a2, a15
     1ea:	c02f20        	sub	a2, a15, a2
     1ed:	f5da           	add.n	a15, a5, a13
     1ef:	c09d50        	sub	a9, a13, a5
     1f2:	b2d9c0        	mulsh	a13, a9, a12
     1f5:	82c9c0        	mull	a12, a9, a12
     1f8:	b25270        	mulsh	a5, a2, a7
     1fb:	827270        	mull	a7, a2, a7
     1fe:	292a           	add.n	a2, a9, a2
     200:	c09fe0        	sub	a9, a15, a14
     203:	efea           	add.n	a14, a15, a14
     205:	c0f380        	sub	a15, a3, a8
     208:	338a           	add.n	a3, a3, a8
     20a:	364334        	ae_cvtq48a32s	aeq1, a3
     20d:	b23960        	mulsh	a3, a9, a6
     210:	826960        	mull	a6, a9, a6
     213:	b292b0        	mulsh	a9, a2, a11
     216:	8222b0        	mull	a2, a2, a11
     219:	ff8d81        	l32r	a8, 50 (b0000001 <_end+0xafffdb59>)
     21c:	14b8           	l32i.n	a11, a4, 4
     21e:	057f70        	extui	a7, a7, 31, 1
     221:	052f20        	extui	a2, a2, 31, 1
     224:	905570        	addx2	a5, a5, a7
     227:	7178           	l32i.n	a7, a1, 28
     229:	902920        	addx2	a2, a9, a2
     22c:	829e80        	mull	a9, a14, a8
     22f:	525a           	add.n	a5, a2, a5
     231:	4eba           	add.n	a4, a14, a11
     233:	05cfc0        	extui	a12, a12, 31, 1
     236:	368534        	ae_cvtq48a32s	aeq2, a5
     239:	11bcf0        	slli	a11, a12, 1
     23c:	fbea14074f 	{ s32i.n	a4, a7, 0; ae_addq56	aeq3, aeq1, aeq2 }
     241:	578b           	addi.n	a5, a7, 8
     243:	7a8b           	addi.n	a7, a10, 8
     245:	b2ae80        	mulsh	a10, a14, a8
     248:	059f90        	extui	a9, a9, 31, 1
     24b:	a0bdb0        	addx4	a11, a13, a11
     24e:	056f60        	extui	a6, a6, 31, 1
     251:	11d9f0        	slli	a13, a9, 1
     254:	f9aad1336f 	{ addx2	a3, a3, a6; ae_subq56	aeq1, aeq1, aeq2 }
     259:	a06ad0        	addx4	a6, a10, a13
     25c:	2b2a           	add.n	a2, a11, a2
     25e:	627704        	ae_sq32f.iu	aeq3, a7, 0
     261:	e64a           	add.n	a14, a6, a4
     263:	630124        	ae_sq56s.i	aeq0, a1, 16
     266:	36cf34        	ae_cvtq48a32s	aeq3, a15
     269:	360234        	ae_cvtq48a32s	aeq0, a2
     26c:	fa3af9d76f 	{ ae_sq32f.iu	aeq1, a7, 24; ae_subq56	aeq2, aeq3, aeq0 }
     271:	4e3a           	add.n	a4, a14, a3
     273:	f87a39e7cf 	{ ae_sq32f.iu	aeq2, a7, -16; ae_addq56	aeq0, aeq3, aeq0 }
     278:	364434        	ae_cvtq48a32s	aeq1, a4
     27b:	618124        	ae_lq56.i	aeq2, a1, 16
     27e:	fbaaf061fe 	{ l32i	a15, a1, 24; ae_subq56	aeq3, aeq1, aeq2 }
     283:	f9ea152e3f 	{ sub	a2, a14, a3; ae_addq56	aeq1, aeq1, aeq2 }
     288:	624724        	ae_sq32f.iu	aeq0, a7, 8
     28b:	627504        	ae_sq32f.iu	aeq3, a5, 0
     28e:	360f34        	ae_cvtq48a32s	aeq0, a15
     291:	368234        	ae_cvtq48a32s	aeq2, a2
     294:	fb7239d56f 	{ ae_sq32f.iu	aeq1, a5, 24; ae_addq56	aeq3, aeq2, aeq0 }
     299:	f832f9f5cf 	{ ae_sq32f.iu	aeq3, a5, -16; ae_subq56	aeq0, aeq2, aeq0 }
     29e:	624524        	ae_sq32f.iu	aeq0, a5, 8
     2a1:	f01d           	retw.n

000002a3 <fix_fft5_stage+0x147>:
	...

000002a4 <fix_fft15_stage>:
     2a4:	00c136        	entry	a1, 96
     2a7:	ff6f71        	l32r	a7, 64 (15c <fix_fft5_stage>)
     2aa:	b44b           	addi.n	a11, a4, 4
     2ac:	04ad           	mov.n	a10, a4
     2ae:	04cd           	mov.n	a12, a4
     2b0:	28c462        	addi	a6, a4, 40
     2b3:	50c452        	addi	a5, a4, 80
     2b6:	0007e0        	callx8	a7
     2b9:	2cc4b2        	addi	a11, a4, 44
     2bc:	06ad           	mov.n	a10, a6
     2be:	06cd           	mov.n	a12, a6
     2c0:	0007e0        	callx8	a7
     2c3:	54c4b2        	addi	a11, a4, 84
     2c6:	05ad           	mov.n	a10, a5
     2c8:	05cd           	mov.n	a12, a5
     2ca:	0007e0        	callx8	a7
     2cd:	672c           	movi.n	a7, 38
     2cf:	91d772        	addmi	a7, a7, 0xffff9100
     2d2:	ff6581        	l32r	a8, 68 (91261468 <_end+0x9125efc0>)
     2d5:	600604        	ae_lq32f.i	aeq0, a6, 0
     2d8:	604504        	ae_lq32f.i	aeq1, a5, 0
     2db:	fa6603c19e 	{ addi	a9, a1, 60; ae_addq56	aeq2, aeq0, aeq1 }
     2e0:	300874        	ae_cvtp24a16x2.ll	aep0, a8, a7
     2e3:	630144        	ae_sq56s.i	aeq0, a1, 32
     2e6:	460904        	ae_sp16x2f.i	aep0, a9, 0
     2e9:	352074        	ae_sraiq56	aeq0, aeq2, 1
     2ec:	60c404        	ae_lq32f.i	aeq3, a4, 0
     2ef:	fafa3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     2f4:	610144        	ae_lq56.i	aeq0, a1, 32
     2f7:	f826ff2bef 	{ ae_trunca32q48	a11, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     2fc:	440904        	ae_lp16x2f.i	aep0, a9, 0
     2ff:	d462fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     304:	fe345402bf 	{ s32i.n	a11, a2, 0; ae_roundsq32asym	aeq2, aeq2 }
     309:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     30e:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     313:	608614        	ae_lq32f.i	aeq2, a6, 4
     316:	fd6c7d651f 	{ ae_lq32f.i	aeq3, a5, 4; ae_truncq32	aeq1, aeq1 }
     31b:	012bc4        	ae_addq56	aeq0, aeq2, aeq3
     31e:	fab6fb00df 	{ ae_sraiq56	aeq3, aeq0, 1; ae_subq56	aeq2, aeq2, aeq3 }
     323:	633134        	ae_sq56s.i	aeq3, a1, 24
     326:	632154        	ae_sq56s.i	aeq2, a1, 40
     329:	608414        	ae_lq32f.i	aeq2, a4, 4
     32c:	f8723de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_addq56	aeq0, aeq2, aeq0 }
     331:	fc3c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_roundsq32asym	aeq0, aeq3 }
     336:	61c154        	ae_lq56.i	aeq3, a1, 40
     339:	d663ba016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_mulfq32sp16u.h	aeq0, aeq3, aep0 }
     33e:	630134        	ae_sq56s.i	aeq0, a1, 24
     341:	610164        	ae_lq56.i	aeq0, a1, 48
     344:	f832fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_subq56	aeq0, aeq2, aeq0 }
     349:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     34c:	f783bde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq3, aep0 }
     351:	fb663f3cef 	{ ae_trunca32q48	a12, aeq3; ae_addq56	aeq3, aeq0, aeq1 }
     356:	f826ff3def 	{ ae_trunca32q48	a13, aeq3; ae_subq56	aeq0, aeq0, aeq1 }
     35b:	fe747f0eef 	{ ae_trunca32q48	a14, aeq0; ae_truncq32	aeq2, aeq2 }
     360:	610124        	ae_lq56.i	aeq0, a1, 16
     363:	fba2d403cf 	{ s32i.n	a12, a3, 0; ae_subq56	aeq3, aeq0, aeq2 }
     368:	f9e23f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     36d:	369a04        	ae_trunca32q48	a10, aeq1
     370:	1462f2        	s32i	a15, a2, 80
     373:	a2a9           	s32i.n	a10, a2, 40
     375:	1463d2        	s32i	a13, a3, 80
     378:	a3e9           	s32i.n	a14, a3, 40
     37a:	60c624        	ae_lq32f.i	aeq3, a6, 8
     37d:	604524        	ae_lq32f.i	aeq1, a5, 8
     380:	f87e3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     385:	60c424        	ae_lq32f.i	aeq3, a4, 8
     388:	fa7a3b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_addq56	aeq2, aeq3, aeq0 }
     38d:	fc247a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     392:	618144        	ae_lq56.i	aeq2, a1, 32
     395:	f936fdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq1, aeq2, aeq1 }
     39a:	d563bf2bef 	{ ae_trunca32q48	a11, aeq2; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     39f:	630124        	ae_sq56s.i	aeq0, a1, 16
     3a2:	352434        	ae_sraiq56	aeq0, aeq2, 16
     3a5:	f483bdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     3aa:	fabad4c2bf 	{ s32i.n	a11, a2, 48; ae_subq56	aeq2, aeq3, aeq2 }
     3af:	632124        	ae_sq56s.i	aeq2, a1, 16
     3b2:	608634        	ae_lq32f.i	aeq2, a6, 12
     3b5:	604534        	ae_lq32f.i	aeq1, a5, 12
     3b8:	fb763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq3, aeq2, aeq1 }
     3bd:	fa36fd043f 	{ ae_lq32f.i	aeq0, a4, 12; ae_subq56	aeq2, aeq2, aeq1 }
     3c2:	fbe63b305f 	{ ae_sraiq56	aeq1, aeq3, 1; ae_addq56	aeq3, aeq0, aeq3 }
     3c7:	d762fa314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     3cc:	631134        	ae_sq56s.i	aeq1, a1, 24
     3cf:	614134        	ae_lq56.i	aeq1, a1, 24
     3d2:	fd2c7b34cf 	{ ae_sraiq56	aeq3, aeq3, 16; ae_roundsq32asym	aeq1, aeq1 }
     3d7:	f782fdc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     3dc:	010dc4        	ae_subq56	aeq0, aeq0, aeq1
     3df:	fd747dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_truncq32	aeq1, aeq2 }
     3e4:	fa663f2cef 	{ ae_trunca32q48	a12, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     3e9:	f826ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     3ee:	fd7c7dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_truncq32	aeq1, aeq3 }
     3f3:	fb36ff0eef 	{ ae_trunca32q48	a14, aeq0; ae_subq56	aeq3, aeq2, aeq1 }
     3f8:	f9763f3fef 	{ ae_trunca32q48	a15, aeq3; ae_addq56	aeq1, aeq2, aeq1 }
     3fd:	369a04        	ae_trunca32q48	a10, aeq1
     400:	c3c9           	s32i.n	a12, a3, 48
     402:	22f9           	s32i.n	a15, a2, 8
     404:	1662a2        	s32i	a10, a2, 88
     407:	23d9           	s32i.n	a13, a3, 8
     409:	1663e2        	s32i	a14, a3, 88
     40c:	600644        	ae_lq32f.i	aeq0, a6, 16
     40f:	604544        	ae_lq32f.i	aeq1, a5, 16
     412:	fa663d644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_addq56	aeq2, aeq0, aeq1 }
     417:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     41c:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     421:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     426:	36ab04        	ae_trunca32q48	a11, aeq2
     429:	618144        	ae_lq56.i	aeq2, a1, 32
     42c:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     431:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     436:	1862b2        	s32i	a11, a2, 96
     439:	f482fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     43e:	608654        	ae_lq32f.i	aeq2, a6, 20
     441:	600554        	ae_lq32f.i	aeq0, a5, 20
     444:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     447:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     44c:	632134        	ae_sq56s.i	aeq2, a1, 24
     44f:	630124        	ae_sq56s.i	aeq0, a1, 16
     452:	600454        	ae_lq32f.i	aeq0, a4, 20
     455:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     45a:	ff347a315f 	{ ae_sq56s.i	aeq3, a1, 40; ae_roundsq32asym	aeq3, aeq2 }
     45f:	618124        	ae_lq56.i	aeq2, a1, 16
     462:	0382a4        	ae_mulfq32sp16u.h	aeq2, aeq2, aep0
     465:	faa6fa216f 	{ ae_sq56s.i	aeq2, a1, 48; ae_subq56	aeq2, aeq0, aeq3 }
     46a:	61c164        	ae_lq56.i	aeq3, a1, 48
     46d:	353434        	ae_sraiq56	aeq0, aeq3, 16
     470:	61c124        	ae_lq56.i	aeq3, a1, 16
     473:	f683ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulafq32sp16s.l	aeq0, aeq3, aep0 }
     478:	ff6c7da15f 	{ ae_lq56.i	aeq1, a1, 40; ae_truncq32	aeq3, aeq1 }
     47d:	faf63f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq2, aeq2, aeq3 }
     482:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     487:	fa26ff2def 	{ ae_trunca32q48	a13, aeq2; ae_subq56	aeq2, aeq0, aeq1 }
     48c:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     491:	618134        	ae_lq56.i	aeq2, a1, 24
     494:	f8b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq0, aeq2, aeq3 }
     499:	368904        	ae_trunca32q48	a9, aeq0
     49c:	1863c2        	s32i	a12, a3, 96
     49f:	e2e9           	s32i.n	a14, a2, 56
     4a1:	42f9           	s32i.n	a15, a2, 16
     4a3:	e3d9           	s32i.n	a13, a3, 56
     4a5:	4399           	s32i.n	a9, a3, 16
     4a7:	60c664        	ae_lq32f.i	aeq3, a6, 24
     4aa:	608564        	ae_lq32f.i	aeq2, a5, 24
     4ad:	f9fa3a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_addq56	aeq1, aeq3, aeq2 }
     4b2:	60c464        	ae_lq32f.i	aeq3, a4, 24
     4b5:	f87e0704de 	{ addi	a13, a4, 112; ae_addq56	aeq0, aeq3, aeq1 }
     4ba:	630124        	ae_sq56s.i	aeq0, a1, 16
     4bd:	610144        	ae_lq56.i	aeq0, a1, 32
     4c0:	010ec4        	ae_subq56	aeq0, aeq0, aeq2
     4c3:	630134        	ae_sq56s.i	aeq0, a1, 24
     4c6:	351074        	ae_sraiq56	aeq0, aeq1, 1
     4c9:	fc247da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     4ce:	f83aff1aef 	{ ae_trunca32q48	a10, aeq1; ae_subq56	aeq0, aeq3, aeq0 }
     4d3:	614134        	ae_lq56.i	aeq1, a1, 24
     4d6:	d5639462af 	{ s32i.n	a10, a2, 24; ae_mulfq32sp16u.h	aeq2, aeq1, aep0 }
     4db:	60c674        	ae_lq32f.i	aeq3, a6, 28
     4de:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     4e1:	f583bd257f 	{ ae_lq32f.i	aeq1, a5, 28; ae_mulafq32sp16s.l	aeq2, aeq1, aep0 }
     4e6:	f87e3a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_addq56	aeq0, aeq3, aeq1 }
     4eb:	f93efd647f 	{ ae_lq32f.i	aeq3, a4, 28; ae_subq56	aeq1, aeq3, aeq1 }
     4f0:	631124        	ae_sq56s.i	aeq1, a1, 16
     4f3:	f87a3b005f 	{ ae_sraiq56	aeq1, aeq0, 1; ae_addq56	aeq0, aeq3, aeq0 }
     4f8:	631134        	ae_sq56s.i	aeq1, a1, 24
     4fb:	614134        	ae_lq56.i	aeq1, a1, 24
     4fe:	fc2c7a016f 	{ ae_sq56s.i	aeq0, a1, 48; ae_roundsq32asym	aeq0, aeq1 }
     503:	614124        	ae_lq56.i	aeq1, a1, 16
     506:	030a64        	ae_mulfq32sp16u.h	aeq1, aeq1, aep0
     509:	f93afa115f 	{ ae_sq56s.i	aeq1, a1, 40; ae_subq56	aeq1, aeq3, aeq0 }
     50e:	61c164        	ae_lq56.i	aeq3, a1, 48
     511:	ff747f3bef 	{ ae_trunca32q48	a11, aeq3; ae_truncq32	aeq3, aeq2 }
     516:	618154        	ae_lq56.i	aeq2, a1, 40
     519:	faee3b240f 	{ ae_sraiq56	aeq0, aeq2, 16; ae_addq56	aeq2, aeq1, aeq3 }
     51e:	631134        	ae_sq56s.i	aeq1, a1, 24
     521:	614124        	ae_lq56.i	aeq1, a1, 16
     524:	f483bf2cef 	{ ae_trunca32q48	a12, aeq2; ae_mulafq32sp16s.l	aeq0, aeq1, aep0 }
     529:	63b9           	s32i.n	a11, a3, 24
     52b:	fd647d814f 	{ ae_lq56.i	aeq0, a1, 32; ae_truncq32	aeq1, aeq0 }
     530:	018dc4        	ae_subq56	aeq2, aeq0, aeq1
     533:	f8663f2eef 	{ ae_trunca32q48	a14, aeq2; ae_addq56	aeq0, aeq0, aeq1 }
     538:	618134        	ae_lq56.i	aeq2, a1, 24
     53b:	f9b6ff0fef 	{ ae_trunca32q48	a15, aeq0; ae_subq56	aeq1, aeq2, aeq3 }
     540:	369904        	ae_trunca32q48	a9, aeq1
     543:	1a62e2        	s32i	a14, a2, 104
     546:	1062f2        	s32i	a15, a2, 64
     549:	1a63c2        	s32i	a12, a3, 104
     54c:	106392        	s32i	a9, a3, 64
     54f:	6005e4        	ae_lq32f.i	aeq0, a5, -8
     552:	604d04        	ae_lq32f.i	aeq1, a13, 0
     555:	fa663d66ef 	{ ae_lq32f.i	aeq3, a6, -8; ae_addq56	aeq2, aeq0, aeq1 }
     55a:	f826fb205f 	{ ae_sraiq56	aeq1, aeq2, 1; ae_subq56	aeq0, aeq0, aeq1 }
     55f:	d462fa114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_mulfq32sp16u.h	aeq1, aeq0, aep0 }
     564:	fafa3a112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_addq56	aeq2, aeq3, aeq2 }
     569:	36aa04        	ae_trunca32q48	a10, aeq2
     56c:	618144        	ae_lq56.i	aeq2, a1, 32
     56f:	fe347da12f 	{ ae_lq56.i	aeq1, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
     574:	fabafb144f 	{ ae_sraiq56	aeq1, aeq1, 16; ae_subq56	aeq2, aeq3, aeq2 }
     579:	1262a2        	s32i	a10, a2, 72
     57c:	f482fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulafq32sp16s.l	aeq1, aeq0, aep0 }
     581:	6085f4        	ae_lq32f.i	aeq2, a5, -4
     584:	fd6c7d0d1f 	{ ae_lq32f.i	aeq0, a13, 4; ae_truncq32	aeq1, aeq1 }
     589:	01e8c4        	ae_addq56	aeq3, aeq2, aeq0
     58c:	f832fb309f 	{ ae_sraiq56	aeq2, aeq3, 1; ae_subq56	aeq0, aeq2, aeq0 }
     591:	632134        	ae_sq56s.i	aeq2, a1, 24
     594:	630154        	ae_sq56s.i	aeq0, a1, 40
     597:	6006f4        	ae_lq32f.i	aeq0, a6, -4
     59a:	fbe63dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq3, aeq0, aeq3 }
     59f:	ff347a314f 	{ ae_sq56s.i	aeq3, a1, 32; ae_roundsq32asym	aeq3, aeq2 }
     5a4:	618154        	ae_lq56.i	aeq2, a1, 40
     5a7:	d762fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_mulfq32sp16u.h	aeq3, aeq2, aep0 }
     5ac:	633164        	ae_sq56s.i	aeq3, a1, 48
     5af:	61c134        	ae_lq56.i	aeq3, a1, 24
     5b2:	f8a6fde16f 	{ ae_lq56.i	aeq3, a1, 48; ae_subq56	aeq0, aeq0, aeq3 }
     5b7:	35f434        	ae_sraiq56	aeq3, aeq3, 16
     5ba:	f782fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulafq32sp16s.l	aeq3, aeq2, aep0 }
     5bf:	fa663f2bef 	{ ae_trunca32q48	a11, aeq2; ae_addq56	aeq2, aeq0, aeq1 }
     5c4:	f826ff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq0, aeq1 }
     5c9:	fe7c7f0def 	{ ae_trunca32q48	a13, aeq0; ae_truncq32	aeq2, aeq3 }
     5ce:	610124        	ae_lq56.i	aeq0, a1, 16
     5d1:	01cec4        	ae_subq56	aeq3, aeq0, aeq2
     5d4:	f9e23f3eef 	{ ae_trunca32q48	a14, aeq3; ae_addq56	aeq1, aeq0, aeq2 }
     5d9:	369f04        	ae_trunca32q48	a15, aeq1
     5dc:	1263b2        	s32i	a11, a3, 72
     5df:	82e9           	s32i.n	a14, a2, 32
     5e1:	1c62f2        	s32i	a15, a2, 112
     5e4:	83c9           	s32i.n	a12, a3, 32
     5e6:	1c63d2        	s32i	a13, a3, 112
     5e9:	f01d           	retw.n

000005eb <fix_fft15_stage+0x347>:
	...

000005ec <fix_fft40>:
     5ec:	034136        	entry	a1, 0x1a0
     5ef:	256122        	s32i	a2, a1, 148
     5f2:	fe9e21        	l32r	a2, 6c (1dec <LC3Plus_lc3_scratch_push>)
     5f5:	40a1b2        	movi	a11, 0x140
     5f8:	05ad           	mov.n	a10, a5
     5fa:	326152        	s32i	a5, a1, 200
     5fd:	276132        	s32i	a3, a1, 156
     600:	045d           	mov.n	a5, a4
     602:	0002e0        	callx8	a2
     605:	fe9181        	l32r	a8, 4c (247c <LC3Plus_RotVector_40_32>)
     608:	1124e0        	slli	a2, a4, 2
     60b:	2e6122        	s32i	a2, a1, 184
     60e:	08f8           	l32i.n	a15, a8, 0
     610:	1124b0        	slli	a2, a4, 5
     613:	2661a2        	s32i	a10, a1, 152
     616:	fcca82        	addi	a8, a10, -4
     619:	2521a2        	l32i	a10, a1, 148
     61c:	2e2142        	l32i	a4, a1, 184
     61f:	830c           	movi.n	a3, 8
     621:	060c           	movi.n	a6, 0
     623:	570c           	movi.n	a7, 5
     625:	2461f2        	s32i	a15, a1, 144

00000628 <fix_fft40+0x3c>:
     628:	0a9d           	mov.n	a9, a10
     62a:	603964        	ae_lq32f.xu	aeq0, a9, a6
     62d:	0b8776        	loop	a7, 63c <fix_fft40+0x50>
     630:	624814        	ae_sq32f.iu	aeq0, a8, 4
     633:	600914        	ae_lq32f.i	aeq0, a9, 4
     636:	624814        	ae_sq32f.iu	aeq0, a8, 4
     639:	603924        	ae_lq32f.xu	aeq0, a9, a2

0000063c <fix_fft40+0x50>:
     63c:	330b           	addi.n	a3, a3, -1
     63e:	664a           	add.n	a6, a6, a4
     640:	fe4356        	bnez	a3, 628 <fix_fft40+0x3c>
     643:	170c           	movi.n	a7, 1
     645:	117750        	slli	a7, a7, 11
     648:	300774        	ae_cvtp24a16x2.ll	aep0, a7, a7
     64b:	fe8621        	l32r	a2, 64 (15c <fix_fft5_stage>)
     64e:	262172        	l32i	a7, a1, 152
     651:	830c           	movi.n	a3, 8
     653:	50c142        	addi	a4, a1, 80
     656:	560174        	ae_sp24x2s.i	aep0, a1, 56

00000659 <fix_fft40+0x6d>:
     659:	600704        	ae_lq32f.i	aeq0, a7, 0
     65c:	540174        	ae_lp24x2.i	aep0, a1, 56
     65f:	d5e2fd471f 	{ ae_lq32f.i	aeq2, a7, 4; ae_mulfq32sp16u.l	aeq3, aeq0, aep0 }
     664:	d7e293844f 	{ or	a8, a4, a4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     669:	ff3c7d273f 	{ ae_lq32f.i	aeq1, a7, 12; ae_roundsq32asym	aeq3, aeq3 }
     66e:	fe3479f80f 	{ ae_sq32f.iu	aeq3, a8, 0; ae_roundsq32asym	aeq2, aeq2 }
     673:	60c744        	ae_lq32f.i	aeq3, a7, 16
     676:	600724        	ae_lq32f.i	aeq0, a7, 8
     679:	d4e2ba112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     67e:	633134        	ae_sq56s.i	aeq3, a1, 24
     681:	fc247de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq0, aeq0 }
     686:	d7e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     68b:	618134        	ae_lq56.i	aeq2, a1, 24
     68e:	d7e28047be 	{ addi	a11, a7, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     693:	ff3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq3 }
     698:	0bad           	mov.n	a10, a11
     69a:	632124        	ae_sq56s.i	aeq2, a1, 16
     69d:	079d           	mov.n	a9, a7
     69f:	604754        	ae_lq32f.i	aeq1, a7, 20
     6a2:	d4e3fd1a6f 	{ ae_lq32f.iu	aeq0, a10, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     6a7:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6aa:	fd2c7de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq1, aeq1 }
     6af:	ff3c7d596f 	{ ae_lq32f.iu	aeq2, a9, 24; ae_roundsq32asym	aeq3, aeq3 }
     6b4:	d7e2ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
     6b9:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6bc:	fe347de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq2, aeq2 }
     6c1:	d7e3fd092f 	{ ae_lq32f.i	aeq0, a9, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
     6c6:	d4e2b9d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
     6cb:	ff3c7d2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_roundsq32asym	aeq3, aeq3 }
     6d0:	d4e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     6d5:	fc2479f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq0, aeq0 }
     6da:	ff2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq3, aeq1 }
     6df:	07ad           	mov.n	a10, a7
     6e1:	04cd           	mov.n	a12, a4
     6e3:	627814        	ae_sq32f.iu	aeq3, a8, 4
     6e6:	0002e0        	callx8	a2
     6e9:	330b           	addi.n	a3, a3, -1
     6eb:	28c772        	addi	a7, a7, 40
     6ee:	f67356        	bnez	a3, 659 <fix_fft40+0x6d>
     6f1:	242162        	l32i	a6, a1, 144
     6f4:	a0f550        	addx4	a15, a5, a5
     6f7:	2a6142        	s32i	a4, a1, 168
     6fa:	8f4d           	ae_sext16	a4, a15
     6fc:	f8c692        	addi	a9, a6, -8
     6ff:	252162        	l32i	a6, a1, 148
     702:	82a032        	movi	a3, 130
     705:	7da082        	movi	a8, 125
     708:	2721f2        	l32i	a15, a1, 156
     70b:	f05440        	subx8	a5, a4, a4
     70e:	fe5821        	l32r	a2, 70 (5a82799a <_end+0x5a8254f2>)
     711:	5ad332        	addmi	a3, a3, 0x5a00
     714:	fe5871        	l32r	a7, 74 (a57d8666 <_end+0xa57d61be>)
     717:	a5d882        	addmi	a8, a8, 0xffffa500
     71a:	a0b440        	addx4	a11, a4, a4
     71d:	90c440        	addx2	a12, a4, a4
     720:	1155e0        	slli	a5, a5, 2
     723:	301874        	ae_cvtp24a16x2.ll	aep1, a8, a7
     726:	300324        	ae_cvtp24a16x2.ll	aep0, a3, a2
     729:	1184c0        	slli	a8, a4, 4
     72c:	b0a460        	addx8	a10, a4, a6
     72f:	113be0        	slli	a3, a11, 2
     732:	11bcd0        	slli	a11, a12, 3
     735:	765a           	add.n	a7, a6, a5
     737:	11cce0        	slli	a12, a12, 2
     73a:	3161a2        	s32i	a10, a1, 196
     73d:	af8a           	add.n	a10, a15, a8
     73f:	268a           	add.n	a2, a6, a8
     741:	2f6172        	s32i	a7, a1, 188
     744:	7fca           	add.n	a7, a15, a12
     746:	3061a2        	s32i	a10, a1, 192
     749:	246122        	s32i	a2, a1, 144
     74c:	8f5a           	add.n	a8, a15, a5
     74e:	2d6172        	s32i	a7, a1, 180
     751:	56ca           	add.n	a5, a6, a12
     753:	afba           	add.n	a10, a15, a11
     755:	26ba           	add.n	a2, a6, a11
     757:	c63a           	add.n	a12, a6, a3
     759:	01d172        	addmi	a7, a1, 0x100
     75c:	bf3a           	add.n	a11, a15, a3
     75e:	2c61a2        	s32i	a10, a1, 176
     761:	296122        	s32i	a2, a1, 164
     764:	60c722        	addi	a2, a7, 96
     767:	2861c2        	s32i	a12, a1, 160
     76a:	2621c2        	l32i	a12, a1, 152
     76d:	01d1a2        	addmi	a10, a1, 0x100
     770:	2b61b2        	s32i	a11, a1, 172
     773:	386122        	s32i	a2, a1, 224
     776:	20ca22        	addi	a2, a10, 32
     779:	a0d4f0        	addx4	a13, a4, a15
     77c:	b0e4f0        	addx8	a14, a4, a15
     77f:	a04460        	addx4	a4, a4, a6
     782:	01d1b2        	addmi	a11, a1, 0x100
     785:	e149           	s32i.n	a4, a1, 56
     787:	54c132        	addi	a3, a1, 84
     78a:	58c142        	addi	a4, a1, 88
     78d:	70c162        	addi	a6, a1, 112
     790:	366122        	s32i	a2, a1, 216
     793:	30cb22        	addi	a2, a11, 48
     796:	346132        	s32i	a3, a1, 208
     799:	336142        	s32i	a4, a1, 204
     79c:	376162        	s32i	a6, a1, 220
     79f:	356122        	s32i	a2, a1, 212
     7a2:	28ccc2        	addi	a12, a12, 40
     7a5:	570c           	movi.n	a7, 5
     7a7:	8a2c           	movi.n	a10, 40
     7a9:	0b2c           	movi.n	a11, 32
     7ab:	011346        	j	bfc <fix_fft40+0x610>

000007ae <fix_fft40+0x1c2>:
	...

000007af <fix_fft40+0x1c3>:
     7af:	093d           	mov.n	a3, a9
     7b1:	342142        	l32i	a4, a1, 208
     7b4:	2a2162        	l32i	a6, a1, 168
     7b7:	44a304        	ae_lp16x2f.iu	aep2, a3, 0
     7ba:	720c           	movi.n	a2, 7
     7bc:	60cc04        	ae_lq32f.i	aeq3, a12, 0
     7bf:	604c14        	ae_lq32f.i	aeq1, a12, 4
     7c2:	443314        	ae_lp16x2f.i	aep3, a3, 4
     7c5:	5c8276        	loop	a2, 825 <fix_fft40+0x239>
     7c8:	03a2e4        	ae_mulfq32sp16u.h	aeq2, aeq3, aep2
     7cb:	0332e4        	ae_mulfq32sp16u.h	aeq0, aeq3, aep3
     7ce:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     7d1:	f78bbb040f 	{ ae_sraiq56	aeq0, aeq0, 16; ae_mulafq32sp16s.l	aeq2, aeq3, aep2 }
     7d6:	0330d4        	ae_mulafq32sp16s.l	aeq0, aeq3, aep3
     7d9:	d56fba212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_mulfq32sp16u.h	aeq2, aeq1, aep3 }
     7de:	630134        	ae_sq56s.i	aeq0, a1, 24
     7e1:	d56bba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16u.h	aeq2, aeq1, aep2 }
     7e6:	632144        	ae_sq56s.i	aeq2, a1, 32
     7e9:	618154        	ae_lq56.i	aeq2, a1, 40
     7ec:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     7ef:	f58fbde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.l	aeq2, aeq1, aep3 }
     7f4:	353434        	ae_sraiq56	aeq0, aeq3, 16
     7f7:	f48bbda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulafq32sp16s.l	aeq0, aeq1, aep2 }
     7fc:	f9ea3dc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_addq56	aeq1, aeq1, aeq2 }
     801:	f8a2fa112f 	{ ae_sq56s.i	aeq1, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     806:	618124        	ae_lq56.i	aeq2, a1, 16
     809:	35a074        	ae_sraiq56	aeq2, aeq2, 1
     80c:	fe347b001f 	{ ae_sraiq56	aeq0, aeq0, 1; ae_roundsq32asym	aeq2, aeq2 }
     811:	fc245ba3bf 	{ ae_lp16x2f.xu	aep2, a3, a11; ae_roundsq32asym	aeq0, aeq0 }
     816:	626414        	ae_sq32f.iu	aeq2, a4, 4
     819:	60fca4        	ae_lq32f.xu	aeq3, a12, a10
     81c:	604c14        	ae_lq32f.i	aeq1, a12, 4
     81f:	443314        	ae_lp16x2f.i	aep3, a3, 4
     822:	624414        	ae_sq32f.iu	aeq0, a4, 4

00000825 <fix_fft40+0x239>:
     825:	372172        	l32i	a7, a1, 220
     828:	600624        	ae_lq32f.i	aeq0, a6, 8
     82b:	630124        	ae_sq56s.i	aeq0, a1, 16
     82e:	60c724        	ae_lq32f.i	aeq3, a7, 8
     831:	633134        	ae_sq56s.i	aeq3, a1, 24
     834:	604734        	ae_lq32f.i	aeq1, a7, 12
     837:	608604        	ae_lq32f.i	aeq2, a6, 0
     83a:	631144        	ae_sq56s.i	aeq1, a1, 32
     83d:	632154        	ae_sq56s.i	aeq2, a1, 40
     840:	618124        	ae_lq56.i	aeq2, a1, 16
     843:	614134        	ae_lq56.i	aeq1, a1, 24
     846:	fa36fd663f 	{ ae_lq32f.i	aeq3, a6, 12; ae_subq56	aeq2, aeq2, aeq1 }
     84b:	614144        	ae_lq56.i	aeq1, a1, 32
     84e:	01d142        	addmi	a4, a1, 0x100
     851:	f93ec7812e 	{ addi	a2, a1, 120; ae_subq56	aeq1, aeq3, aeq1 }
     856:	40c442        	addi	a4, a4, 64
     859:	6312a4        	ae_sq56s.i	aeq1, a2, -48
     85c:	600704        	ae_lq32f.i	aeq0, a7, 0
     85f:	614154        	ae_lq56.i	aeq1, a1, 40
     862:	fa6a39a46f 	{ ae_sq32f.i	aeq2, a4, 24; ae_addq56	aeq2, aeq1, aeq0 }
     867:	f82afda2af 	{ ae_lq56.i	aeq1, a2, -48; ae_subq56	aeq0, aeq1, aeq0 }
     86c:	630164        	ae_sq56s.i	aeq0, a1, 48
     86f:	3520b4        	ae_sraiq56	aeq0, aeq2, 2
     872:	fd2479947f 	{ ae_sq32f.i	aeq1, a4, 28; ae_roundsq32asym	aeq1, aeq0 }
     877:	608614        	ae_lq32f.i	aeq2, a6, 4
     87a:	600714        	ae_lq32f.i	aeq0, a7, 4
     87d:	f97239940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_addq56	aeq1, aeq2, aeq0 }
     882:	f832fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_subq56	aeq0, aeq2, aeq0 }
     887:	3550b4        	ae_sraiq56	aeq1, aeq1, 2
     88a:	630154        	ae_sq56s.i	aeq0, a1, 40
     88d:	fe2c7b202f 	{ ae_sraiq56	aeq0, aeq2, 2; ae_roundsq32asym	aeq2, aeq1 }
     892:	fc2479a41f 	{ ae_sq32f.i	aeq2, a4, 4; ae_roundsq32asym	aeq0, aeq0 }
     897:	614124        	ae_lq56.i	aeq1, a1, 16
     89a:	618134        	ae_lq56.i	aeq2, a1, 24
     89d:	f9ea3dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_addq56	aeq1, aeq1, aeq2 }
     8a2:	fbfa3dc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_addq56	aeq3, aeq3, aeq2 }
     8a7:	35a0b4        	ae_sraiq56	aeq2, aeq2, 2
     8aa:	fe347b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq2 }
     8af:	ff3c79842f 	{ ae_sq32f.i	aeq0, a4, 8; ae_roundsq32asym	aeq3, aeq3 }
     8b4:	622434        	ae_sq32f.i	aeq2, a4, 12
     8b7:	600644        	ae_lq32f.i	aeq0, a6, 16
     8ba:	608744        	ae_lq32f.i	aeq2, a7, 16
     8bd:	fbe239b45f 	{ ae_sq32f.i	aeq3, a4, 20; ae_addq56	aeq3, aeq0, aeq2 }
     8c2:	faa2fb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq2, aeq0, aeq2 }
     8c7:	fd2c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq1, aeq1 }
     8cc:	632134        	ae_sq56s.i	aeq2, a1, 24
     8cf:	608664        	ae_lq32f.i	aeq2, a6, 24
     8d2:	3821d2        	l32i	a13, a1, 224
     8d5:	632124        	ae_sq56s.i	aeq2, a1, 16
     8d8:	618134        	ae_lq56.i	aeq2, a1, 24
     8db:	fe3479944f 	{ ae_sq32f.i	aeq1, a4, 16; ae_roundsq32asym	aeq2, aeq2 }
     8e0:	604654        	ae_lq32f.i	aeq1, a6, 20
     8e3:	600754        	ae_lq32f.i	aeq0, a7, 20
     8e6:	fa6a39ad2f 	{ ae_sq32f.i	aeq2, a13, 8; ae_addq56	aeq2, aeq1, aeq0 }
     8eb:	f82afb30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_subq56	aeq0, aeq1, aeq0 }
     8f0:	ff3c7b20af 	{ ae_sraiq56	aeq2, aeq2, 2; ae_roundsq32asym	aeq3, aeq3 }
     8f5:	fe347b002f 	{ ae_sraiq56	aeq0, aeq0, 2; ae_roundsq32asym	aeq2, aeq2 }
     8fa:	fc2479bd0f 	{ ae_sq32f.i	aeq3, a13, 0; ae_roundsq32asym	aeq0, aeq0 }
     8ff:	60c764        	ae_lq32f.i	aeq3, a7, 24
     902:	fd1c79ad1f 	{ ae_sq32f.i	aeq2, a13, 4; ae_movq56	aeq1, aeq3 }
     907:	608674        	ae_lq32f.i	aeq2, a6, 28
     90a:	630154        	ae_sq56s.i	aeq0, a1, 40
     90d:	610124        	ae_lq56.i	aeq0, a1, 16
     910:	fbe63a214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_addq56	aeq3, aeq0, aeq3 }
     915:	f826fa313f 	{ ae_sq56s.i	aeq3, a1, 24; ae_subq56	aeq0, aeq0, aeq1 }
     91a:	61c154        	ae_lq56.i	aeq3, a1, 40
     91d:	608774        	ae_lq32f.i	aeq2, a7, 28
     920:	614144        	ae_lq56.i	aeq1, a1, 32
     923:	f8aafa012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_subq56	aeq0, aeq1, aeq2 }
     928:	fbea39bd3f 	{ ae_sq32f.i	aeq3, a13, 12; ae_addq56	aeq3, aeq1, aeq2 }
     92d:	618134        	ae_lq56.i	aeq2, a1, 24
     930:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     933:	fe2c7b30ef 	{ ae_sraiq56	aeq3, aeq3, 2; ae_roundsq32asym	aeq2, aeq1 }
     938:	fe3c79ad4f 	{ ae_sq32f.i	aeq2, a13, 16; ae_roundsq32asym	aeq2, aeq3 }
     93d:	61c124        	ae_lq56.i	aeq3, a1, 16
     940:	622d54        	ae_sq32f.i	aeq2, a13, 20
     943:	620d74        	ae_sq32f.i	aeq0, a13, 28
     946:	623d64        	ae_sq32f.i	aeq3, a13, 24
     949:	600d04        	ae_lq32f.i	aeq0, a13, 0
     94c:	604404        	ae_lq32f.i	aeq1, a4, 0
     94f:	fb6a3d4d1f 	{ ae_lq32f.i	aeq2, a13, 4; ae_addq56	aeq3, aeq1, aeq0 }
     954:	01d132        	addmi	a3, a1, 0x100
     957:	f92afd0d3f 	{ ae_lq32f.i	aeq0, a13, 12; ae_subq56	aeq1, aeq1, aeq0 }
     95c:	623304        	ae_sq32f.i	aeq3, a3, 0
     95f:	630124        	ae_sq56s.i	aeq0, a1, 16
     962:	60c414        	ae_lq32f.i	aeq3, a4, 4
     965:	f8fa3361ae 	{ l32i	a10, a1, 216; ae_addq56	aeq0, aeq3, aeq2 }
     96a:	fabaf9934f 	{ ae_sq32f.i	aeq1, a3, 16; ae_subq56	aeq2, aeq3, aeq2 }
     96f:	604424        	ae_lq32f.i	aeq1, a4, 8
     972:	61c124        	ae_lq56.i	aeq3, a1, 16
     975:	faaef9a35f 	{ ae_sq32f.i	aeq2, a3, 20; ae_subq56	aeq2, aeq1, aeq3 }
     97a:	f9ee39831f 	{ ae_sq32f.i	aeq0, a3, 4; ae_addq56	aeq1, aeq1, aeq3 }
     97f:	622a04        	ae_sq32f.i	aeq2, a10, 0
     982:	60c434        	ae_lq32f.i	aeq3, a4, 12
     985:	608d24        	ae_lq32f.i	aeq2, a13, 8
     988:	f9fa399a2f 	{ ae_sq32f.i	aeq1, a10, 8; ae_addq56	aeq1, aeq3, aeq2 }
     98d:	fabafd046f 	{ ae_lq32f.i	aeq0, a4, 24; ae_subq56	aeq2, aeq3, aeq2 }
     992:	60cd64        	ae_lq32f.i	aeq3, a13, 24
     995:	fae63a212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_addq56	aeq2, aeq0, aeq3 }
     99a:	fba6f99a1f 	{ ae_sq32f.i	aeq1, a10, 4; ae_subq56	aeq3, aeq0, aeq3 }
     99f:	3560b4        	ae_sraiq56	aeq1, aeq2, 2
     9a2:	fe2c7d2d5f 	{ ae_lq32f.i	aeq1, a13, 20; ae_roundsq32asym	aeq2, aeq1 }
     9a7:	35f0b4        	ae_sraiq56	aeq3, aeq3, 2
     9aa:	fd3c7a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq1, aeq3 }
     9af:	600d44        	ae_lq32f.i	aeq0, a13, 16
     9b2:	621424        	ae_sq32f.i	aeq1, a4, 8
     9b5:	622414        	ae_sq32f.i	aeq2, a4, 4
     9b8:	614124        	ae_lq56.i	aeq1, a1, 16
     9bb:	608d74        	ae_lq32f.i	aeq2, a13, 28
     9be:	60c474        	ae_lq32f.i	aeq3, a4, 28
     9c1:	f9fa399a3f 	{ ae_sq32f.i	aeq1, a10, 12; ae_addq56	aeq1, aeq3, aeq2 }
     9c6:	fabafd644f 	{ ae_lq32f.i	aeq3, a4, 16; ae_subq56	aeq2, aeq3, aeq2 }
     9cb:	fa7a3a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_addq56	aeq2, aeq3, aeq0 }
     9d0:	f83afb106f 	{ ae_sraiq56	aeq1, aeq1, 2; ae_subq56	aeq0, aeq3, aeq0 }
     9d5:	fd2c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq1, aeq1 }
     9da:	630124        	ae_sq56s.i	aeq0, a1, 16
     9dd:	3530b4        	ae_sraiq56	aeq0, aeq3, 2
     9e0:	ff2479940f 	{ ae_sq32f.i	aeq1, a4, 0; ae_roundsq32asym	aeq3, aeq0 }
     9e5:	600454        	ae_lq32f.i	aeq0, a4, 20
     9e8:	614144        	ae_lq56.i	aeq1, a1, 32
     9eb:	622324        	ae_sq32f.i	aeq2, a3, 8
     9ee:	fb6639b43f 	{ ae_sq32f.i	aeq3, a4, 12; ae_addq56	aeq3, aeq0, aeq1 }
     9f3:	f82afd440f 	{ ae_lq32f.i	aeq2, a4, 0; ae_subq56	aeq0, aeq1, aeq0 }
     9f8:	632154        	ae_sq56s.i	aeq2, a1, 40
     9fb:	633134        	ae_sq56s.i	aeq3, a1, 24
     9fe:	60c424        	ae_lq32f.i	aeq3, a4, 8
     a01:	fd1c7a014f 	{ ae_sq56s.i	aeq0, a1, 32; ae_movq56	aeq1, aeq3 }
     a06:	610154        	ae_lq56.i	aeq0, a1, 40
     a09:	fbe63d443f 	{ ae_lq32f.i	aeq2, a4, 12; ae_addq56	aeq3, aeq0, aeq3 }
     a0e:	f826fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_subq56	aeq0, aeq0, aeq1 }
     a13:	614124        	ae_lq56.i	aeq1, a1, 16
     a16:	608414        	ae_lq32f.i	aeq2, a4, 4
     a19:	621374        	ae_sq32f.i	aeq1, a3, 28
     a1c:	614294        	ae_lq56.i	aeq1, a2, -56
     a1f:	fbaafa32af 	{ ae_sq56s.i	aeq3, a2, -48; ae_subq56	aeq3, aeq1, aeq2 }
     a24:	fa763a015f 	{ ae_sq56s.i	aeq0, a1, 40; ae_addq56	aeq2, aeq2, aeq1 }
     a29:	610134        	ae_lq56.i	aeq0, a1, 24
     a2c:	633124        	ae_sq56s.i	aeq3, a1, 16
     a2f:	61c2a4        	ae_lq56.i	aeq3, a2, -48
     a32:	d6e3b9833f 	{ ae_sq32f.i	aeq0, a3, 12; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
     a37:	614144        	ae_lq56.i	aeq1, a1, 32
     a3a:	630164        	ae_sq56s.i	aeq0, a1, 48
     a3d:	610154        	ae_lq56.i	aeq0, a1, 40
     a40:	d5e2ba213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
     a45:	621364        	ae_sq32f.i	aeq1, a3, 24
     a48:	614124        	ae_lq56.i	aeq1, a1, 16
     a4b:	d4e3fa229f 	{ ae_sq56s.i	aeq2, a2, -56; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
     a50:	618164        	ae_lq56.i	aeq2, a1, 48
     a53:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a56:	f703ba116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_mulafq32sp16s.h	aeq2, aeq3, aep0 }
     a5b:	61c164        	ae_lq56.i	aeq3, a1, 48
     a5e:	357434        	ae_sraiq56	aeq1, aeq3, 16
     a61:	61c134        	ae_lq56.i	aeq3, a1, 24
     a64:	d7e7fa214f 	{ ae_sq56s.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep1 }
     a69:	618294        	ae_lq56.i	aeq2, a2, -56
     a6c:	35a434        	ae_sraiq56	aeq2, aeq2, 16
     a6f:	f502b351fe 	{ l32i	a15, a1, 212; ae_mulafq32sp16s.h	aeq2, aeq0, aep0 }
     a74:	353434        	ae_sraiq56	aeq0, aeq3, 16
     a77:	61c124        	ae_lq56.i	aeq3, a1, 16
     a7a:	f603fde14f 	{ ae_lq56.i	aeq3, a1, 32; ae_mulafq32sp16s.h	aeq1, aeq3, aep0 }
     a7f:	623f04        	ae_sq32f.i	aeq3, a15, 0
     a82:	61c134        	ae_lq56.i	aeq3, a1, 24
     a85:	f607b9af2f 	{ ae_sq32f.i	aeq2, a15, 8; ae_mulafq32sp16s.h	aeq0, aeq3, aep1 }
     a8a:	621f14        	ae_sq32f.i	aeq1, a15, 4
     a8d:	620f34        	ae_sq32f.i	aeq0, a15, 12
     a90:	604304        	ae_lq32f.i	aeq1, a3, 0
     a93:	608324        	ae_lq32f.i	aeq2, a3, 8
     a96:	fbea3251be 	{ l32i	a11, a1, 148; ae_addq56	aeq3, aeq1, aeq2 }
     a9b:	faaafa312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_subq56	aeq2, aeq1, aeq2 }
     aa0:	2421f2        	l32i	a15, a1, 144
     aa3:	614124        	ae_lq56.i	aeq1, a1, 16
     aa6:	369204        	ae_trunca32q48	a2, aeq1
     aa9:	60c314        	ae_lq32f.i	aeq3, a3, 4
     aac:	600334        	ae_lq32f.i	aeq0, a3, 12
     aaf:	fa7a3f26ef 	{ ae_trunca32q48	a6, aeq2; ae_addq56	aeq2, aeq3, aeq0 }
     ab4:	0b29           	s32i.n	a2, a11, 0
     ab6:	0f69           	s32i.n	a6, a15, 0
     ab8:	f83afd2a2f 	{ ae_lq32f.i	aeq1, a10, 8; ae_subq56	aeq0, aeq3, aeq0 }
     abd:	60ca44        	ae_lq32f.i	aeq3, a10, 16
     ac0:	2721f2        	l32i	a15, a1, 156
     ac3:	302122        	l32i	a2, a1, 192
     ac6:	e148           	l32i.n	a4, a1, 56
     ac8:	36ac04        	ae_trunca32q48	a12, aeq2
     acb:	f8ee3f08ef 	{ ae_trunca32q48	a8, aeq0; ae_addq56	aeq0, aeq1, aeq3 }
     ad0:	f9aefd4a3f 	{ ae_lq32f.i	aeq2, a10, 12; ae_subq56	aeq1, aeq1, aeq3 }
     ad5:	60ca54        	ae_lq32f.i	aeq3, a10, 20
     ad8:	f8f63f07ef 	{ ae_trunca32q48	a7, aeq0; ae_addq56	aeq0, aeq2, aeq3 }
     add:	fab6ff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq2, aeq2, aeq3 }
     ae2:	36ae04        	ae_trunca32q48	a14, aeq2
     ae5:	0fc9           	s32i.n	a12, a15, 0
     ae7:	0289           	s32i.n	a8, a2, 0
     ae9:	0479           	s32i.n	a7, a4, 0
     aeb:	600344        	ae_lq32f.i	aeq0, a3, 16
     aee:	608364        	ae_lq32f.i	aeq2, a3, 24
     af1:	282162        	l32i	a6, a1, 160
     af4:	3e2172        	l32i	a7, a1, 248
     af7:	fd047f19ef 	{ ae_trunca32q48	a9, aeq1; ae_movq56	aeq1, aeq0 }
     afc:	f8a2fd635f 	{ ae_lq32f.i	aeq3, a3, 20; ae_subq56	aeq0, aeq0, aeq2 }
     b01:	f9ea3a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_addq56	aeq1, aeq1, aeq2 }
     b06:	0699           	s32i.n	a9, a6, 0
     b08:	633134        	ae_sq56s.i	aeq3, a1, 24
     b0b:	60c374        	ae_lq32f.i	aeq3, a3, 28
     b0e:	07d9           	s32i.n	a13, a7, 0
     b10:	07dd           	mov.n	a13, a7
     b12:	610124        	ae_lq56.i	aeq0, a1, 16
     b15:	608a04        	ae_lq32f.i	aeq2, a10, 0
     b18:	2b21b2        	l32i	a11, a1, 172
     b1b:	312162        	l32i	a6, a1, 196
     b1e:	292172        	l32i	a7, a1, 164
     b21:	fc1c7f08ef 	{ ae_trunca32q48	a8, aeq0; ae_movq56	aeq0, aeq3 }
     b26:	632144        	ae_sq56s.i	aeq2, a1, 32
     b29:	618134        	ae_lq56.i	aeq2, a1, 24
     b2c:	fbb6ff19ef 	{ ae_trunca32q48	a9, aeq1; ae_subq56	aeq3, aeq2, aeq3 }
     b31:	fa723d2a6f 	{ ae_lq32f.i	aeq1, a10, 24; ae_addq56	aeq2, aeq2, aeq0 }
     b36:	610144        	ae_lq56.i	aeq0, a1, 32
     b39:	0be9           	s32i.n	a14, a11, 0
     b3b:	633124        	ae_sq56s.i	aeq3, a1, 16
     b3e:	0689           	s32i.n	a8, a6, 0
     b40:	0799           	s32i.n	a9, a7, 0
     b42:	fe0c7f29ef 	{ ae_trunca32q48	a9, aeq2; ae_movq56	aeq2, aeq1 }
     b47:	f96633d1ee 	{ l32i	a14, a1, 244; ae_addq56	aeq1, aeq0, aeq1 }
     b4c:	f8a2fde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_subq56	aeq0, aeq0, aeq2 }
     b51:	631124        	ae_sq56s.i	aeq1, a1, 16
     b54:	2c2142        	l32i	a4, a1, 176
     b57:	36bc04        	ae_trunca32q48	a12, aeq3
     b5a:	60ca14        	ae_lq32f.i	aeq3, a10, 4
     b5d:	614124        	ae_lq56.i	aeq1, a1, 16
     b60:	633134        	ae_sq56s.i	aeq3, a1, 24
     b63:	0ec9           	s32i.n	a12, a14, 0
     b65:	369c04        	ae_trunca32q48	a12, aeq1
     b68:	60ca74        	ae_lq32f.i	aeq3, a10, 28
     b6b:	0499           	s32i.n	a9, a4, 0
     b6d:	618134        	ae_lq56.i	aeq2, a1, 24
     b70:	f9f61405cf 	{ s32i.n	a12, a5, 0; ae_addq56	aeq1, aeq2, aeq3 }
     b75:	3b6152        	s32i	a5, a1, 236
     b78:	fbb6f2f15e 	{ l32i	a5, a1, 188; ae_subq56	aeq3, aeq2, aeq3 }
     b7d:	2d21a2        	l32i	a10, a1, 180
     b80:	368704        	ae_trunca32q48	a7, aeq0
     b83:	369904        	ae_trunca32q48	a9, aeq1
     b86:	0579           	s32i.n	a7, a5, 0
     b88:	0a99           	s32i.n	a9, a10, 0
     b8a:	3c2182        	l32i	a8, a1, 240
     b8d:	3a2172        	l32i	a7, a1, 232
     b90:	392192        	l32i	a9, a1, 228
     b93:	3f2132        	l32i	a3, a1, 252
     b96:	36bc04        	ae_trunca32q48	a12, aeq3
     b99:	08c9           	s32i.n	a12, a8, 0
     b9b:	c78b           	addi.n	a12, a7, 8
     b9d:	790b           	addi.n	a7, a9, -1
     b9f:	938b           	addi.n	a9, a3, 8
     ba1:	2e2132        	l32i	a3, a1, 184
     ba4:	443a           	add.n	a4, a4, a3
     ba6:	2c6142        	s32i	a4, a1, 176
     ba9:	252142        	l32i	a4, a1, 148
     bac:	223a           	add.n	a2, a2, a3
     bae:	306122        	s32i	a2, a1, 192
     bb1:	243a           	add.n	a2, a4, a3
     bb3:	256122        	s32i	a2, a1, 148
     bb6:	3b2122        	l32i	a2, a1, 236
     bb9:	292142        	l32i	a4, a1, 164
     bbc:	663a           	add.n	a6, a6, a3
     bbe:	553a           	add.n	a5, a5, a3
     bc0:	316162        	s32i	a6, a1, 196
     bc3:	282162        	l32i	a6, a1, 160
     bc6:	2f6152        	s32i	a5, a1, 188
     bc9:	523a           	add.n	a5, a2, a3
     bcb:	243a           	add.n	a2, a4, a3
     bcd:	296122        	s32i	a2, a1, 164
     bd0:	e128           	l32i.n	a2, a1, 56
     bd2:	463a           	add.n	a4, a6, a3
     bd4:	242162        	l32i	a6, a1, 144
     bd7:	286142        	s32i	a4, a1, 160
     bda:	423a           	add.n	a4, a2, a3
     bdc:	bb3a           	add.n	a11, a11, a3
     bde:	aa3a           	add.n	a10, a10, a3
     be0:	e149           	s32i.n	a4, a1, 56
     be2:	463a           	add.n	a4, a6, a3
     be4:	2b61b2        	s32i	a11, a1, 172
     be7:	2d61a2        	s32i	a10, a1, 180
     bea:	ff3a           	add.n	a15, a15, a3
     bec:	dd3a           	add.n	a13, a13, a3
     bee:	0b2c           	movi.n	a11, 32
     bf0:	ee3a           	add.n	a14, a14, a3
     bf2:	8a2c           	movi.n	a10, 40
     bf4:	883a           	add.n	a8, a8, a3
     bf6:	246142        	s32i	a4, a1, 144
     bf9:	051716        	beqz	a7, c4e <fix_fft40+0x662>

00000bfc <fix_fft40+0x610>:
     bfc:	d8cc32        	addi	a3, a12, -40
     bff:	0348           	l32i.n	a4, a3, 0
     c01:	1338           	l32i.n	a3, a3, 4
     c03:	2761f2        	s32i	a15, a1, 156
     c06:	214140        	srai	a4, a4, 1
     c09:	213130        	srai	a3, a3, 1
     c0c:	146142        	s32i	a4, a1, 80
     c0f:	156132        	s32i	a3, a1, 84
     c12:	3f6192        	s32i	a9, a1, 252
     c15:	3e61d2        	s32i	a13, a1, 248
     c18:	3d61e2        	s32i	a14, a1, 244
     c1b:	3c6182        	s32i	a8, a1, 240
     c1e:	3a61c2        	s32i	a12, a1, 232
     c21:	396172        	s32i	a7, a1, 228
     c24:	025726        	beqi	a7, 5, c2a <fix_fft40+0x63e>
     c27:	fee106        	j	7af <fix_fft40+0x1c3>
     c2a:	332142        	l32i	a4, a1, 204
     c2d:	2a2162        	l32i	a6, a1, 168
     c30:	720c           	movi.n	a2, 7
     c32:	203cc0        	or	a3, a12, a12
     c35:	128276        	loop	a2, c4b <fix_fft40+0x65f>
     c38:	03c8           	l32i.n	a12, a3, 0
     c3a:	1378           	l32i.n	a7, a3, 4
     c3c:	28c332        	addi	a3, a3, 40
     c3f:	21c1c0        	srai	a12, a12, 1
     c42:	217170        	srai	a7, a7, 1
     c45:	04c9           	s32i.n	a12, a4, 0
     c47:	1479           	s32i.n	a7, a4, 4
     c49:	448b           	addi.n	a4, a4, 8

00000c4b <fix_fft40+0x65f>:
     c4b:	fef586        	j	825 <fix_fft40+0x239>

00000c4e <fix_fft40+0x662>:
     c4e:	fd0a21        	l32r	a2, 78 (1e2c <LC3Plus_lc3_scratch_pop>)
     c51:	3221a2        	l32i	a10, a1, 200
     c54:	2621b2        	l32i	a11, a1, 152
     c57:	0002e0        	callx8	a2
     c5a:	f01d           	retw.n

00000c5c <FFT8N>:
     c5c:	020136        	entry	a1, 0x100
     c5f:	186132        	s32i	a3, a1, 96
     c62:	176122        	s32i	a2, a1, 92
     c65:	0215e6        	bgei	a5, 1, c6b <FFT8N+0xf>
     c68:	01b346        	j	1339 <FFT8N+0x6dd>
     c6b:	d1e750        	mul16s	a14, a7, a5
     c6e:	412132        	l32i	a3, a1, 0x104
     c71:	11a6e0        	slli	a10, a6, 2
     c74:	90cee0        	addx2	a12, a14, a14
     c77:	11b7e0        	slli	a11, a7, 2
     c7a:	a08ee0        	addx4	a8, a14, a14
     c7d:	3061a2        	s32i	a10, a1, 192
     c80:	11acf0        	slli	a10, a12, 1
     c83:	f09ee0        	subx8	a9, a14, a14
     c86:	2f61b2        	s32i	a11, a1, 188
     c89:	e0be30        	subx4	a11, a14, a3
     c8c:	c07c30        	sub	a7, a12, a3
     c8f:	d0ce30        	subx2	a12, a14, a3
     c92:	c0aa30        	sub	a10, a10, a3
     c95:	c08830        	sub	a8, a8, a3
     c98:	c0ee30        	sub	a14, a14, a3
     c9b:	c03930        	sub	a3, a9, a3
     c9e:	172192        	l32i	a9, a1, 92
     ca1:	d12650        	mul16s	a2, a6, a5
     ca4:	a06840        	addx4	a6, a8, a4
     ca7:	a08a40        	addx4	a8, a10, a4
     caa:	a0a740        	addx4	a10, a7, a4
     cad:	182172        	l32i	a7, a1, 96
     cb0:	a0f290        	addx4	a15, a2, a9
     cb3:	a0bb40        	addx4	a11, a11, a4
     cb6:	2e61f2        	s32i	a15, a1, 184
     cb9:	a0fc40        	addx4	a15, a12, a4
     cbc:	a03340        	addx4	a3, a3, a4
     cbf:	a04e40        	addx4	a4, a14, a4
     cc2:	216162        	s32i	a6, a1, 132
     cc5:	206182        	s32i	a8, a1, 128
     cc8:	1c61a2        	s32i	a10, a1, 112
     ccb:	c1b9           	s32i.n	a11, a1, 48
     ccd:	a06270        	addx4	a6, a2, a7
     cd0:	b08290        	addx8	a8, a2, a9
     cd3:	b0a270        	addx8	a10, a2, a7
     cd6:	90b220        	addx2	a11, a2, a2
     cd9:	f0c220        	subx8	a12, a2, a2
     cdc:	a0e220        	addx4	a14, a2, a2
     cdf:	1122c0        	slli	a2, a2, 4
     ce2:	4021d2        	l32i	a13, a1, 0x100
     ce5:	226132        	s32i	a3, a1, 136
     ce8:	1b61f2        	s32i	a15, a1, 108
     ceb:	1f6142        	s32i	a4, a1, 124
     cee:	114ce0        	slli	a4, a12, 2
     cf1:	f72a           	add.n	a15, a7, a2
     cf3:	292a           	add.n	a2, a9, a2
     cf5:	113bd0        	slli	a3, a11, 3
     cf8:	2b6122        	s32i	a2, a1, 172
     cfb:	112be0        	slli	a2, a11, 2
     cfe:	b74a           	add.n	a11, a7, a4
     d00:	c94a           	add.n	a12, a9, a4
     d02:	473a           	add.n	a4, a7, a3
     d04:	393a           	add.n	a3, a9, a3
     d06:	246162        	s32i	a6, a1, 144
     d09:	116ee0        	slli	a6, a14, 2
     d0c:	e92a           	add.n	a14, a9, a2
     d0e:	286132        	s32i	a3, a1, 160
     d11:	272a           	add.n	a2, a7, a2
     d13:	f03550        	subx8	a3, a5, a5
     d16:	2d6182        	s32i	a8, a1, 180
     d19:	876a           	add.n	a8, a7, a6
     d1b:	2c61a2        	s32i	a10, a1, 176
     d1e:	a96a           	add.n	a10, a9, a6
     d20:	236122        	s32i	a2, a1, 140
     d23:	b023d0        	addx8	a2, a3, a13
     d26:	a06550        	addx4	a6, a5, a5
     d29:	1e6122        	s32i	a2, a1, 120
     d2c:	b026d0        	addx8	a2, a6, a13
     d2f:	1175b0        	slli	a7, a5, 5
     d32:	2a6182        	s32i	a8, a1, 168
     d35:	b129           	s32i.n	a2, a1, 44
     d37:	2d7a           	add.n	a2, a13, a7
     d39:	908550        	addx2	a8, a5, a5
     d3c:	2961a2        	s32i	a10, a1, 164
     d3f:	1a6122        	s32i	a2, a1, 104
     d42:	1198c0        	slli	a9, a8, 4
     d45:	b028d0        	addx8	a2, a8, a13
     d48:	11a5c0        	slli	a10, a5, 4
     d4b:	2761e2        	s32i	a14, a1, 156
     d4e:	3d9a           	add.n	a3, a13, a9
     d50:	196122        	s32i	a2, a1, 100
     d53:	2daa           	add.n	a2, a13, a10
     d55:	b0e5d0        	addx8	a14, a5, a13
     d58:	070c           	movi.n	a7, 0
     d5a:	a139           	s32i.n	a3, a1, 40
     d5c:	086122        	s32i	a2, a1, 32
     d5f:	2561d2        	s32i	a13, a1, 148
     d62:	0d61e2        	s32i	a14, a1, 52
     d65:	178576        	loop	a5, d80 <FFT8N+0x124>
     d68:	030150        	rsr.lend	a5
     d6b:	130050        	wsr.lbeg	a5
     d6e:	fcc351        	l32r	a5, 7c (1339 <FFT8N+0x6dd>)
     d71:	0020f0        	nop
     d74:	130150        	wsr.lend	a5
     d77:	002000        	isync
     d7a:	030250        	rsr.lcount	a5
     d7d:	01c552        	addi	a5, a5, 1
     d80:	252122        	l32i	a2, a1, 148
     d83:	d1a8           	l32i.n	a10, a1, 52
     d85:	346142        	s32i	a4, a1, 208
     d88:	0238           	l32i.n	a3, a2, 0
     d8a:	1298           	l32i.n	a9, a2, 4
     d8c:	0a68           	l32i.n	a6, a10, 0
     d8e:	331b           	addi.n	a3, a3, 1
     d90:	491b           	addi.n	a4, a9, 1
     d92:	21d130        	srai	a13, a3, 1
     d95:	21e140        	srai	a14, a4, 1
     d98:	3761f2        	s32i	a15, a1, 220
     d9b:	3661b2        	s32i	a11, a1, 216
     d9e:	3561c2        	s32i	a12, a1, 212
     da1:	266172        	s32i	a7, a1, 152
     da4:	1d61d2        	s32i	a13, a1, 116
     da7:	91e9           	s32i.n	a14, a1, 36
     da9:	4169           	s32i.n	a6, a1, 16
     dab:	213716        	beqz	a7, fc2 <FFT8N+0x366>
     dae:	8128           	l32i.n	a2, a1, 32
     db0:	1b2132        	l32i	a3, a1, 108
     db3:	c198           	l32i.n	a9, a1, 48
     db5:	0278           	l32i.n	a7, a2, 0
     db7:	0348           	l32i.n	a4, a3, 0
     db9:	192152        	l32i	a5, a1, 100
     dbc:	1c2162        	l32i	a6, a1, 112
     dbf:	13c8           	l32i.n	a12, a3, 4
     dc1:	8129           	s32i.n	a2, a1, 32
     dc3:	12a8           	l32i.n	a10, a2, 4
     dc5:	822740        	mull	a2, a7, a4
     dc8:	05b8           	l32i.n	a11, a5, 0
     dca:	15d8           	l32i.n	a13, a5, 4
     dcc:	0688           	l32i.n	a8, a6, 0
     dce:	1658           	l32i.n	a5, a6, 4
     dd0:	09e8           	l32i.n	a14, a9, 0
     dd2:	096d           	mov.n	a6, a9
     dd4:	c199           	s32i.n	a9, a1, 48
     dd6:	b29740        	mulsh	a9, a7, a4
     dd9:	052f20        	extui	a2, a2, 31, 1
     ddc:	902920        	addx2	a2, a9, a2
     ddf:	8297c0        	mull	a9, a7, a12
     de2:	b277c0        	mulsh	a7, a7, a12
     de5:	059f90        	extui	a9, a9, 31, 1
     de8:	909790        	addx2	a9, a7, a9
     deb:	827ac0        	mull	a7, a10, a12
     dee:	b2cac0        	mulsh	a12, a10, a12
     df1:	057f70        	extui	a7, a7, 31, 1
     df4:	907c70        	addx2	a7, a12, a7
     df7:	c02270        	sub	a2, a2, a7
     dfa:	7129           	s32i.n	a2, a1, 28
     dfc:	b22a40        	mulsh	a2, a10, a4
     dff:	824a40        	mull	a4, a10, a4
     e02:	82ab50        	mull	a10, a11, a5
     e05:	054f40        	extui	a4, a4, 31, 1
     e08:	902240        	addx2	a2, a2, a4
     e0b:	824b80        	mull	a4, a11, a8
     e0e:	292a           	add.n	a2, a9, a2
     e10:	1a2132        	l32i	a3, a1, 104
     e13:	f129           	s32i.n	a2, a1, 60
     e15:	b29b80        	mulsh	a9, a11, a8
     e18:	052f40        	extui	a2, a4, 31, 1
     e1b:	054fa0        	extui	a4, a10, 31, 1
     e1e:	b2bb50        	mulsh	a11, a11, a5
     e21:	82ad50        	mull	a10, a13, a5
     e24:	b25d50        	mulsh	a5, a13, a5
     e27:	03f8           	l32i.n	a15, a3, 0
     e29:	902920        	addx2	a2, a9, a2
     e2c:	059fa0        	extui	a9, a10, 31, 1
     e2f:	904b40        	addx2	a4, a11, a4
     e32:	b2bd80        	mulsh	a11, a13, a8
     e35:	82dd80        	mull	a13, a13, a8
     e38:	16c8           	l32i.n	a12, a6, 4
     e3a:	b168           	l32i.n	a6, a1, 44
     e3c:	905590        	addx2	a5, a5, a9
     e3f:	2121a2        	l32i	a10, a1, 132
     e42:	1338           	l32i.n	a3, a3, 4
     e44:	c02250        	sub	a2, a2, a5
     e47:	055fd0        	extui	a5, a13, 31, 1
     e4a:	166122        	s32i	a2, a1, 88
     e4d:	902b50        	addx2	a2, a11, a5
     e50:	82bfe0        	mull	a11, a15, a14
     e53:	242a           	add.n	a2, a4, a2
     e55:	825fc0        	mull	a5, a15, a12
     e58:	0678           	l32i.n	a7, a6, 0
     e5a:	b169           	s32i.n	a6, a1, 44
     e5c:	1688           	l32i.n	a8, a6, 4
     e5e:	0a98           	l32i.n	a9, a10, 0
     e60:	b2dfe0        	mulsh	a13, a15, a14
     e63:	b26fc0        	mulsh	a6, a15, a12
     e66:	0afd           	mov.n	a15, a10
     e68:	82a3c0        	mull	a10, a3, a12
     e6b:	136122        	s32i	a2, a1, 76
     e6e:	052fb0        	extui	a2, a11, 31, 1
     e71:	b2b3c0        	mulsh	a11, a3, a12
     e74:	054f50        	extui	a4, a5, 31, 1
     e77:	055fa0        	extui	a5, a10, 31, 1
     e7a:	b2c3e0        	mulsh	a12, a3, a14
     e7d:	8233e0        	mull	a3, a3, a14
     e80:	902d20        	addx2	a2, a13, a2
     e83:	905b50        	addx2	a5, a11, a5
     e86:	1fa8           	l32i.n	a10, a15, 4
     e88:	c02250        	sub	a2, a2, a5
     e8b:	053f30        	extui	a3, a3, 31, 1
     e8e:	904640        	addx2	a4, a6, a4
     e91:	6129           	s32i.n	a2, a1, 24
     e93:	902c30        	addx2	a2, a12, a3
     e96:	82d790        	mull	a13, a7, a9
     e99:	242a           	add.n	a2, a4, a2
     e9b:	b2e790        	mulsh	a14, a7, a9
     e9e:	8247a0        	mull	a4, a7, a10
     ea1:	146122        	s32i	a2, a1, 80
     ea4:	052fd0        	extui	a2, a13, 31, 1
     ea7:	a168           	l32i.n	a6, a1, 40
     ea9:	902e20        	addx2	a2, a14, a2
     eac:	b277a0        	mulsh	a7, a7, a10
     eaf:	82b8a0        	mull	a11, a8, a10
     eb2:	2021e2        	l32i	a14, a1, 128
     eb5:	053f40        	extui	a3, a4, 31, 1
     eb8:	b2a8a0        	mulsh	a10, a8, a10
     ebb:	903730        	addx2	a3, a7, a3
     ebe:	057fb0        	extui	a7, a11, 31, 1
     ec1:	907a70        	addx2	a7, a10, a7
     ec4:	0658           	l32i.n	a5, a6, 0
     ec6:	0ea8           	l32i.n	a10, a14, 0
     ec8:	82d890        	mull	a13, a8, a9
     ecb:	b2c890        	mulsh	a12, a8, a9
     ece:	1e88           	l32i.n	a8, a14, 4
     ed0:	c02270        	sub	a2, a2, a7
     ed3:	057fd0        	extui	a7, a13, 31, 1
     ed6:	16d8           	l32i.n	a13, a6, 4
     ed8:	8245a0        	mull	a4, a5, a10
     edb:	82b580        	mull	a11, a5, a8
     ede:	156122        	s32i	a2, a1, 84
     ee1:	902c70        	addx2	a2, a12, a7
     ee4:	057f40        	extui	a7, a4, 31, 1
     ee7:	b295a0        	mulsh	a9, a5, a10
     eea:	b25580        	mulsh	a5, a5, a8
     eed:	824d80        	mull	a4, a13, a8
     ef0:	a169           	s32i.n	a6, a1, 40
     ef2:	05cfb0        	extui	a12, a11, 31, 1
     ef5:	b26d80        	mulsh	a6, a13, a8
     ef8:	232a           	add.n	a2, a3, a2
     efa:	9035c0        	addx2	a3, a5, a12
     efd:	055f40        	extui	a5, a4, 31, 1
     f00:	126122        	s32i	a2, a1, 72
     f03:	902970        	addx2	a2, a9, a7
     f06:	905650        	addx2	a5, a6, a5
     f09:	222162        	l32i	a6, a1, 136
     f0c:	b27da0        	mulsh	a7, a13, a10
     f0f:	82bda0        	mull	a11, a13, a10
     f12:	1e21d2        	l32i	a13, a1, 120
     f15:	0698           	l32i.n	a9, a6, 0
     f17:	c02250        	sub	a2, a2, a5
     f1a:	0d88           	l32i.n	a8, a13, 0
     f1c:	055fb0        	extui	a5, a11, 31, 1
     f1f:	5129           	s32i.n	a2, a1, 20
     f21:	902750        	addx2	a2, a7, a5
     f24:	82c890        	mull	a12, a8, a9
     f27:	232a           	add.n	a2, a3, a2
     f29:	1638           	l32i.n	a3, a6, 4
     f2b:	e129           	s32i.n	a2, a1, 56
     f2d:	052fc0        	extui	a2, a12, 31, 1
     f30:	1dc8           	l32i.n	a12, a13, 4
     f32:	b24890        	mulsh	a4, a8, a9
     f35:	827830        	mull	a7, a8, a3
     f38:	902420        	addx2	a2, a4, a2
     f3b:	b28830        	mulsh	a8, a8, a3
     f3e:	824c30        	mull	a4, a12, a3
     f41:	05af70        	extui	a10, a7, 31, 1
     f44:	9058a0        	addx2	a5, a8, a10
     f47:	058f40        	extui	a8, a4, 31, 1
     f4a:	1f2142        	l32i	a4, a1, 124
     f4d:	b23c30        	mulsh	a3, a12, a3
     f50:	41b8           	l32i.n	a11, a1, 16
     f52:	827c90        	mull	a7, a12, a9
     f55:	b2ac90        	mulsh	a10, a12, a9
     f58:	1498           	l32i.n	a9, a4, 4
     f5a:	903380        	addx2	a3, a3, a8
     f5d:	c08230        	sub	a8, a2, a3
     f60:	052f70        	extui	a2, a7, 31, 1
     f63:	902a20        	addx2	a2, a10, a2
     f66:	82cb90        	mull	a12, a11, a9
     f69:	0478           	l32i.n	a7, a4, 0
     f6b:	d1a8           	l32i.n	a10, a1, 52
     f6d:	252a           	add.n	a2, a5, a2
     f6f:	b25b90        	mulsh	a5, a11, a9
     f72:	053fc0        	extui	a3, a12, 31, 1
     f75:	116122        	s32i	a2, a1, 68
     f78:	902530        	addx2	a2, a5, a3
     f7b:	1a38           	l32i.n	a3, a10, 4
     f7d:	82cb70        	mull	a12, a11, a7
     f80:	b2bb70        	mulsh	a11, a11, a7
     f83:	05afc0        	extui	a10, a12, 31, 1
     f86:	825370        	mull	a5, a3, a7
     f89:	90aba0        	addx2	a10, a11, a10
     f8c:	b2b370        	mulsh	a11, a3, a7
     f8f:	827390        	mull	a7, a3, a9
     f92:	b23390        	mulsh	a3, a3, a9
     f95:	055f50        	extui	a5, a5, 31, 1
     f98:	057f70        	extui	a7, a7, 31, 1
     f9b:	903370        	addx2	a3, a3, a7
     f9e:	905b50        	addx2	a5, a11, a5
     fa1:	c03a30        	sub	a3, a10, a3
     fa4:	225a           	add.n	a2, a2, a5
     fa6:	04ad           	mov.n	a10, a4
     fa8:	106122        	s32i	a2, a1, 64
     fab:	4139           	s32i.n	a3, a1, 16
     fad:	1921c2        	l32i	a12, a1, 100
     fb0:	1b2192        	l32i	a9, a1, 108
     fb3:	1a2142        	l32i	a4, a1, 104
     fb6:	a1b8           	l32i.n	a11, a1, 40
     fb8:	b128           	l32i.n	a2, a1, 44
     fba:	c158           	l32i.n	a5, a1, 48
     fbc:	1c2132        	l32i	a3, a1, 112
     fbf:	0017c6        	j	1022 <FFT8N+0x3c6>

00000fc2 <FFT8N+0x366>:
     fc2:	d128           	l32i.n	a2, a1, 52
     fc4:	8158           	l32i.n	a5, a1, 32
     fc6:	1921c2        	l32i	a12, a1, 100
     fc9:	1228           	l32i.n	a2, a2, 4
     fcb:	106122        	s32i	a2, a1, 64
     fce:	1528           	l32i.n	a2, a5, 4
     fd0:	f129           	s32i.n	a2, a1, 60
     fd2:	b128           	l32i.n	a2, a1, 44
     fd4:	1a2142        	l32i	a4, a1, 104
     fd7:	0538           	l32i.n	a3, a5, 0
     fd9:	12b8           	l32i.n	a11, a2, 4
     fdb:	1261b2        	s32i	a11, a1, 72
     fde:	a1b8           	l32i.n	a11, a1, 40
     fe0:	0c68           	l32i.n	a6, a12, 0
     fe2:	0488           	l32i.n	a8, a4, 0
     fe4:	0bd8           	l32i.n	a13, a11, 0
     fe6:	51d9           	s32i.n	a13, a1, 20
     fe8:	1e21d2        	l32i	a13, a1, 120
     feb:	1498           	l32i.n	a9, a4, 4
     fed:	02a8           	l32i.n	a10, a2, 0
     fef:	1be8           	l32i.n	a14, a11, 4
     ff1:	1df8           	l32i.n	a15, a13, 4
     ff3:	7139           	s32i.n	a3, a1, 28
     ff5:	8159           	s32i.n	a5, a1, 32
     ff7:	166162        	s32i	a6, a1, 88
     ffa:	6189           	s32i.n	a8, a1, 24
     ffc:	146192        	s32i	a9, a1, 80
     fff:	1561a2        	s32i	a10, a1, 84
    1002:	e1e9           	s32i.n	a14, a1, 56
    1004:	1161f2        	s32i	a15, a1, 68
    1007:	0d88           	l32i.n	a8, a13, 0
    1009:	222162        	l32i	a6, a1, 136
    100c:	2121f2        	l32i	a15, a1, 132
    100f:	2021e2        	l32i	a14, a1, 128
    1012:	1c2132        	l32i	a3, a1, 112
    1015:	c158           	l32i.n	a5, a1, 48
    1017:	1b2192        	l32i	a9, a1, 108
    101a:	1f21a2        	l32i	a10, a1, 124
    101d:	1c78           	l32i.n	a7, a12, 4
    101f:	136172        	s32i	a7, a1, 76
    1022:	262172        	l32i	a7, a1, 152
    1025:	dd8b           	addi.n	a13, a13, 8
    1027:	bb8b           	addi.n	a11, a11, 8
    1029:	770b           	addi.n	a7, a7, -1
    102b:	266172        	s32i	a7, a1, 152
    102e:	8178           	l32i.n	a7, a1, 32
    1030:	1e61d2        	s32i	a13, a1, 120
    1033:	2f21d2        	l32i	a13, a1, 188
    1036:	a1b9           	s32i.n	a11, a1, 40
    1038:	cc8b           	addi.n	a12, a12, 8
    103a:	d1b8           	l32i.n	a11, a1, 52
    103c:	228b           	addi.n	a2, a2, 8
    103e:	448b           	addi.n	a4, a4, 8
    1040:	1961c2        	s32i	a12, a1, 100
    1043:	2521c2        	l32i	a12, a1, 148
    1046:	b129           	s32i.n	a2, a1, 44
    1048:	278b           	addi.n	a2, a7, 8
    104a:	1a6142        	s32i	a4, a1, 104
    104d:	142142        	l32i	a4, a1, 80
    1050:	8129           	s32i.n	a2, a1, 32
    1052:	2b8b           	addi.n	a2, a11, 8
    1054:	55da           	add.n	a5, a5, a13
    1056:	d129           	s32i.n	a2, a1, 52
    1058:	2c8b           	addi.n	a2, a12, 8
    105a:	66da           	add.n	a6, a6, a13
    105c:	c159           	s32i.n	a5, a1, 48
    105e:	9158           	l32i.n	a5, a1, 36
    1060:	256122        	s32i	a2, a1, 148
    1063:	241b           	addi.n	a2, a4, 1
    1065:	226162        	s32i	a6, a1, 136
    1068:	7168           	l32i.n	a6, a1, 28
    106a:	5178           	l32i.n	a7, a1, 20
    106c:	212120        	srai	a2, a2, 1
    106f:	33da           	add.n	a3, a3, a13
    1071:	99da           	add.n	a9, a9, a13
    1073:	b25a           	add.n	a11, a2, a5
    1075:	c02520        	sub	a2, a5, a2
    1078:	1c6132        	s32i	a3, a1, 112
    107b:	371b           	addi.n	a3, a7, 1
    107d:	1b6192        	s32i	a9, a1, 108
    1080:	9129           	s32i.n	a2, a1, 36
    1082:	261b           	addi.n	a2, a6, 1
    1084:	162192        	l32i	a9, a1, 88
    1087:	eeda           	add.n	a14, a14, a13
    1089:	212120        	srai	a2, a2, 1
    108c:	213130        	srai	a3, a3, 1
    108f:	523a           	add.n	a5, a2, a3
    1091:	2061e2        	s32i	a14, a1, 128
    1094:	ffda           	add.n	a15, a15, a13
    1096:	aada           	add.n	a10, a10, a13
    1098:	c02230        	sub	a2, a2, a3
    109b:	41d8           	l32i.n	a13, a1, 16
    109d:	1521e2        	l32i	a14, a1, 84
    10a0:	1f61a2        	s32i	a10, a1, 124
    10a3:	7129           	s32i.n	a2, a1, 28
    10a5:	291b           	addi.n	a2, a9, 1
    10a7:	a81b           	addi.n	a10, a8, 1
    10a9:	2131a0        	srai	a3, a10, 1
    10ac:	212120        	srai	a2, a2, 1
    10af:	6168           	l32i.n	a6, a1, 24
    10b1:	c23a           	add.n	a12, a2, a3
    10b3:	c07230        	sub	a7, a2, a3
    10b6:	2d1b           	addi.n	a2, a13, 1
    10b8:	3e1b           	addi.n	a3, a14, 1
    10ba:	212120        	srai	a2, a2, 1
    10bd:	213130        	srai	a3, a3, 1
    10c0:	1d21a2        	l32i	a10, a1, 116
    10c3:	2161f2        	s32i	a15, a1, 132
    10c6:	f23a           	add.n	a15, a2, a3
    10c8:	c0e230        	sub	a14, a2, a3
    10cb:	261b           	addi.n	a2, a6, 1
    10cd:	212120        	srai	a2, a2, 1
    10d0:	2181f0        	srai	a8, a15, 1
    10d3:	5129           	s32i.n	a2, a1, 20
    10d5:	22aa           	add.n	a2, a2, a10
    10d7:	381b           	addi.n	a3, a8, 1
    10d9:	212120        	srai	a2, a2, 1
    10dc:	21c1c0        	srai	a12, a12, 1
    10df:	219130        	srai	a9, a3, 1
    10e2:	3c1b           	addi.n	a3, a12, 1
    10e4:	221b           	addi.n	a2, a2, 1
    10e6:	215150        	srai	a5, a5, 1
    10e9:	21d130        	srai	a13, a3, 1
    10ec:	21f120        	srai	a15, a2, 1
    10ef:	251b           	addi.n	a2, a5, 1
    10f1:	212120        	srai	a2, a2, 1
    10f4:	69da           	add.n	a6, a9, a13
    10f6:	156192        	s32i	a9, a1, 84
    10f9:	172182        	l32i	a8, a1, 92
    10fc:	132192        	l32i	a9, a1, 76
    10ff:	1121c2        	l32i	a12, a1, 68
    1102:	32fa           	add.n	a3, a2, a15
    1104:	1661d2        	s32i	a13, a1, 88
    1107:	61f9           	s32i.n	a15, a1, 24
    1109:	4129           	s32i.n	a2, a1, 16
    110b:	263a           	add.n	a2, a6, a3
    110d:	1221f2        	l32i	a15, a1, 72
    1110:	1021d2        	l32i	a13, a1, 64
    1113:	336132        	s32i	a3, a1, 204
    1116:	3c1b           	addi.n	a3, a12, 1
    1118:	0829           	s32i.n	a2, a8, 0
    111a:	291b           	addi.n	a2, a9, 1
    111c:	212120        	srai	a2, a2, 1
    111f:	213130        	srai	a3, a3, 1
    1122:	923a           	add.n	a9, a2, a3
    1124:	4f1b           	addi.n	a4, a15, 1
    1126:	c02230        	sub	a2, a2, a3
    1129:	3d1b           	addi.n	a3, a13, 1
    112b:	146162        	s32i	a6, a1, 80
    112e:	216130        	srai	a6, a3, 1
    1131:	215140        	srai	a5, a4, 1
    1134:	c03650        	sub	a3, a6, a5
    1137:	832a           	add.n	a8, a3, a2
    1139:	21c180        	srai	a12, a8, 1
    113c:	c04320        	sub	a4, a3, a2
    113f:	3c1b           	addi.n	a3, a12, 1
    1141:	c0fe70        	sub	a15, a14, a7
    1144:	21d130        	srai	a13, a3, 1
    1147:	2131f0        	srai	a3, a15, 1
    114a:	331b           	addi.n	a3, a3, 1
    114c:	fbc9c1        	l32r	a12, 70 (5a82799a <_end+0x5a8254f2>)
    114f:	213130        	srai	a3, a3, 1
    1152:	126132        	s32i	a3, a1, 72
    1155:	33da           	add.n	a3, a3, a13
    1157:	8223c0        	mull	a2, a3, a12
    115a:	b283c0        	mulsh	a8, a3, a12
    115d:	1361d2        	s32i	a13, a1, 76
    1160:	052f20        	extui	a2, a2, 31, 1
    1163:	de7a           	add.n	a13, a14, a7
    1165:	908820        	addx2	a8, a8, a2
    1168:	2121d0        	srai	a2, a13, 1
    116b:	221b           	addi.n	a2, a2, 1
    116d:	21f140        	srai	a15, a4, 1
    1170:	21e120        	srai	a14, a2, 1
    1173:	2f1b           	addi.n	a2, a15, 1
    1175:	212120        	srai	a2, a2, 1
    1178:	106122        	s32i	a2, a1, 64
    117b:	c022e0        	sub	a2, a2, a14
    117e:	8272c0        	mull	a7, a2, a12
    1181:	b242c0        	mulsh	a4, a2, a12
    1184:	f1c8           	l32i.n	a12, a1, 60
    1186:	e1f8           	l32i.n	a15, a1, 56
    1188:	057f70        	extui	a7, a7, 31, 1
    118b:	dc1b           	addi.n	a13, a12, 1
    118d:	2f1b           	addi.n	a2, a15, 1
    118f:	1161e2        	s32i	a14, a1, 68
    1192:	90e470        	addx2	a14, a4, a7
    1195:	765a           	add.n	a7, a6, a5
    1197:	2151d0        	srai	a5, a13, 1
    119a:	216120        	srai	a6, a2, 1
    119d:	214170        	srai	a4, a7, 1
    11a0:	756a           	add.n	a7, a5, a6
    11a2:	219190        	srai	a9, a9, 1
    11a5:	2131b0        	srai	a3, a11, 1
    11a8:	21b170        	srai	a11, a7, 1
    11ab:	441b           	addi.n	a4, a4, 1
    11ad:	991b           	addi.n	a9, a9, 1
    11af:	c31b           	addi.n	a12, a3, 1
    11b1:	bb1b           	addi.n	a11, a11, 1
    11b3:	214140        	srai	a4, a4, 1
    11b6:	219190        	srai	a9, a9, 1
    11b9:	21c1c0        	srai	a12, a12, 1
    11bc:	21b1b0        	srai	a11, a11, 1
    11bf:	f49a           	add.n	a15, a4, a9
    11c1:	dbca           	add.n	a13, a11, a12
    11c3:	e1f9           	s32i.n	a15, a1, 56
    11c5:	3fda           	add.n	a3, a15, a13
    11c7:	182172        	l32i	a7, a1, 96
    11ca:	51f8           	l32i.n	a15, a1, 20
    11cc:	c05560        	sub	a5, a5, a6
    11cf:	0739           	s32i.n	a3, a7, 0
    11d1:	c03af0        	sub	a3, a10, a15
    11d4:	9178           	l32i.n	a7, a1, 36
    11d6:	71f8           	l32i.n	a15, a1, 28
    11d8:	216130        	srai	a6, a3, 1
    11db:	661b           	addi.n	a6, a6, 1
    11dd:	215150        	srai	a5, a5, 1
    11e0:	212160        	srai	a2, a6, 1
    11e3:	2161f0        	srai	a6, a15, 1
    11e6:	21a170        	srai	a10, a7, 1
    11e9:	551b           	addi.n	a5, a5, 1
    11eb:	761b           	addi.n	a7, a6, 1
    11ed:	f1d9           	s32i.n	a13, a1, 60
    11ef:	da1b           	addi.n	a13, a10, 1
    11f1:	215150        	srai	a5, a5, 1
    11f4:	21d1d0        	srai	a13, a13, 1
    11f7:	217170        	srai	a7, a7, 1
    11fa:	c0ad70        	sub	a10, a13, a7
    11fd:	652a           	add.n	a6, a5, a2
    11ff:	316182        	s32i	a8, a1, 196
    1202:	3261e2        	s32i	a14, a1, 200
    1205:	3eaa           	add.n	a3, a14, a10
    1207:	1d61a2        	s32i	a10, a1, 116
    120a:	e86a           	add.n	a14, a8, a6
    120c:	5169           	s32i.n	a6, a1, 20
    120e:	2e21a2        	l32i	a10, a1, 184
    1211:	2421f2        	l32i	a15, a1, 144
    1214:	4168           	l32i.n	a6, a1, 16
    1216:	6188           	l32i.n	a8, a1, 24
    1218:	0ae9           	s32i.n	a14, a10, 0
    121a:	77da           	add.n	a7, a7, a13
    121c:	c09940        	sub	a9, a9, a4
    121f:	0f39           	s32i.n	a3, a15, 0
    1221:	c06860        	sub	a6, a8, a6
    1224:	1321d2        	l32i	a13, a1, 76
    1227:	1221f2        	l32i	a15, a1, 72
    122a:	4199           	s32i.n	a9, a1, 16
    122c:	9169           	s32i.n	a6, a1, 36
    122e:	c09690        	sub	a9, a6, a9
    1231:	c06250        	sub	a6, a2, a5
    1234:	fb8f51        	l32r	a5, 70 (5a82799a <_end+0x5a8254f2>)
    1237:	2d21e2        	l32i	a14, a1, 180
    123a:	c03df0        	sub	a3, a13, a15
    123d:	c04cb0        	sub	a4, a12, a11
    1240:	1621b2        	l32i	a11, a1, 88
    1243:	1521c2        	l32i	a12, a1, 84
    1246:	1121d2        	l32i	a13, a1, 68
    1249:	1021f2        	l32i	a15, a1, 64
    124c:	828350        	mull	a8, a3, a5
    124f:	0e99           	s32i.n	a9, a14, 0
    1251:	2c2192        	l32i	a9, a1, 176
    1254:	c02cb0        	sub	a2, a12, a11
    1257:	05cf80        	extui	a12, a8, 31, 1
    125a:	8dfa           	add.n	a8, a13, a15
    125c:	fb86d1        	l32r	a13, 74 (a57d8666 <_end+0xa57d61be>)
    125f:	c0b420        	sub	a11, a4, a2
    1262:	09b9           	s32i.n	a11, a9, 0
    1264:	b2b350        	mulsh	a11, a3, a5
    1267:	82f8d0        	mull	a15, a8, a13
    126a:	90bbc0        	addx2	a11, a11, a12
    126d:	b2c8d0        	mulsh	a12, a8, a13
    1270:	05dff0        	extui	a13, a15, 31, 1
    1273:	90ccd0        	addx2	a12, a12, a13
    1276:	7179           	s32i.n	a7, a1, 28
    1278:	dc7a           	add.n	a13, a12, a7
    127a:	272172        	l32i	a7, a1, 156
    127d:	232152        	l32i	a5, a1, 140
    1280:	3b6a           	add.n	a3, a11, a6
    1282:	6169           	s32i.n	a6, a1, 24
    1284:	0739           	s32i.n	a3, a7, 0
    1286:	05d9           	s32i.n	a13, a5, 0
    1288:	f168           	l32i.n	a6, a1, 60
    128a:	e188           	l32i.n	a8, a1, 56
    128c:	1421d2        	l32i	a13, a1, 80
    128f:	3321f2        	l32i	a15, a1, 204
    1292:	c03680        	sub	a3, a6, a8
    1295:	2b2182        	l32i	a8, a1, 172
    1298:	c05fd0        	sub	a5, a15, a13
    129b:	322162        	l32i	a6, a1, 200
    129e:	1d21d2        	l32i	a13, a1, 116
    12a1:	0859           	s32i.n	a5, a8, 0
    12a3:	3721f2        	l32i	a15, a1, 220
    12a6:	c0dd60        	sub	a13, a13, a6
    12a9:	312152        	l32i	a5, a1, 196
    12ac:	5168           	l32i.n	a6, a1, 20
    12ae:	0f39           	s32i.n	a3, a15, 0
    12b0:	c03650        	sub	a3, a6, a5
    12b3:	292162        	l32i	a6, a1, 164
    12b6:	2a2152        	l32i	a5, a1, 168
    12b9:	0639           	s32i.n	a3, a6, 0
    12bb:	05d9           	s32i.n	a13, a5, 0
    12bd:	324a           	add.n	a3, a2, a4
    12bf:	4148           	l32i.n	a4, a1, 16
    12c1:	91d8           	l32i.n	a13, a1, 36
    12c3:	44da           	add.n	a4, a4, a13
    12c5:	2821d2        	l32i	a13, a1, 160
    12c8:	0d49           	s32i.n	a4, a13, 0
    12ca:	342142        	l32i	a4, a1, 208
    12cd:	0439           	s32i.n	a3, a4, 0
    12cf:	7138           	l32i.n	a3, a1, 28
    12d1:	c023c0        	sub	a2, a3, a12
    12d4:	61c8           	l32i.n	a12, a1, 24
    12d6:	c03cb0        	sub	a3, a12, a11
    12d9:	3521c2        	l32i	a12, a1, 212
    12dc:	3621b2        	l32i	a11, a1, 216
    12df:	0c39           	s32i.n	a3, a12, 0
    12e1:	0b29           	s32i.n	a2, a11, 0
    12e3:	302122        	l32i	a2, a1, 192
    12e6:	172132        	l32i	a3, a1, 92
    12e9:	aa2a           	add.n	a10, a10, a2
    12eb:	332a           	add.n	a3, a3, a2
    12ed:	176132        	s32i	a3, a1, 92
    12f0:	182132        	l32i	a3, a1, 96
    12f3:	2e61a2        	s32i	a10, a1, 184
    12f6:	ee2a           	add.n	a14, a14, a2
    12f8:	2421a2        	l32i	a10, a1, 144
    12fb:	2d61e2        	s32i	a14, a1, 180
    12fe:	2321e2        	l32i	a14, a1, 140
    1301:	332a           	add.n	a3, a3, a2
    1303:	772a           	add.n	a7, a7, a2
    1305:	186132        	s32i	a3, a1, 96
    1308:	3a2a           	add.n	a3, a10, a2
    130a:	276172        	s32i	a7, a1, 156
    130d:	262172        	l32i	a7, a1, 152
    1310:	246132        	s32i	a3, a1, 144
    1313:	992a           	add.n	a9, a9, a2
    1315:	dd2a           	add.n	a13, a13, a2
    1317:	552a           	add.n	a5, a5, a2
    1319:	662a           	add.n	a6, a6, a2
    131b:	882a           	add.n	a8, a8, a2
    131d:	3e2a           	add.n	a3, a14, a2
    131f:	2c6192        	s32i	a9, a1, 176
    1322:	bb2a           	add.n	a11, a11, a2
    1324:	cc2a           	add.n	a12, a12, a2
    1326:	442a           	add.n	a4, a4, a2
    1328:	ff2a           	add.n	a15, a15, a2
    132a:	2861d2        	s32i	a13, a1, 160
    132d:	2a6152        	s32i	a5, a1, 168
    1330:	296162        	s32i	a6, a1, 164
    1333:	2b6182        	s32i	a8, a1, 172
    1336:	236132        	s32i	a3, a1, 140

00001339 <FFT8N+0x6dd>:
    1339:	f01d           	retw.n

0000133b <FFT8N+0x6df>:
	...

0000133c <fix_fft10>:
    133c:	01c136        	entry	a1, 224
    133f:	00a452        	movi	a5, 0x400
    1342:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    1345:	600204        	ae_lq32f.i	aeq0, a2, 0
    1348:	d5e2bd224f 	{ ae_lq32f.i	aeq1, a2, 16; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
    134d:	01d142        	addmi	a4, a1, 0x100
    1350:	d4e3c9044e 	{ addi	a4, a4, -112; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1355:	fe3442039e 	{ addi	a9, a3, 32; ae_roundsq32asym	aeq2, aeq2 }
    135a:	04ed           	mov.n	a14, a4
    135c:	40c282        	addi	a8, a2, 64
    135f:	626e04        	ae_sq32f.iu	aeq2, a14, 0
    1362:	608944        	ae_lq32f.i	aeq2, a9, 16
    1365:	60c304        	ae_lq32f.i	aeq3, a3, 0
    1368:	d7e3c4036e 	{ addi	a6, a3, 64; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    136d:	600344        	ae_lq32f.i	aeq0, a3, 16
    1370:	ff3c7a213f 	{ ae_sq56s.i	aeq2, a1, 24; ae_roundsq32asym	aeq3, aeq3 }
    1375:	608804        	ae_lq32f.i	aeq2, a8, 0
    1378:	631174        	ae_sq56s.i	aeq1, a1, 56
    137b:	604884        	ae_lq32f.i	aeq1, a8, -32
    137e:	78c1f2        	addi	a15, a1, 120
    1381:	630124        	ae_sq56s.i	aeq0, a1, 16
    1384:	632164        	ae_sq56s.i	aeq2, a1, 48
    1387:	608604        	ae_lq32f.i	aeq2, a6, 0
    138a:	631f94        	ae_sq56s.i	aeq1, a15, -56
    138d:	604904        	ae_lq32f.i	aeq1, a9, 0
    1390:	6008c4        	ae_lq32f.i	aeq0, a8, -16
    1393:	20c272        	addi	a7, a2, 32
    1396:	d5e2ba215f 	{ ae_sq56s.i	aeq2, a1, 40; ae_mulfq32sp16u.l	aeq2, aeq0, aep0 }
    139b:	631144        	ae_sq56s.i	aeq1, a1, 32
    139e:	fe347da13f 	{ ae_lq56.i	aeq1, a1, 24; ae_roundsq32asym	aeq2, aeq2 }
    13a3:	d4e3b9fe1f 	{ ae_sq32f.iu	aeq3, a14, 4; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    13a8:	61c124        	ae_lq56.i	aeq3, a1, 16
    13ab:	fc2479ee1f 	{ ae_sq32f.iu	aeq2, a14, 4; ae_roundsq32asym	aeq0, aeq0 }
    13b0:	d7e3fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    13b5:	d7e2bda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    13ba:	fc2c79ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_roundsq32asym	aeq0, aeq1 }
    13bf:	614154        	ae_lq56.i	aeq1, a1, 40
    13c2:	d4e3f9ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    13c7:	fc3c7def9f 	{ ae_lq56.i	aeq3, a15, -56; ae_roundsq32asym	aeq0, aeq3 }
    13cc:	fc3479ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_roundsq32asym	aeq0, aeq2 }
    13d1:	d7e3fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    13d6:	d7e2b9ce1f 	{ ae_sq32f.iu	aeq0, a14, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    13db:	fd2c4641be 	{ addi	a11, a1, 100; ae_roundsq32asym	aeq1, aeq1 }
    13e0:	176162        	s32i	a6, a1, 92
    13e3:	fd3c79de1f 	{ ae_sq32f.iu	aeq1, a14, 4; ae_roundsq32asym	aeq1, aeq3 }
    13e8:	ff3446016e 	{ addi	a6, a1, 96; ae_roundsq32asym	aeq3, aeq2 }
    13ed:	fb1d51        	l32r	a5, 64 (15c <fix_fft5_stage>)
    13f0:	625e14        	ae_sq32f.iu	aeq1, a14, 4
    13f3:	04cd           	mov.n	a12, a4
    13f5:	06ad           	mov.n	a10, a6
    13f7:	560fa4        	ae_sp24x2s.i	aep0, a15, -48
    13fa:	166182        	s32i	a8, a1, 88
    13fd:	156192        	s32i	a9, a1, 84
    1400:	627e14        	ae_sq32f.iu	aeq3, a14, 4
    1403:	0005e0        	callx8	a5
    1406:	78c1a2        	addi	a10, a1, 120
    1409:	604724        	ae_lq32f.i	aeq1, a7, 8
    140c:	540aa4        	ae_lp24x2.i	aep0, a10, -48
    140f:	d4e3f1518e 	{ l32i	a8, a1, 84; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1414:	059d           	mov.n	a9, a5
    1416:	045d           	mov.n	a5, a4
    1418:	fd2c7d082f 	{ ae_lq32f.i	aeq0, a8, 8; ae_roundsq32asym	aeq1, aeq1 }
    141d:	d4e2bd432f 	{ ae_lq32f.i	aeq2, a3, 8; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1422:	625404        	ae_sq32f.iu	aeq1, a4, 0
    1425:	604264        	ae_lq32f.i	aeq1, a2, 24
    1428:	1621e2        	l32i	a14, a1, 88
    142b:	632124        	ae_sq56s.i	aeq2, a1, 16
    142e:	631174        	ae_sq56s.i	aeq1, a1, 56
    1431:	604364        	ae_lq32f.i	aeq1, a3, 24
    1434:	631164        	ae_sq56s.i	aeq1, a1, 48
    1437:	614124        	ae_lq56.i	aeq1, a1, 16
    143a:	1721f2        	l32i	a15, a1, 92
    143d:	60c224        	ae_lq32f.i	aeq3, a2, 8
    1440:	d4e3ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1445:	d7e3fd2e2f 	{ ae_lq32f.i	aeq1, a14, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    144a:	608764        	ae_lq32f.i	aeq2, a7, 24
    144d:	ff3c7a114f 	{ ae_sq56s.i	aeq1, a1, 32; ae_roundsq32asym	aeq3, aeq3 }
    1452:	614134        	ae_lq56.i	aeq1, a1, 24
    1455:	632154        	ae_sq56s.i	aeq2, a1, 40
    1458:	fc2c7a012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_roundsq32asym	aeq0, aeq1 }
    145d:	604f24        	ae_lq32f.i	aeq1, a15, 8
    1460:	624414        	ae_sq32f.iu	aeq0, a4, 4
    1463:	631134        	ae_sq56s.i	aeq1, a1, 24
    1466:	614154        	ae_lq56.i	aeq1, a1, 40
    1469:	d4e3fd486f 	{ ae_lq32f.i	aeq2, a8, 24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    146e:	d7e2b9f41f 	{ ae_sq32f.iu	aeq3, a4, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1473:	61c124        	ae_lq56.i	aeq3, a1, 16
    1476:	fc3c7de17f 	{ ae_lq56.i	aeq3, a1, 56; ae_roundsq32asym	aeq0, aeq3 }
    147b:	fc2c79c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_roundsq32asym	aeq0, aeq1 }
    1480:	d7e3fda16f 	{ ae_lq56.i	aeq1, a1, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1485:	d4e3f9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    148a:	fc347dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_roundsq32asym	aeq0, aeq2 }
    148f:	d7e2b9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1494:	fc3c7de13f 	{ ae_lq56.i	aeq3, a1, 24; ae_roundsq32asym	aeq0, aeq3 }
    1499:	d7e3f9c41f 	{ ae_sq32f.iu	aeq0, a4, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    149e:	fd2c53a55f 	{ or	a10, a5, a5; ae_roundsq32asym	aeq1, aeq1 }
    14a3:	01d1b2        	addmi	a11, a1, 0x100
    14a6:	fe3479d41f 	{ ae_sq32f.iu	aeq1, a4, 4; ae_roundsq32asym	aeq2, aeq2 }
    14ab:	ff3c494bbe 	{ addi	a11, a11, -108; ae_roundsq32asym	aeq3, aeq3 }
    14b0:	626414        	ae_sq32f.iu	aeq2, a4, 4
    14b3:	05cd           	mov.n	a12, a5
    14b5:	627414        	ae_sq32f.iu	aeq3, a4, 4
    14b8:	0009e0        	callx8	a9
    14bb:	601604        	ae_lq32f.iu	aeq0, a6, 0
    14be:	60d504        	ae_lq32f.iu	aeq3, a5, 0
    14c1:	fae63d361f 	{ ae_lq32f.iu	aeq1, a6, 4; ae_addq56	aeq2, aeq0, aeq3 }
    14c6:	f8a6fa212f 	{ ae_sq56s.i	aeq2, a1, 16; ae_subq56	aeq0, aeq0, aeq3 }
    14cb:	609514        	ae_lq32f.iu	aeq2, a5, 4
    14ce:	f8ea3f07ef 	{ ae_trunca32q48	a7, aeq0; ae_addq56	aeq0, aeq1, aeq2 }
    14d3:	f9aafde12f 	{ ae_lq56.i	aeq3, a1, 16; ae_subq56	aeq1, aeq1, aeq2 }
    14d8:	36b404        	ae_trunca32q48	a4, aeq3
    14db:	630124        	ae_sq56s.i	aeq0, a1, 16
    14de:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    14e1:	601514        	ae_lq32f.iu	aeq0, a5, 4
    14e4:	618124        	ae_lq56.i	aeq2, a1, 16
    14e7:	f97a3f19ef 	{ ae_trunca32q48	a9, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    14ec:	f83aff28ef 	{ ae_trunca32q48	a8, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
    14f1:	631124        	ae_sq56s.i	aeq1, a1, 16
    14f4:	609614        	ae_lq32f.iu	aeq2, a6, 4
    14f7:	605514        	ae_lq32f.iu	aeq1, a5, 4
    14fa:	61c124        	ae_lq56.i	aeq3, a1, 16
    14fd:	f8763f0bef 	{ ae_trunca32q48	a11, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
    1502:	f936ff3aef 	{ ae_trunca32q48	a10, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
    1507:	630124        	ae_sq56s.i	aeq0, a1, 16
    150a:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    150d:	601514        	ae_lq32f.iu	aeq0, a5, 4
    1510:	618124        	ae_lq56.i	aeq2, a1, 16
    1513:	f97a3f1def 	{ ae_trunca32q48	a13, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    1518:	f83aff2cef 	{ ae_trunca32q48	a12, aeq2; ae_subq56	aeq0, aeq3, aeq0 }
    151d:	631124        	ae_sq56s.i	aeq1, a1, 16
    1520:	609614        	ae_lq32f.iu	aeq2, a6, 4
    1523:	605514        	ae_lq32f.iu	aeq1, a5, 4
    1526:	61c124        	ae_lq56.i	aeq3, a1, 16
    1529:	f8763f0fef 	{ ae_trunca32q48	a15, aeq0; ae_addq56	aeq0, aeq2, aeq1 }
    152e:	f936ff3eef 	{ ae_trunca32q48	a14, aeq3; ae_subq56	aeq1, aeq2, aeq1 }
    1533:	630124        	ae_sq56s.i	aeq0, a1, 16
    1536:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    1539:	601514        	ae_lq32f.iu	aeq0, a5, 4
    153c:	0249           	s32i.n	a4, a2, 0
    153e:	a279           	s32i.n	a7, a2, 40
    1540:	0389           	s32i.n	a8, a3, 0
    1542:	f97a3f18ef 	{ ae_trunca32q48	a8, aeq1; ae_addq56	aeq1, aeq3, aeq0 }
    1547:	f83afdc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_subq56	aeq0, aeq3, aeq0 }
    154c:	631124        	ae_sq56s.i	aeq1, a1, 16
    154f:	36a704        	ae_trunca32q48	a7, aeq2
    1552:	609614        	ae_lq32f.iu	aeq2, a6, 4
    1555:	61c124        	ae_lq56.i	aeq3, a1, 16
    1558:	a399           	s32i.n	a9, a3, 40
    155a:	36b904        	ae_trunca32q48	a9, aeq3
    155d:	60d614        	ae_lq32f.iu	aeq3, a6, 4
    1560:	42a9           	s32i.n	a10, a2, 16
    1562:	fc147f0aef 	{ ae_trunca32q48	a10, aeq0; ae_movq56	aeq0, aeq2 }
    1567:	605514        	ae_lq32f.iu	aeq1, a5, 4
    156a:	fb763a312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_addq56	aeq3, aeq2, aeq1 }
    156f:	f926fd551f 	{ ae_lq32f.iu	aeq2, a5, 4; ae_subq56	aeq1, aeq0, aeq1 }
    1574:	610124        	ae_lq56.i	aeq0, a1, 16
    1577:	e2b9           	s32i.n	a11, a2, 56
    1579:	43c9           	s32i.n	a12, a3, 16
    157b:	36bb04        	ae_trunca32q48	a11, aeq3
    157e:	f9e23f1cef 	{ ae_trunca32q48	a12, aeq1; ae_addq56	aeq1, aeq0, aeq2 }
    1583:	f8a2fd761f 	{ ae_lq32f.iu	aeq3, a6, 4; ae_subq56	aeq0, aeq0, aeq2 }
    1588:	369604        	ae_trunca32q48	a6, aeq1
    158b:	605514        	ae_lq32f.iu	aeq1, a5, 4
    158e:	fa7e14e3df 	{ s32i.n	a13, a3, 56; ae_addq56	aeq2, aeq3, aeq1 }
    1593:	82e9           	s32i.n	a14, a2, 32
    1595:	1262f2        	s32i	a15, a2, 72
    1598:	f93eff0def 	{ ae_trunca32q48	a13, aeq0; ae_subq56	aeq1, aeq3, aeq1 }
    159d:	36ae04        	ae_trunca32q48	a14, aeq2
    15a0:	369f04        	ae_trunca32q48	a15, aeq1
    15a3:	8379           	s32i.n	a7, a3, 32
    15a5:	126382        	s32i	a8, a3, 72
    15a8:	c299           	s32i.n	a9, a2, 48
    15aa:	22a9           	s32i.n	a10, a2, 8
    15ac:	c3b9           	s32i.n	a11, a3, 48
    15ae:	23c9           	s32i.n	a12, a3, 8
    15b0:	106262        	s32i	a6, a2, 64
    15b3:	62d9           	s32i.n	a13, a2, 24
    15b5:	1063e2        	s32i	a14, a3, 64
    15b8:	63f9           	s32i.n	a15, a3, 24
    15ba:	f01d           	retw.n

000015bc <fix_fft15>:
    15bc:	02e136        	entry	a1, 0x170
    15bf:	01d1d2        	addmi	a13, a1, 0x100
    15c2:	608264        	ae_lq32f.i	aeq2, a2, 24
    15c5:	60c364        	ae_lq32f.i	aeq3, a3, 24
    15c8:	632114        	ae_sq56s.i	aeq2, a1, 8
    15cb:	633124        	ae_sq56s.i	aeq3, a1, 16
    15ce:	608244        	ae_lq32f.i	aeq2, a2, 16
    15d1:	80cdd2        	addi	a13, a13, -128
    15d4:	60c344        	ae_lq32f.i	aeq3, a3, 16
    15d7:	01d1e2        	addmi	a14, a1, 0x100
    15da:	632d74        	ae_sq56s.i	aeq2, a13, 56
    15dd:	633e94        	ae_sq56s.i	aeq3, a14, -56
    15e0:	60c324        	ae_lq32f.i	aeq3, a3, 8
    15e3:	20c272        	addi	a7, a2, 32
    15e6:	20c362        	addi	a6, a3, 32
    15e9:	608224        	ae_lq32f.i	aeq2, a2, 8
    15ec:	78c1f2        	addi	a15, a1, 120
    15ef:	632f74        	ae_sq56s.i	aeq2, a15, 56
    15f2:	633e84        	ae_sq56s.i	aeq3, a14, -64
    15f5:	608744        	ae_lq32f.i	aeq2, a7, 16
    15f8:	60c644        	ae_lq32f.i	aeq3, a6, 16
    15fb:	40c292        	addi	a9, a2, 64
    15fe:	40c3b2        	addi	a11, a3, 64
    1601:	632144        	ae_sq56s.i	aeq2, a1, 32
    1604:	633134        	ae_sq56s.i	aeq3, a1, 24
    1607:	608924        	ae_lq32f.i	aeq2, a9, 8
    160a:	60cb24        	ae_lq32f.i	aeq3, a11, 8
    160d:	60c282        	addi	a8, a2, 96
    1610:	60c3a2        	addi	a10, a3, 96
    1613:	632154        	ae_sq56s.i	aeq2, a1, 40
    1616:	633164        	ae_sq56s.i	aeq3, a1, 48
    1619:	608804        	ae_lq32f.i	aeq2, a8, 0
    161c:	60ca04        	ae_lq32f.i	aeq3, a10, 0
    161f:	632174        	ae_sq56s.i	aeq2, a1, 56
    1622:	633f94        	ae_sq56s.i	aeq3, a15, -56
    1625:	608724        	ae_lq32f.i	aeq2, a7, 8
    1628:	60c624        	ae_lq32f.i	aeq3, a6, 8
    162b:	00a452        	movi	a5, 0x400
    162e:	632fa4        	ae_sq56s.i	aeq2, a15, -48
    1631:	633fb4        	ae_sq56s.i	aeq3, a15, -40
    1634:	608904        	ae_lq32f.i	aeq2, a9, 0
    1637:	60cb04        	ae_lq32f.i	aeq3, a11, 0
    163a:	632fc4        	ae_sq56s.i	aeq2, a15, -32
    163d:	633fd4        	ae_sq56s.i	aeq3, a15, -24
    1640:	608964        	ae_lq32f.i	aeq2, a9, 24
    1643:	60cb64        	ae_lq32f.i	aeq3, a11, 24
    1646:	300554        	ae_cvtp24a16x2.ll	aep0, a5, a5
    1649:	600204        	ae_lq32f.i	aeq0, a2, 0
    164c:	01d1c2        	addmi	a12, a1, 0x100
    164f:	d4e2ba2fef 	{ ae_sq56s.i	aeq2, a15, -16; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1654:	633ff4        	ae_sq56s.i	aeq3, a15, -8
    1657:	fc247d484f 	{ ae_lq32f.i	aeq2, a8, 16; ae_roundsq32asym	aeq0, aeq0 }
    165c:	60ca44        	ae_lq32f.i	aeq3, a10, 16
    165f:	d0ccc2        	addi	a12, a12, -48
    1662:	632f04        	ae_sq56s.i	aeq2, a15, 0
    1665:	633f14        	ae_sq56s.i	aeq3, a15, 8
    1668:	60cb44        	ae_lq32f.i	aeq3, a11, 16
    166b:	608944        	ae_lq32f.i	aeq2, a9, 16
    166e:	0c5d           	mov.n	a5, a12
    1670:	632f24        	ae_sq56s.i	aeq2, a15, 16
    1673:	633f34        	ae_sq56s.i	aeq3, a15, 24
    1676:	60ca24        	ae_lq32f.i	aeq3, a10, 8
    1679:	608824        	ae_lq32f.i	aeq2, a8, 8
    167c:	604304        	ae_lq32f.i	aeq1, a3, 0
    167f:	d4e3b9c50f 	{ ae_sq32f.iu	aeq0, a5, 0; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1684:	632f54        	ae_sq56s.i	aeq2, a15, 40
    1687:	fc247dc11f 	{ ae_lq56.i	aeq2, a1, 8; ae_roundsq32asym	aeq0, aeq0 }
    168c:	d7e2ba3f6f 	{ ae_sq56s.i	aeq3, a15, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1691:	60c704        	ae_lq32f.i	aeq3, a7, 0
    1694:	633114        	ae_sq56s.i	aeq3, a1, 8
    1697:	61c124        	ae_lq56.i	aeq3, a1, 16
    169a:	d6e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    169f:	fc347dc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_roundsq32asym	aeq0, aeq2 }
    16a4:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16a9:	d7e2bda13f 	{ ae_lq56.i	aeq1, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16ae:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16b3:	fc347dc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_roundsq32asym	aeq0, aeq2 }
    16b8:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16bd:	d7e2bda16f 	{ ae_lq56.i	aeq1, a1, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16c2:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16c7:	fc347dc17f 	{ ae_lq56.i	aeq2, a1, 56; ae_roundsq32asym	aeq0, aeq2 }
    16cc:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16d1:	d7e2bdaf9f 	{ ae_lq56.i	aeq1, a15, -56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16d6:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16db:	fc347dcfaf 	{ ae_lq56.i	aeq2, a15, -48; ae_roundsq32asym	aeq0, aeq2 }
    16e0:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16e5:	d7e2bdafbf 	{ ae_lq56.i	aeq1, a15, -40; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16ea:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    16ef:	fc347dcfcf 	{ ae_lq56.i	aeq2, a15, -32; ae_roundsq32asym	aeq0, aeq2 }
    16f4:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    16f9:	d7e2bdafdf 	{ ae_lq56.i	aeq1, a15, -24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    16fe:	d4e3f9c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1703:	fc347dcfef 	{ ae_lq56.i	aeq2, a15, -16; ae_roundsq32asym	aeq0, aeq2 }
    1708:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    170d:	d7e2bdafff 	{ ae_lq56.i	aeq1, a15, -8; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1712:	d4e3fd660f 	{ ae_lq32f.i	aeq3, a6, 0; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1717:	fc3479c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq2 }
    171c:	618f04        	ae_lq56.i	aeq2, a15, 0
    171f:	d7e2ba312f 	{ ae_sq56s.i	aeq3, a1, 16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1724:	60c764        	ae_lq32f.i	aeq3, a7, 24
    1727:	fc2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq1 }
    172c:	614f14        	ae_lq56.i	aeq1, a15, 8
    172f:	d4e3fa3f4f 	{ ae_sq56s.i	aeq3, a15, 32; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1734:	61cd74        	ae_lq56.i	aeq3, a13, 56
    1737:	fc3479c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq0, aeq2 }
    173c:	d7e3fdce9f 	{ ae_lq56.i	aeq2, a14, -56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1741:	fd2c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq1, aeq1 }
    1746:	d7e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    174b:	fd3c7def2f 	{ ae_lq56.i	aeq3, a15, 16; ae_roundsq32asym	aeq1, aeq3 }
    1750:	fd3479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq1, aeq2 }
    1755:	d7e3fdcf3f 	{ ae_lq56.i	aeq2, a15, 24; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    175a:	d7e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    175f:	fd3c7def5f 	{ ae_lq56.i	aeq3, a15, 40; ae_roundsq32asym	aeq1, aeq3 }
    1764:	fd3479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq1, aeq2 }
    1769:	d7e3fdcf6f 	{ ae_lq56.i	aeq2, a15, 48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    176e:	d7e2bd8f7f 	{ ae_lq56.i	aeq0, a15, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1773:	d4e2b9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1778:	fd3c7dee8f 	{ ae_lq56.i	aeq3, a14, -64; ae_roundsq32asym	aeq1, aeq3 }
    177d:	d7e3f9d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1782:	fd347dc11f 	{ ae_lq56.i	aeq2, a1, 8; ae_roundsq32asym	aeq1, aeq2 }
    1787:	fc2479d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    178c:	d7e2bda12f 	{ ae_lq56.i	aeq1, a1, 16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1791:	ff3c79c51f 	{ ae_sq32f.iu	aeq0, a5, 4; ae_roundsq32asym	aeq3, aeq3 }
    1796:	d4e3f9f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    179b:	fe347def4f 	{ ae_lq56.i	aeq3, a15, 32; ae_roundsq32asym	aeq2, aeq2 }
    17a0:	d7e3fd066f 	{ ae_lq32f.i	aeq0, a6, 24; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    17a5:	d4e2b9e51f 	{ ae_sq32f.iu	aeq2, a5, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    17aa:	fd2c53a22f 	{ or	a10, a2, a2; ae_roundsq32asym	aeq1, aeq1 }
    17af:	ff3c79d51f 	{ ae_sq32f.iu	aeq1, a5, 4; ae_roundsq32asym	aeq3, aeq3 }
    17b4:	fc2479f51f 	{ ae_sq32f.iu	aeq3, a5, 4; ae_roundsq32asym	aeq0, aeq0 }
    17b9:	624514        	ae_sq32f.iu	aeq0, a5, 4
    17bc:	fa3151        	l32r	a5, 80 (2a4 <fix_fft15_stage>)
    17bf:	03bd           	mov.n	a11, a3
    17c1:	04dd           	mov.n	a13, a4
    17c3:	0005e0        	callx8	a5
    17c6:	f01d           	retw.n

000017c8 <fix_fft30>:
    17c8:	04a136        	entry	a1, 0x250
    17cb:	037d           	mov.n	a7, a3
    17cd:	80a0f2        	movi	a15, 128
    17d0:	00a432        	movi	a3, 0x400
    17d3:	300334        	ae_cvtp24a16x2.ll	aep0, a3, a3
    17d6:	6067f4        	ae_lq32f.x	aeq1, a7, a15
    17d9:	78c192        	addi	a9, a1, 120
    17dc:	60c204        	ae_lq32f.i	aeq3, a2, 0
    17df:	02d1c2        	addmi	a12, a1, 0x200
    17e2:	d6e3fa199f 	{ ae_sq56s.i	aeq1, a9, -56; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    17e7:	600704        	ae_lq32f.i	aeq0, a7, 0
    17ea:	d4e2bbd2ff 	{ ae_lq32f.x	aeq2, a2, a15; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    17ef:	01d182        	addmi	a8, a1, 0x100
    17f2:	fd2c47c2ae 	{ addi	a10, a2, 124; ae_roundsq32asym	aeq1, aeq1 }
    17f7:	fc244b0cce 	{ addi	a12, a12, -80; ae_roundsq32asym	aeq0, aeq0 }
    17fc:	5608b4        	ae_sp24x2s.i	aep0, a8, -40
    17ff:	0c8d           	mov.n	a8, a12
    1801:	632174        	ae_sq56s.i	aeq2, a1, 56
    1804:	7cc792        	addi	a9, a7, 124
    1807:	608a54        	ae_lq32f.i	aeq2, a10, 20
    180a:	d6e2f9d80f 	{ ae_sq32f.iu	aeq1, a8, 0; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    180f:	20c2f2        	addi	a15, a2, 32
    1812:	c53c           	movi.n	a5, 60
    1814:	608954        	ae_lq32f.i	aeq2, a9, 20
    1817:	d7e280c06f 	{ movi	a6, 192; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    181c:	d15450        	mul16s	a5, a4, a5
    181f:	60cf44        	ae_lq32f.i	aeq3, a15, 16
    1822:	d26a           	add.n	a13, a2, a6
    1824:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1829:	d6e3c0a0ef 	{ movi	a14, 160; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    182e:	3f61d2        	s32i	a13, a1, 252
    1831:	ff3450d2ef 	{ add	a13, a2, a14; ae_roundsq32asym	aeq3, aeq2 }
    1836:	fd2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq1, aeq1 }
    183b:	4961a2        	s32i	a10, a1, 0x124
    183e:	b75a           	add.n	a11, a7, a5
    1840:	e25a           	add.n	a14, a2, a5
    1842:	025d           	mov.n	a5, a2
    1844:	c0a0a2        	movi	a10, 192
    1847:	627814        	ae_sq32f.iu	aeq3, a8, 4
    184a:	60a2a4        	ae_lq32f.x	aeq2, a2, a10
    184d:	01d262        	addmi	a6, a2, 0x100
    1850:	426122        	s32i	a2, a1, 0x108
    1853:	d7e2bc6a7f 	{ ae_lq32f.xu	aeq3, a10, a7; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1858:	072d           	mov.n	a2, a7
    185a:	3e6142        	s32i	a4, a1, 248
    185d:	625814        	ae_sq32f.iu	aeq1, a8, 4
    1860:	446172        	s32i	a7, a1, 0x110
    1863:	604744        	ae_lq32f.i	aeq1, a7, 16
    1866:	e0a042        	movi	a4, 224
    1869:	4b61b2        	s32i	a11, a1, 0x12c
    186c:	4a61e2        	s32i	a14, a1, 0x128
    186f:	436162        	s32i	a6, a1, 0x10c
    1872:	486192        	s32i	a9, a1, 0x120
    1875:	4061a2        	s32i	a10, a1, 0x100
    1878:	631134        	ae_sq56s.i	aeq1, a1, 24
    187b:	3061d2        	s32i	a13, a1, 192
    187e:	4561f2        	s32i	a15, a1, 0x114
    1881:	606544        	ae_lq32f.x	aeq1, a5, a4
    1884:	11a9           	s32i.n	a10, a1, 4
    1886:	78c172        	addi	a7, a1, 120
    1889:	631754        	ae_sq56s.i	aeq1, a7, 40
    188c:	607424        	ae_lq32f.xu	aeq1, a4, a2
    188f:	416142        	s32i	a4, a1, 0x104
    1892:	a0a042        	movi	a4, 160
    1895:	631144        	ae_sq56s.i	aeq1, a1, 32
    1898:	606544        	ae_lq32f.x	aeq1, a5, a4
    189b:	631154        	ae_sq56s.i	aeq1, a1, 40
    189e:	607424        	ae_lq32f.xu	aeq1, a4, a2
    18a1:	60c5e2        	addi	a14, a5, 96
    18a4:	631114        	ae_sq56s.i	aeq1, a1, 8
    18a7:	604544        	ae_lq32f.i	aeq1, a5, 16
    18aa:	631124        	ae_sq56s.i	aeq1, a1, 16
    18ad:	604e04        	ae_lq32f.i	aeq1, a14, 0
    18b0:	6317d4        	ae_sq56s.i	aeq1, a7, -24
    18b3:	604e44        	ae_lq32f.i	aeq1, a14, 16
    18b6:	631734        	ae_sq56s.i	aeq1, a7, 24
    18b9:	604e84        	ae_lq32f.i	aeq1, a14, -32
    18bc:	6317e4        	ae_sq56s.i	aeq1, a7, -16
    18bf:	604ec4        	ae_lq32f.i	aeq1, a14, -16
    18c2:	40c562        	addi	a6, a5, 64
    18c5:	631744        	ae_sq56s.i	aeq1, a7, 32
    18c8:	604f04        	ae_lq32f.i	aeq1, a15, 0
    18cb:	631164        	ae_sq56s.i	aeq1, a1, 48
    18ce:	604d44        	ae_lq32f.i	aeq1, a13, 16
    18d1:	3f21d2        	l32i	a13, a1, 252
    18d4:	2e61e2        	s32i	a14, a1, 184
    18d7:	631774        	ae_sq56s.i	aeq1, a7, 56
    18da:	1178           	l32i.n	a7, a1, 4
    18dc:	20c2f2        	addi	a15, a2, 32
    18df:	604d44        	ae_lq32f.i	aeq1, a13, 16
    18e2:	78c1e2        	addi	a14, a1, 120
    18e5:	631e04        	ae_sq56s.i	aeq1, a14, 0
    18e8:	604f04        	ae_lq32f.i	aeq1, a15, 0
    18eb:	60c292        	addi	a9, a2, 96
    18ee:	631e64        	ae_sq56s.i	aeq1, a14, 48
    18f1:	604744        	ae_lq32f.i	aeq1, a7, 16
    18f4:	631ef4        	ae_sq56s.i	aeq1, a14, -8
    18f7:	604904        	ae_lq32f.i	aeq1, a9, 0
    18fa:	631eb4        	ae_sq56s.i	aeq1, a14, -40
    18fd:	604944        	ae_lq32f.i	aeq1, a9, 16
    1900:	d6e3fa1e1f 	{ ae_sq56s.i	aeq1, a14, 8; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    1905:	60c984        	ae_lq32f.i	aeq3, a9, -32
    1908:	633ec4        	ae_sq56s.i	aeq3, a14, -32
    190b:	61c154        	ae_lq56.i	aeq3, a1, 40
    190e:	d7e3fd0f4f 	{ ae_lq32f.i	aeq0, a15, 16; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1913:	d4e2b3e1de 	{ l32i	a13, a1, 248; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1918:	633ea4        	ae_sq56s.i	aeq3, a14, -48
    191b:	fc247d69cf 	{ ae_lq32f.i	aeq3, a9, -16; ae_roundsq32asym	aeq0, aeq0 }
    1920:	40c2a2        	addi	a10, a2, 64
    1923:	633e24        	ae_sq56s.i	aeq3, a14, 16
    1926:	60c444        	ae_lq32f.i	aeq3, a4, 16
    1929:	633154        	ae_sq56s.i	aeq3, a1, 40
    192c:	61c114        	ae_lq56.i	aeq3, a1, 8
    192f:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1934:	0a2d           	mov.n	a2, a10
    1936:	fc347a311f 	{ ae_sq56s.i	aeq3, a1, 8; ae_roundsq32asym	aeq0, aeq2 }
    193b:	61ced4        	ae_lq56.i	aeq3, a14, -24
    193e:	d7e3bdeebf 	{ ae_lq56.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    1943:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1948:	d6e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    194d:	fe347de12f 	{ ae_lq56.i	aeq3, a1, 16; ae_roundsq32asym	aeq2, aeq2 }
    1952:	d6e3b9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq3, aep0 }
    1957:	ff2c7da13f 	{ ae_lq56.i	aeq1, a1, 24; ae_roundsq32asym	aeq3, aeq1 }
    195c:	627814        	ae_sq32f.iu	aeq3, a8, 4
    195f:	61cea4        	ae_lq56.i	aeq3, a14, -48
    1962:	d4e3ba012f 	{ ae_sq56s.i	aeq0, a1, 16; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    1967:	fe3c7daeef 	{ ae_lq56.i	aeq1, a14, -16; ae_roundsq32asym	aeq2, aeq3 }
    196c:	d5e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq1, aep0 }
    1971:	618114        	ae_lq56.i	aeq2, a1, 8
    1974:	fe347daecf 	{ ae_lq56.i	aeq1, a14, -32; ae_roundsq32asym	aeq2, aeq2 }
    1979:	d4e3ba013f 	{ ae_sq56s.i	aeq0, a1, 24; ae_mulfq32sp16u.l	aeq0, aeq1, aep0 }
    197e:	fe3c79e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_roundsq32asym	aeq2, aeq3 }
    1983:	fc247dee0f 	{ ae_lq56.i	aeq3, a14, 0; ae_roundsq32asym	aeq0, aeq0 }
    1988:	d7e3f9e81f 	{ ae_sq32f.iu	aeq2, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    198d:	618ef4        	ae_lq56.i	aeq2, a14, -8
    1990:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1995:	fc3c7dee3f 	{ ae_lq56.i	aeq3, a14, 24; ae_roundsq32asym	aeq0, aeq3 }
    199a:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    199f:	d7e3fdce1f 	{ ae_lq56.i	aeq2, a14, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    19a4:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    19a9:	fc3c7dee5f 	{ ae_lq56.i	aeq3, a14, 40; ae_roundsq32asym	aeq0, aeq3 }
    19ae:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    19b3:	d7e3fdc14f 	{ ae_lq56.i	aeq2, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    19b8:	d6e2fdce4f 	{ ae_lq56.i	aeq2, a14, 32; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    19bd:	624814        	ae_sq32f.iu	aeq0, a8, 4
    19c0:	631144        	ae_sq56s.i	aeq1, a1, 32
    19c3:	614124        	ae_lq56.i	aeq1, a1, 16
    19c6:	fc2c53744f 	{ or	a7, a4, a4; ae_roundsq32asym	aeq0, aeq1 }
    19cb:	d6e2fdc13f 	{ ae_lq56.i	aeq2, a1, 24; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    19d0:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    19d5:	618e24        	ae_lq56.i	aeq2, a14, 16
    19d8:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    19dd:	d7e2bda17f 	{ ae_lq56.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    19e2:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    19e7:	fc347dce9f 	{ ae_lq56.i	aeq2, a14, -56; ae_roundsq32asym	aeq0, aeq2 }
    19ec:	d6e2fa117f 	{ ae_sq56s.i	aeq1, a1, 56; ae_mulfq32sp16u.l	aeq1, aeq2, aep0 }
    19f1:	fe3c7de16f 	{ ae_lq56.i	aeq3, a1, 48; ae_roundsq32asym	aeq2, aeq3 }
    19f6:	624814        	ae_sq32f.iu	aeq0, a8, 4
    19f9:	d6e3fa1e9f 	{ ae_sq56s.i	aeq1, a14, -56; ae_mulfq32sp16u.l	aeq1, aeq3, aep0 }
    19fe:	626814        	ae_sq32f.iu	aeq2, a8, 4
    1a01:	618144        	ae_lq56.i	aeq2, a1, 32
    1a04:	fc347a116f 	{ ae_sq56s.i	aeq1, a1, 48; ae_roundsq32asym	aeq0, aeq2 }
    1a09:	614174        	ae_lq56.i	aeq1, a1, 56
    1a0c:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1a11:	614e94        	ae_lq56.i	aeq1, a14, -56
    1a14:	61ce64        	ae_lq56.i	aeq3, a14, 48
    1a17:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1a1c:	d7e3fdce7f 	{ ae_lq56.i	aeq2, a14, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1a21:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1a26:	ff3c7d816f 	{ ae_lq56.i	aeq0, a1, 48; ae_roundsq32asym	aeq3, aeq3 }
    1a2b:	fc247da15f 	{ ae_lq56.i	aeq1, a1, 40; ae_roundsq32asym	aeq0, aeq0 }
    1a30:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1a35:	01d1b2        	addmi	a11, a1, 0x100
    1a38:	4661f2        	s32i	a15, a1, 0x118
    1a3b:	01d1f2        	addmi	a15, a1, 0x100
    1a3e:	fe3479f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq2, aeq2 }
    1a43:	f98f31        	l32r	a3, 80 (2a4 <fix_fft15_stage>)
    1a46:	fd2c430fae 	{ addi	a10, a15, 48; ae_roundsq32asym	aeq1, aeq1 }
    1a4b:	626814        	ae_sq32f.iu	aeq2, a8, 4
    1a4e:	34cbb2        	addi	a11, a11, 52
    1a51:	095d           	mov.n	a5, a9
    1a53:	625814        	ae_sq32f.iu	aeq1, a8, 4
    1a56:	4761a2        	s32i	a10, a1, 0x11c
    1a59:	0c4d           	mov.n	a4, a12
    1a5b:	0003e0        	callx8	a3
    1a5e:	302182        	l32i	a8, a1, 192
    1a61:	60c724        	ae_lq32f.i	aeq3, a7, 8
    1a64:	4121b2        	l32i	a11, a1, 0x104
    1a67:	608864        	ae_lq32f.i	aeq2, a8, 24
    1a6a:	632174        	ae_sq56s.i	aeq2, a1, 56
    1a6d:	608764        	ae_lq32f.i	aeq2, a7, 24
    1a70:	432172        	l32i	a7, a1, 0x10c
    1a73:	78c1e2        	addi	a14, a1, 120
    1a76:	604824        	ae_lq32f.i	aeq1, a8, 8
    1a79:	3f21c2        	l32i	a12, a1, 252
    1a7c:	4021d2        	l32i	a13, a1, 0x100
    1a7f:	039d           	mov.n	a9, a3
    1a81:	2e2132        	l32i	a3, a1, 184
    1a84:	631e94        	ae_sq56s.i	aeq1, a14, -56
    1a87:	633e34        	ae_sq56s.i	aeq3, a14, 24
    1a8a:	632e74        	ae_sq56s.i	aeq2, a14, 56
    1a8d:	60c624        	ae_lq32f.i	aeq3, a6, 8
    1a90:	604664        	ae_lq32f.i	aeq1, a6, 24
    1a93:	608224        	ae_lq32f.i	aeq2, a2, 8
    1a96:	633e14        	ae_sq56s.i	aeq3, a14, 8
    1a99:	631164        	ae_sq56s.i	aeq1, a1, 48
    1a9c:	6047a4        	ae_lq32f.i	aeq1, a7, -24
    1a9f:	632ef4        	ae_sq56s.i	aeq2, a14, -8
    1aa2:	608b24        	ae_lq32f.i	aeq2, a11, 8
    1aa5:	60c264        	ae_lq32f.i	aeq3, a2, 24
    1aa8:	492162        	l32i	a6, a1, 0x124
    1aab:	633e64        	ae_sq56s.i	aeq3, a14, 48
    1aae:	631144        	ae_sq56s.i	aeq1, a1, 32
    1ab1:	632154        	ae_sq56s.i	aeq2, a1, 40
    1ab4:	60cc64        	ae_lq32f.i	aeq3, a12, 24
    1ab7:	604c24        	ae_lq32f.i	aeq1, a12, 8
    1aba:	608d64        	ae_lq32f.i	aeq2, a13, 24
    1abd:	048d           	mov.n	a8, a4
    1abf:	04ad           	mov.n	a10, a4
    1ac1:	01d142        	addmi	a4, a1, 0x100
    1ac4:	482172        	l32i	a7, a1, 0x120
    1ac7:	633ed4        	ae_sq56s.i	aeq3, a14, -24
    1aca:	60cd24        	ae_lq32f.i	aeq3, a13, 8
    1acd:	631e54        	ae_sq56s.i	aeq1, a14, 40
    1ad0:	632ea4        	ae_sq56s.i	aeq2, a14, -48
    1ad3:	80c422        	addi	a2, a4, -128
    1ad6:	604324        	ae_lq32f.i	aeq1, a3, 8
    1ad9:	608524        	ae_lq32f.i	aeq2, a5, 8
    1adc:	4521b2        	l32i	a11, a1, 0x114
    1adf:	631274        	ae_sq56s.i	aeq1, a2, 56
    1ae2:	633e44        	ae_sq56s.i	aeq3, a14, 32
    1ae5:	632484        	ae_sq56s.i	aeq2, a4, -64
    1ae8:	60c634        	ae_lq32f.i	aeq3, a6, 12
    1aeb:	608674        	ae_lq32f.i	aeq2, a6, 28
    1aee:	600364        	ae_lq32f.i	aeq0, a3, 24
    1af1:	5404b4        	ae_lp24x2.i	aep0, a4, -40
    1af4:	d4e2b4212e 	{ l32i	a2, a1, 0x108; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1af9:	4621c2        	l32i	a12, a1, 0x118
    1afc:	fc247a3eef 	{ ae_sq56s.i	aeq3, a14, -16; ae_roundsq32asym	aeq0, aeq0 }
    1b01:	632e24        	ae_sq56s.i	aeq2, a14, 16
    1b04:	60c734        	ae_lq32f.i	aeq3, a7, 12
    1b07:	608774        	ae_lq32f.i	aeq2, a7, 28
    1b0a:	442162        	l32i	a6, a1, 0x110
    1b0d:	633114        	ae_sq56s.i	aeq3, a1, 8
    1b10:	632134        	ae_sq56s.i	aeq2, a1, 24
    1b13:	60cb24        	ae_lq32f.i	aeq3, a11, 8
    1b16:	608b64        	ae_lq32f.i	aeq2, a11, 24
    1b19:	6334a4        	ae_sq56s.i	aeq3, a4, -48
    1b1c:	632e04        	ae_sq56s.i	aeq2, a14, 0
    1b1f:	608c24        	ae_lq32f.i	aeq2, a12, 8
    1b22:	60c264        	ae_lq32f.i	aeq3, a2, 24
    1b25:	604564        	ae_lq32f.i	aeq1, a5, 24
    1b28:	d4e3f9c80f 	{ ae_sq32f.iu	aeq0, a8, 0; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1b2d:	d7e3ba249f 	{ ae_sq56s.i	aeq2, a4, -56; ae_mulfq32sp16u.l	aeq2, aeq3, aep0 }
    1b32:	fd2c7d622f 	{ ae_lq32f.i	aeq3, a2, 8; ae_roundsq32asym	aeq1, aeq1 }
    1b37:	600664        	ae_lq32f.i	aeq0, a6, 24
    1b3a:	d5e2fa3ebf 	{ ae_sq56s.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq3, aeq0, aep0 }
    1b3f:	600624        	ae_lq32f.i	aeq0, a6, 8
    1b42:	630ec4        	ae_sq56s.i	aeq0, a14, -32
    1b45:	600c64        	ae_lq32f.i	aeq0, a12, 24
    1b48:	630124        	ae_sq56s.i	aeq0, a1, 16
    1b4b:	610e94        	ae_lq56.i	aeq0, a14, -56
    1b4e:	d4e2b9d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_mulfq32sp16u.l	aeq0, aeq0, aep0 }
    1b53:	fd347dce3f 	{ ae_lq56.i	aeq2, a14, 24; ae_roundsq32asym	aeq1, aeq2 }
    1b58:	fd3c79d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq1, aeq3 }
    1b5d:	d7e2bdee1f 	{ ae_lq56.i	aeq3, a14, 8; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1b62:	fc2479d81f 	{ ae_sq32f.iu	aeq1, a8, 4; ae_roundsq32asym	aeq0, aeq0 }
    1b67:	d7e3fdaeff 	{ ae_lq56.i	aeq1, a14, -8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1b6c:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1b71:	d4e3fdcedf 	{ ae_lq56.i	aeq2, a14, -24; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1b76:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1b7b:	d7e2bdeeaf 	{ ae_lq56.i	aeq3, a14, -48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1b80:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1b85:	d7e3fda4af 	{ ae_lq56.i	aeq1, a4, -48; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1b8a:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1b8f:	d4e3fdc49f 	{ ae_lq56.i	aeq2, a4, -56; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1b94:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1b99:	d7e2bde17f 	{ ae_lq56.i	aeq3, a1, 56; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1b9e:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1ba3:	d7e3fdae7f 	{ ae_lq56.i	aeq1, a14, 56; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1ba8:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1bad:	d4e3fdc16f 	{ ae_lq56.i	aeq2, a1, 48; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1bb2:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1bb7:	d7e2bdee6f 	{ ae_lq56.i	aeq3, a14, 48; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1bbc:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1bc1:	d7e3fda14f 	{ ae_lq56.i	aeq1, a1, 32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1bc6:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1bcb:	d4e3fdc15f 	{ ae_lq56.i	aeq2, a1, 40; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1bd0:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1bd5:	d7e2bdeeef 	{ ae_lq56.i	aeq3, a14, -16; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1bda:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1bdf:	d7e3fda11f 	{ ae_lq56.i	aeq1, a1, 8; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1be4:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1be9:	d4e3fdce5f 	{ ae_lq56.i	aeq2, a14, 40; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1bee:	01d1d2        	addmi	a13, a1, 0x100
    1bf1:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1bf6:	d7e2bdee4f 	{ ae_lq56.i	aeq3, a14, 32; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1bfb:	d7e3c80d3e 	{ addi	a3, a13, -128; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1c00:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1c05:	614374        	ae_lq56.i	aeq1, a3, 56
    1c08:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1c0d:	d4e3fdc48f 	{ ae_lq56.i	aeq2, a4, -64; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1c12:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1c17:	d7e2bdeebf 	{ ae_lq56.i	aeq3, a14, -40; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1c1c:	fc2c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq1 }
    1c21:	d7e3fdaecf 	{ ae_lq56.i	aeq1, a14, -32; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1c26:	fc3479c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq2 }
    1c2b:	d4e3fdce2f 	{ ae_lq56.i	aeq2, a14, 16; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1c30:	fc3c79c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_roundsq32asym	aeq0, aeq3 }
    1c35:	d7e2bde13f 	{ ae_lq56.i	aeq3, a1, 24; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1c3a:	d7e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq3, aeq3, aep0 }
    1c3f:	fc2c7dae0f 	{ ae_lq56.i	aeq1, a14, 0; ae_roundsq32asym	aeq0, aeq1 }
    1c44:	d4e3f9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq1, aeq1, aep0 }
    1c49:	fc347dc12f 	{ ae_lq56.i	aeq2, a1, 16; ae_roundsq32asym	aeq0, aeq2 }
    1c4e:	d7e2b9c81f 	{ ae_sq32f.iu	aeq0, a8, 4; ae_mulfq32sp16u.l	aeq2, aeq2, aep0 }
    1c53:	ff3c73e1de 	{ l32i	a13, a1, 248; ae_roundsq32asym	aeq3, aeq3 }
    1c58:	02d1b2        	addmi	a11, a1, 0x200
    1c5b:	fd2c79f81f 	{ ae_sq32f.iu	aeq3, a8, 4; ae_roundsq32asym	aeq1, aeq1 }
    1c60:	ff344b4bbe 	{ addi	a11, a11, -76; ae_roundsq32asym	aeq3, aeq2 }
    1c65:	625814        	ae_sq32f.iu	aeq1, a8, 4
    1c68:	0acd           	mov.n	a12, a10
    1c6a:	627814        	ae_sq32f.iu	aeq3, a8, 4
    1c6d:	0a4d           	mov.n	a4, a10
    1c6f:	0009e0        	callx8	a9
    1c72:	4a2172        	l32i	a7, a1, 0x128
    1c75:	4b2182        	l32i	a8, a1, 0x12c
    1c78:	472152        	l32i	a5, a1, 0x11c
    1c7b:	3d6152        	s32i	a5, a1, 244
    1c7e:	f8c852        	addi	a5, a8, -8
    1c81:	3c6142        	s32i	a4, a1, 240
    1c84:	f8c742        	addi	a4, a7, -8
    1c87:	01d172        	addmi	a7, a1, 0x100
    1c8a:	f8c632        	addi	a3, a6, -8
    1c8d:	01d1f2        	addmi	a15, a1, 0x100
    1c90:	01d1c2        	addmi	a12, a1, 0x100
    1c93:	01d1d2        	addmi	a13, a1, 0x100
    1c96:	01d1e2        	addmi	a14, a1, 0x100
    1c99:	01d1a2        	addmi	a10, a1, 0x100
    1c9c:	3a6142        	s32i	a4, a1, 232
    1c9f:	396132        	s32i	a3, a1, 228
    1ca2:	386152        	s32i	a5, a1, 224
    1ca5:	f0cc32        	addi	a3, a12, -16
    1ca8:	eccd42        	addi	a4, a13, -20
    1cab:	e8ce52        	addi	a5, a14, -24
    1cae:	e4cf62        	addi	a6, a15, -28
    1cb1:	e0c772        	addi	a7, a7, -32
    1cb4:	f8f481        	l32r	a8, 84 (1d10 <fix_fft2_stage>)
    1cb7:	f8c222        	addi	a2, a2, -8
    1cba:	090c           	movi.n	a9, 0
    1cbc:	f4caa2        	addi	a10, a10, -12
    1cbf:	03bd           	mov.n	a11, a3
    1cc1:	04cd           	mov.n	a12, a4
    1cc3:	05dd           	mov.n	a13, a5
    1cc5:	06ed           	mov.n	a14, a6
    1cc7:	07fd           	mov.n	a15, a7
    1cc9:	3b6122        	s32i	a2, a1, 236
    1ccc:	3e61a2        	s32i	a10, a1, 248
    1ccf:	0199           	s32i.n	a9, a1, 0
    1cd1:	0008e0        	callx8	a8
    1cd4:	220c           	movi.n	a2, 2
    1cd6:	000706        	j	1cf6 <fix_fft30+0x52e>

00001cd9 <fix_fft30+0x511>:
    1cd9:	3e21a2        	l32i	a10, a1, 248
    1cdc:	03bd           	mov.n	a11, a3
    1cde:	04cd           	mov.n	a12, a4
    1ce0:	05dd           	mov.n	a13, a5
    1ce2:	06ed           	mov.n	a14, a6
    1ce4:	07fd           	mov.n	a15, a7
    1ce6:	c4af82        	movi	a8, -60
    1ce9:	0189           	s32i.n	a8, a1, 0
    1ceb:	f8e681        	l32r	a8, 84 (1d10 <fix_fft2_stage>)
    1cee:	0008e0        	callx8	a8
    1cf1:	221b           	addi.n	a2, a2, 1
    1cf3:	14b226        	beqi	a2, 16, 1d0b <fix_fft30+0x543>
    1cf6:	dfe207        	bbsi	a2, 0, 1cd9 <fix_fft30+0x511>
    1cf9:	3e21a2        	l32i	a10, a1, 248
    1cfc:	03bd           	mov.n	a11, a3
    1cfe:	05cd           	mov.n	a12, a5
    1d00:	04dd           	mov.n	a13, a4
    1d02:	07ed           	mov.n	a14, a7
    1d04:	06fd           	mov.n	a15, a6
    1d06:	c83c           	movi.n	a8, 60
    1d08:	fff746        	j	1ce9 <fix_fft30+0x521>

00001d0b <fix_fft30+0x543>:
    1d0b:	f01d           	retw.n

00001d0d <fix_fft30+0x545>:
    1d0d:	000000                                        ...

00001d10 <fix_fft2_stage>:
    1d10:	004136        	entry	a1, 32
    1d13:	8188           	l32i.n	a8, a1, 32
    1d15:	0298           	l32i.n	a9, a2, 0
    1d17:	603984        	ae_lq32f.xu	aeq0, a9, a8
    1d1a:	0299           	s32i.n	a9, a2, 0
    1d1c:	0398           	l32i.n	a9, a3, 0
    1d1e:	350074        	ae_sraiq56	aeq0, aeq0, 1
    1d21:	fc247c298f 	{ ae_lq32f.xu	aeq1, a9, a8; ae_roundsq32asym	aeq0, aeq0 }
    1d26:	0399           	s32i.n	a9, a3, 0
    1d28:	355074        	ae_sraiq56	aeq1, aeq1, 1
    1d2b:	fd2c7004fe 	{ l32i	a15, a4, 0; ae_roundsq32asym	aeq1, aeq1 }
    1d30:	0189c4        	ae_addq56	aeq2, aeq0, aeq1
    1d33:	f826f9ef2f 	{ ae_sq32f.iu	aeq2, a15, 8; ae_subq56	aeq0, aeq0, aeq1 }
    1d38:	04f9           	s32i.n	a15, a4, 0
    1d3a:	0548           	l32i.n	a4, a5, 0
    1d3c:	624424        	ae_sq32f.iu	aeq0, a4, 8
    1d3f:	0549           	s32i.n	a4, a5, 0
    1d41:	0248           	l32i.n	a4, a2, 0
    1d43:	601414        	ae_lq32f.iu	aeq0, a4, 4
    1d46:	0249           	s32i.n	a4, a2, 0
    1d48:	0328           	l32i.n	a2, a3, 0
    1d4a:	350074        	ae_sraiq56	aeq0, aeq0, 1
    1d4d:	fc247d521f 	{ ae_lq32f.iu	aeq2, a2, 4; ae_roundsq32asym	aeq0, aeq0 }
    1d52:	0329           	s32i.n	a2, a3, 0
    1d54:	356074        	ae_sraiq56	aeq1, aeq2, 1
    1d57:	fd2c70062e 	{ l32i	a2, a6, 0; ae_roundsq32asym	aeq1, aeq1 }
    1d5c:	01c9c4        	ae_addq56	aeq3, aeq0, aeq1
    1d5f:	f826f9f22f 	{ ae_sq32f.iu	aeq3, a2, 8; ae_subq56	aeq0, aeq0, aeq1 }
    1d64:	0629           	s32i.n	a2, a6, 0
    1d66:	0728           	l32i.n	a2, a7, 0
    1d68:	624224        	ae_sq32f.iu	aeq0, a2, 8
    1d6b:	0729           	s32i.n	a2, a7, 0
    1d6d:	f01d           	retw.n

00001d6f <fix_fft2_stage+0x5f>:
	...

00001d70 <__do_global_ctors_aux>:
    1d70:	004136        	entry	a1, 32
    1d73:	f8c531        	l32r	a3, 88 (2138 <__CTOR_END__>)
    1d76:	fcc322        	addi	a2, a3, -4
    1d79:	0228           	l32i.n	a2, a2, 0
    1d7b:	f8c332        	addi	a3, a3, -8
    1d7e:	0a0226        	beqi	a2, -1, 1d8c <__do_global_ctors_aux+0x1c>

00001d81 <__do_global_ctors_aux+0x11>:
    1d81:	0002e0        	callx8	a2
    1d84:	0328           	l32i.n	a2, a3, 0
    1d86:	fcc332        	addi	a3, a3, -4
    1d89:	f40266        	bnei	a2, -1, 1d81 <__do_global_ctors_aux+0x11>
    1d8c:	f01d           	retw.n

00001d8e <__do_global_ctors_aux+0x1e>:
	...

00001d90 <LC3Plus_lc3_scratch_init>:
    1d90:	004136        	entry	a1, 32
    1d93:	1f0c           	movi.n	a15, 1
    1d95:	401400        	ssl	a4
    1d98:	a14f00        	sll	a4, a15
    1d9b:	026d           	mov.n	a6, a2
    1d9d:	740b           	addi.n	a7, a4, -1
    1d9f:	0f0277        	bnone	a2, a7, 1db2 <LC3Plus_lc3_scratch_init+0x22>
    1da2:	102760        	and	a2, a7, a6
    1da5:	c08420        	sub	a8, a4, a2
    1da8:	020c           	movi.n	a2, 0
    1daa:	3a3387        	bltu	a3, a8, 1de8 <LC3Plus_lc3_scratch_init+0x58>
    1dad:	686a           	add.n	a6, a8, a6
    1daf:	c03380        	sub	a3, a3, a8

00001db2 <LC3Plus_lc3_scratch_init+0x22>:
    1db2:	c81c           	movi.n	a8, 28
    1db4:	109780        	and	a9, a7, a8
    1db7:	c07490        	sub	a7, a4, a9
    1dba:	1cc772        	addi	a7, a7, 28
    1dbd:	020c           	movi.n	a2, 0
    1dbf:	837890        	moveqz	a7, a8, a9
    1dc2:	6659           	s32i.n	a5, a6, 24
    1dc4:	5629           	s32i.n	a2, a6, 20
    1dc6:	4629           	s32i.n	a2, a6, 16
    1dc8:	1c3377        	bltu	a3, a7, 1de8 <LC3Plus_lc3_scratch_init+0x58>
    1dcb:	258c           	beqz.n	a5, 1dd1 <LC3Plus_lc3_scratch_init+0x41>
    1dcd:	5679           	s32i.n	a7, a6, 20
    1dcf:	4679           	s32i.n	a7, a6, 16
    1dd1:	f41b           	addi.n	a15, a4, 1
    1dd3:	603040        	neg	a3, a4
    1dd6:	267a           	add.n	a2, a6, a7
    1dd8:	0e0c           	movi.n	a14, 0
    1dda:	103f30        	and	a3, a15, a3
    1ddd:	0629           	s32i.n	a2, a6, 0
    1ddf:	062d           	mov.n	a2, a6
    1de1:	2649           	s32i.n	a4, a6, 8
    1de3:	0256e2        	s16i	a14, a6, 4
    1de6:	3639           	s32i.n	a3, a6, 12
    1de8:	f01d           	retw.n

00001dea <LC3Plus_lc3_scratch_init+0x5a>:
	...

00001dec <LC3Plus_lc3_scratch_push>:
    1dec:	004136        	entry	a1, 32
    1def:	024d           	mov.n	a4, a2
    1df1:	fe7c           	movi.n	a14, -1
    1df3:	f420e0        	extui	a2, a14, 0, 16
    1df6:	2458           	l32i.n	a5, a4, 8
    1df8:	0468           	l32i.n	a6, a4, 0
    1dfa:	021472        	l16ui	a7, a4, 4
    1dfd:	232a           	add.n	a2, a3, a2
    1dff:	3438           	l32i.n	a3, a4, 12
    1e01:	6488           	l32i.n	a8, a4, 24
    1e03:	252a           	add.n	a2, a5, a2
    1e05:	605050        	neg	a5, a5
    1e08:	f67a           	add.n	a15, a6, a7
    1e0a:	105250        	and	a5, a2, a5
    1e0d:	2f3a           	add.n	a2, a15, a3
    1e0f:	6f7d           	ae_s16i.n	a7, a15, 0
    1e11:	025452        	s16i	a5, a4, 4
    1e14:	0429           	s32i.n	a2, a4, 0
    1e16:	f88c           	beqz.n	a8, 1e29 <LC3Plus_lc3_scratch_push+0x3d>
    1e18:	5468           	l32i.n	a6, a4, 20
    1e1a:	955d           	ae_zext16	a5, a5
    1e1c:	44f8           	l32i.n	a15, a4, 16
    1e1e:	335a           	add.n	a3, a3, a5
    1e20:	336a           	add.n	a3, a3, a6
    1e22:	5439           	s32i.n	a3, a4, 20
    1e24:	7333f0        	maxu	a3, a3, a15
    1e27:	4439           	s32i.n	a3, a4, 16

00001e29 <LC3Plus_lc3_scratch_push+0x3d>:
    1e29:	f01d           	retw.n

00001e2b <LC3Plus_lc3_scratch_push+0x3f>:
	...

00001e2c <LC3Plus_lc3_scratch_pop>:
    1e2c:	004136        	entry	a1, 32
    1e2f:	023d           	mov.n	a3, a2
    1e31:	02f8           	l32i.n	a15, a2, 0
    1e33:	3248           	l32i.n	a4, a2, 12
    1e35:	6258           	l32i.n	a5, a2, 24
    1e37:	c02f40        	sub	a2, a15, a4
    1e3a:	a58c           	beqz.n	a5, 1e48 <LC3Plus_lc3_scratch_pop+0x1c>
    1e3c:	021352        	l16ui	a5, a3, 4
    1e3f:	5368           	l32i.n	a6, a3, 20
    1e41:	445a           	add.n	a4, a4, a5
    1e43:	c04640        	sub	a4, a6, a4
    1e46:	5349           	s32i.n	a4, a3, 20

00001e48 <LC3Plus_lc3_scratch_pop+0x1c>:
    1e48:	424d           	ae_l16ui.n	a4, a2, 0
    1e4a:	025342        	s16i	a4, a3, 4
    1e4d:	c04240        	sub	a4, a2, a4
    1e50:	020c           	movi.n	a2, 0
    1e52:	0349           	s32i.n	a4, a3, 0
    1e54:	f01d           	retw.n

00001e56 <LC3Plus_lc3_scratch_pop+0x2a>:
	...

00001e58 <_fini>:
    1e58:	008136        	entry	a1, 64
    1e5b:	f88c81        	l32r	a8, 8c (a8 <__do_global_dtors_aux>)
    1e5e:	f03d           	nop.n
    1e60:	0008e0        	callx8	a8

00001e63 <_fini+0xb>:
    1e63:	f01d           	retw.n
