
#define omp_arg128(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, _128, ...) _128

#define omp_narg(...) omp_narg_ (0, ##__VA_ARGS__)
#define omp_narg_(...) omp_arg128 (__VA_ARGS__, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, )

#define omp_peek_(_0, ...) _0
#define omp_peek(...) omp_peek_(__VA_ARGS__)
#define omp_pop_(_0, ...) __VA_ARGS__
#define omp_pop(...) omp_pop_(__VA_ARGS__)

#define omp_comma(...) ,
#define omp_empty(...)
#define omp_zero(...) 0



#define omp_sizeof(v) sizeof(v)

#define omp_remove_first(_1,...) __VA_ARGS__
#define omp_1st(_1, ...) _1
#define omp_2nd(_1, _2, ...) _2
#define omp_3rd(_1, _2, _3, ...) _3
#define omp_4th(_1, _2, _3, _4, ...) _4

#define omp_glue2_(a,b) a ## b
#define omp_glue2(a,b) omp_glue2_(a,b)

#define omp_string(a) #a

#define omp_for(macro,opt,...) omp_glue2(omp_for_, omp_narg(__VA_ARGS__))(macro, opt, __VA_ARGS__)
#define omp_for_2nd(macro,opt,...) omp_glue2(omp_for_2nd_, omp_narg(__VA_ARGS__))(macro, opt, __VA_ARGS__)
#define omp_for_3rd(macro,opt,...) omp_glue2(omp_for_3rd_, omp_narg(__VA_ARGS__))(macro, opt, __VA_ARGS__)


#define omp_apply(mc,...) mc(__VA_ARGS__)
#define omp_fold_(f) f

#define omp_reverse_0(...)
#define omp_reverse_1(a) a
#define omp_reverse_2(a,b) b,a
#define omp_reverse_3(a,...) omp_fold_(omp_reverse_2(__VA_ARGS__)),a
#define omp_reverse_4(a,...) omp_fold_(omp_reverse_3(__VA_ARGS__)),a
#define omp_reverse_5(a,...) omp_fold_(omp_reverse_4(__VA_ARGS__)),a
#define omp_reverse_6(a,...) omp_fold_(omp_reverse_5(__VA_ARGS__)),a
#define omp_reverse_7(a,...) omp_fold_(omp_reverse_6(__VA_ARGS__)),a
#define omp_reverse_8(a,...) omp_fold_(omp_reverse_7(__VA_ARGS__)),a
#define omp_reverse_9(a,...) omp_fold_(omp_reverse_8(__VA_ARGS__)),a
#define omp_reverse_10(a,...) omp_fold_(omp_reverse_9(__VA_ARGS__)),a
#define omp_reverse_11(a,...) omp_fold_(omp_reverse_10(__VA_ARGS__)),a
#define omp_reverse_12(a,...) omp_fold_(omp_reverse_11(__VA_ARGS__)),a
#define omp_reverse_13(a,...) omp_fold_(omp_reverse_12(__VA_ARGS__)),a
#define omp_reverse_14(a,...) omp_fold_(omp_reverse_13(__VA_ARGS__)),a
#define omp_reverse_15(a,...) omp_fold_(omp_reverse_14(__VA_ARGS__)),a
#define omp_reverse_16(a,...) omp_fold_(omp_reverse_15(__VA_ARGS__)),a
#define omp_reverse_17(a,...) omp_fold_(omp_reverse_16(__VA_ARGS__)),a
#define omp_reverse_18(a,...) omp_fold_(omp_reverse_17(__VA_ARGS__)),a
#define omp_reverse_19(a,...) omp_fold_(omp_reverse_18(__VA_ARGS__)),a
#define omp_reverse_20(a,...) omp_fold_(omp_reverse_19(__VA_ARGS__)),a
#define omp_reverse_21(a,...) omp_fold_(omp_reverse_20(__VA_ARGS__)),a
#define omp_reverse_22(a,...) omp_fold_(omp_reverse_21(__VA_ARGS__)),a
#define omp_reverse_23(a,...) omp_fold_(omp_reverse_22(__VA_ARGS__)),a
#define omp_reverse_24(a,...) omp_fold_(omp_reverse_23(__VA_ARGS__)),a
#define omp_reverse_25(a,...) omp_fold_(omp_reverse_24(__VA_ARGS__)),a
#define omp_reverse_26(a,...) omp_fold_(omp_reverse_25(__VA_ARGS__)),a
#define omp_reverse_27(a,...) omp_fold_(omp_reverse_26(__VA_ARGS__)),a
#define omp_reverse_28(a,...) omp_fold_(omp_reverse_27(__VA_ARGS__)),a
#define omp_reverse_29(a,...) omp_fold_(omp_reverse_28(__VA_ARGS__)),a
#define omp_reverse_30(a,...) omp_fold_(omp_reverse_29(__VA_ARGS__)),a
#define omp_reverse_31(a,...) omp_fold_(omp_reverse_30(__VA_ARGS__)),a
#define omp_reverse_32(a,...) omp_fold_(omp_reverse_31(__VA_ARGS__)),a
#define omp_reverse_33(a,...) omp_fold_(omp_reverse_32(__VA_ARGS__)),a
#define omp_reverse_34(a,...) omp_fold_(omp_reverse_33(__VA_ARGS__)),a
#define omp_reverse_35(a,...) omp_fold_(omp_reverse_34(__VA_ARGS__)),a
#define omp_reverse_36(a,...) omp_fold_(omp_reverse_35(__VA_ARGS__)),a
#define omp_reverse_37(a,...) omp_fold_(omp_reverse_36(__VA_ARGS__)),a
#define omp_reverse_38(a,...) omp_fold_(omp_reverse_37(__VA_ARGS__)),a
#define omp_reverse_39(a,...) omp_fold_(omp_reverse_38(__VA_ARGS__)),a
#define omp_reverse_40(a,...) omp_fold_(omp_reverse_39(__VA_ARGS__)),a
#define omp_reverse_41(a,...) omp_fold_(omp_reverse_40(__VA_ARGS__)),a
#define omp_reverse_42(a,...) omp_fold_(omp_reverse_41(__VA_ARGS__)),a
#define omp_reverse_43(a,...) omp_fold_(omp_reverse_42(__VA_ARGS__)),a
#define omp_reverse_44(a,...) omp_fold_(omp_reverse_43(__VA_ARGS__)),a
#define omp_reverse_45(a,...) omp_fold_(omp_reverse_44(__VA_ARGS__)),a
#define omp_reverse_46(a,...) omp_fold_(omp_reverse_45(__VA_ARGS__)),a
#define omp_reverse_47(a,...) omp_fold_(omp_reverse_46(__VA_ARGS__)),a
#define omp_reverse_48(a,...) omp_fold_(omp_reverse_47(__VA_ARGS__)),a
#define omp_reverse_49(a,...) omp_fold_(omp_reverse_48(__VA_ARGS__)),a
#define omp_reverse_50(a,...) omp_fold_(omp_reverse_49(__VA_ARGS__)),a
#define omp_reverse_51(a,...) omp_fold_(omp_reverse_50(__VA_ARGS__)),a
#define omp_reverse_52(a,...) omp_fold_(omp_reverse_51(__VA_ARGS__)),a
#define omp_reverse_53(a,...) omp_fold_(omp_reverse_52(__VA_ARGS__)),a
#define omp_reverse_54(a,...) omp_fold_(omp_reverse_53(__VA_ARGS__)),a
#define omp_reverse_55(a,...) omp_fold_(omp_reverse_54(__VA_ARGS__)),a
#define omp_reverse_56(a,...) omp_fold_(omp_reverse_55(__VA_ARGS__)),a
#define omp_reverse_57(a,...) omp_fold_(omp_reverse_56(__VA_ARGS__)),a
#define omp_reverse_58(a,...) omp_fold_(omp_reverse_57(__VA_ARGS__)),a
#define omp_reverse_59(a,...) omp_fold_(omp_reverse_58(__VA_ARGS__)),a
#define omp_reverse_60(a,...) omp_fold_(omp_reverse_59(__VA_ARGS__)),a
#define omp_reverse_61(a,...) omp_fold_(omp_reverse_60(__VA_ARGS__)),a
#define omp_reverse_62(a,...) omp_fold_(omp_reverse_61(__VA_ARGS__)),a
#define omp_reverse_63(a,...) omp_fold_(omp_reverse_62(__VA_ARGS__)),a
#define omp_reverse_64(a,...) omp_fold_(omp_reverse_63(__VA_ARGS__)),a
#define omp_reverse_65(a,...) omp_fold_(omp_reverse_64(__VA_ARGS__)),a
#define omp_reverse_66(a,...) omp_fold_(omp_reverse_65(__VA_ARGS__)),a
#define omp_reverse_67(a,...) omp_fold_(omp_reverse_66(__VA_ARGS__)),a
#define omp_reverse_68(a,...) omp_fold_(omp_reverse_67(__VA_ARGS__)),a
#define omp_reverse_69(a,...) omp_fold_(omp_reverse_68(__VA_ARGS__)),a
#define omp_reverse_70(a,...) omp_fold_(omp_reverse_69(__VA_ARGS__)),a
#define omp_reverse_71(a,...) omp_fold_(omp_reverse_70(__VA_ARGS__)),a
#define omp_reverse_72(a,...) omp_fold_(omp_reverse_71(__VA_ARGS__)),a
#define omp_reverse_73(a,...) omp_fold_(omp_reverse_72(__VA_ARGS__)),a
#define omp_reverse_74(a,...) omp_fold_(omp_reverse_73(__VA_ARGS__)),a
#define omp_reverse_75(a,...) omp_fold_(omp_reverse_74(__VA_ARGS__)),a
#define omp_reverse_76(a,...) omp_fold_(omp_reverse_75(__VA_ARGS__)),a
#define omp_reverse_77(a,...) omp_fold_(omp_reverse_76(__VA_ARGS__)),a
#define omp_reverse_78(a,...) omp_fold_(omp_reverse_77(__VA_ARGS__)),a
#define omp_reverse_79(a,...) omp_fold_(omp_reverse_78(__VA_ARGS__)),a
#define omp_reverse_80(a,...) omp_fold_(omp_reverse_79(__VA_ARGS__)),a
#define omp_reverse_81(a,...) omp_fold_(omp_reverse_80(__VA_ARGS__)),a
#define omp_reverse_82(a,...) omp_fold_(omp_reverse_81(__VA_ARGS__)),a
#define omp_reverse_83(a,...) omp_fold_(omp_reverse_82(__VA_ARGS__)),a
#define omp_reverse_84(a,...) omp_fold_(omp_reverse_83(__VA_ARGS__)),a
#define omp_reverse_85(a,...) omp_fold_(omp_reverse_84(__VA_ARGS__)),a
#define omp_reverse_86(a,...) omp_fold_(omp_reverse_85(__VA_ARGS__)),a
#define omp_reverse_87(a,...) omp_fold_(omp_reverse_86(__VA_ARGS__)),a
#define omp_reverse_88(a,...) omp_fold_(omp_reverse_87(__VA_ARGS__)),a
#define omp_reverse_89(a,...) omp_fold_(omp_reverse_88(__VA_ARGS__)),a
#define omp_reverse_90(a,...) omp_fold_(omp_reverse_89(__VA_ARGS__)),a
#define omp_reverse_91(a,...) omp_fold_(omp_reverse_90(__VA_ARGS__)),a
#define omp_reverse_92(a,...) omp_fold_(omp_reverse_91(__VA_ARGS__)),a
#define omp_reverse_93(a,...) omp_fold_(omp_reverse_92(__VA_ARGS__)),a
#define omp_reverse_94(a,...) omp_fold_(omp_reverse_93(__VA_ARGS__)),a
#define omp_reverse_95(a,...) omp_fold_(omp_reverse_94(__VA_ARGS__)),a
#define omp_reverse_96(a,...) omp_fold_(omp_reverse_95(__VA_ARGS__)),a
#define omp_reverse(...) omp_glue2(omp_reverse_, omp_narg(__VA_ARGS__))(__VA_ARGS__)

#define omp_for_0(m,opt,V,...) 
#define omp_for_1(m,opt,V,...) m(1, V, opt, __VA_ARGS__)
#define omp_for_2(m,opt,V,...) m(2, V, opt, __VA_ARGS__) omp_for_1(m, opt, __VA_ARGS__)
#define omp_for_3(m,opt,V,...) m(3, V, opt, __VA_ARGS__) omp_for_2(m, opt, __VA_ARGS__)
#define omp_for_4(m,opt,V,...) m(4, V, opt, __VA_ARGS__) omp_for_3(m, opt, __VA_ARGS__)
#define omp_for_5(m,opt,V,...) m(5, V, opt, __VA_ARGS__) omp_for_4(m, opt, __VA_ARGS__)
#define omp_for_6(m,opt,V,...) m(6, V, opt, __VA_ARGS__) omp_for_5(m, opt, __VA_ARGS__)
#define omp_for_7(m,opt,V,...) m(7, V, opt, __VA_ARGS__) omp_for_6(m, opt, __VA_ARGS__)
#define omp_for_8(m,opt,V,...) m(8, V, opt, __VA_ARGS__) omp_for_7(m, opt, __VA_ARGS__)
#define omp_for_9(m,opt,V,...) m(9, V, opt, __VA_ARGS__) omp_for_8(m, opt, __VA_ARGS__)
#define omp_for_10(m,opt,V,...) m(10, V, opt, __VA_ARGS__) omp_for_9(m, opt, __VA_ARGS__)
#define omp_for_11(m,opt,V,...) m(11, V, opt, __VA_ARGS__) omp_for_10(m, opt, __VA_ARGS__)
#define omp_for_12(m,opt,V,...) m(12, V, opt, __VA_ARGS__) omp_for_11(m, opt, __VA_ARGS__)
#define omp_for_13(m,opt,V,...) m(13, V, opt, __VA_ARGS__) omp_for_12(m, opt, __VA_ARGS__)
#define omp_for_14(m,opt,V,...) m(14, V, opt, __VA_ARGS__) omp_for_13(m, opt, __VA_ARGS__)
#define omp_for_15(m,opt,V,...) m(15, V, opt, __VA_ARGS__) omp_for_14(m, opt, __VA_ARGS__)
#define omp_for_16(m,opt,V,...) m(16, V, opt, __VA_ARGS__) omp_for_15(m, opt, __VA_ARGS__)
#define omp_for_17(m,opt,V,...) m(17, V, opt, __VA_ARGS__) omp_for_16(m, opt, __VA_ARGS__)
#define omp_for_18(m,opt,V,...) m(18, V, opt, __VA_ARGS__) omp_for_17(m, opt, __VA_ARGS__)
#define omp_for_19(m,opt,V,...) m(19, V, opt, __VA_ARGS__) omp_for_18(m, opt, __VA_ARGS__)
#define omp_for_20(m,opt,V,...) m(20, V, opt, __VA_ARGS__) omp_for_19(m, opt, __VA_ARGS__)
#define omp_for_21(m,opt,V,...) m(21, V, opt, __VA_ARGS__) omp_for_20(m, opt, __VA_ARGS__)
#define omp_for_22(m,opt,V,...) m(22, V, opt, __VA_ARGS__) omp_for_21(m, opt, __VA_ARGS__)
#define omp_for_23(m,opt,V,...) m(23, V, opt, __VA_ARGS__) omp_for_22(m, opt, __VA_ARGS__)
#define omp_for_24(m,opt,V,...) m(24, V, opt, __VA_ARGS__) omp_for_23(m, opt, __VA_ARGS__)
#define omp_for_25(m,opt,V,...) m(25, V, opt, __VA_ARGS__) omp_for_24(m, opt, __VA_ARGS__)
#define omp_for_26(m,opt,V,...) m(26, V, opt, __VA_ARGS__) omp_for_25(m, opt, __VA_ARGS__)
#define omp_for_27(m,opt,V,...) m(27, V, opt, __VA_ARGS__) omp_for_26(m, opt, __VA_ARGS__)
#define omp_for_28(m,opt,V,...) m(28, V, opt, __VA_ARGS__) omp_for_27(m, opt, __VA_ARGS__)
#define omp_for_29(m,opt,V,...) m(29, V, opt, __VA_ARGS__) omp_for_28(m, opt, __VA_ARGS__)
#define omp_for_30(m,opt,V,...) m(30, V, opt, __VA_ARGS__) omp_for_29(m, opt, __VA_ARGS__)
#define omp_for_31(m,opt,V,...) m(31, V, opt, __VA_ARGS__) omp_for_30(m, opt, __VA_ARGS__)
#define omp_for_32(m,opt,V,...) m(32, V, opt, __VA_ARGS__) omp_for_31(m, opt, __VA_ARGS__)
#define omp_for_33(m,opt,V,...) m(33, V, opt, __VA_ARGS__) omp_for_32(m, opt, __VA_ARGS__)
#define omp_for_34(m,opt,V,...) m(34, V, opt, __VA_ARGS__) omp_for_33(m, opt, __VA_ARGS__)
#define omp_for_35(m,opt,V,...) m(35, V, opt, __VA_ARGS__) omp_for_34(m, opt, __VA_ARGS__)
#define omp_for_36(m,opt,V,...) m(36, V, opt, __VA_ARGS__) omp_for_35(m, opt, __VA_ARGS__)
#define omp_for_37(m,opt,V,...) m(37, V, opt, __VA_ARGS__) omp_for_36(m, opt, __VA_ARGS__)
#define omp_for_38(m,opt,V,...) m(38, V, opt, __VA_ARGS__) omp_for_37(m, opt, __VA_ARGS__)
#define omp_for_39(m,opt,V,...) m(39, V, opt, __VA_ARGS__) omp_for_38(m, opt, __VA_ARGS__)
#define omp_for_40(m,opt,V,...) m(40, V, opt, __VA_ARGS__) omp_for_39(m, opt, __VA_ARGS__)
#define omp_for_41(m,opt,V,...) m(41, V, opt, __VA_ARGS__) omp_for_40(m, opt, __VA_ARGS__)
#define omp_for_42(m,opt,V,...) m(42, V, opt, __VA_ARGS__) omp_for_41(m, opt, __VA_ARGS__)
#define omp_for_43(m,opt,V,...) m(43, V, opt, __VA_ARGS__) omp_for_42(m, opt, __VA_ARGS__)
#define omp_for_44(m,opt,V,...) m(44, V, opt, __VA_ARGS__) omp_for_43(m, opt, __VA_ARGS__)
#define omp_for_45(m,opt,V,...) m(45, V, opt, __VA_ARGS__) omp_for_44(m, opt, __VA_ARGS__)
#define omp_for_46(m,opt,V,...) m(46, V, opt, __VA_ARGS__) omp_for_45(m, opt, __VA_ARGS__)
#define omp_for_47(m,opt,V,...) m(47, V, opt, __VA_ARGS__) omp_for_46(m, opt, __VA_ARGS__)
#define omp_for_48(m,opt,V,...) m(48, V, opt, __VA_ARGS__) omp_for_47(m, opt, __VA_ARGS__)
#define omp_for_49(m,opt,V,...) m(49, V, opt, __VA_ARGS__) omp_for_48(m, opt, __VA_ARGS__)
#define omp_for_50(m,opt,V,...) m(50, V, opt, __VA_ARGS__) omp_for_49(m, opt, __VA_ARGS__)
#define omp_for_51(m,opt,V,...) m(51, V, opt, __VA_ARGS__) omp_for_50(m, opt, __VA_ARGS__)
#define omp_for_52(m,opt,V,...) m(52, V, opt, __VA_ARGS__) omp_for_51(m, opt, __VA_ARGS__)
#define omp_for_53(m,opt,V,...) m(53, V, opt, __VA_ARGS__) omp_for_52(m, opt, __VA_ARGS__)
#define omp_for_54(m,opt,V,...) m(54, V, opt, __VA_ARGS__) omp_for_53(m, opt, __VA_ARGS__)
#define omp_for_55(m,opt,V,...) m(55, V, opt, __VA_ARGS__) omp_for_54(m, opt, __VA_ARGS__)
#define omp_for_56(m,opt,V,...) m(56, V, opt, __VA_ARGS__) omp_for_55(m, opt, __VA_ARGS__)
#define omp_for_57(m,opt,V,...) m(57, V, opt, __VA_ARGS__) omp_for_56(m, opt, __VA_ARGS__)
#define omp_for_58(m,opt,V,...) m(58, V, opt, __VA_ARGS__) omp_for_57(m, opt, __VA_ARGS__)
#define omp_for_59(m,opt,V,...) m(59, V, opt, __VA_ARGS__) omp_for_58(m, opt, __VA_ARGS__)
#define omp_for_60(m,opt,V,...) m(60, V, opt, __VA_ARGS__) omp_for_59(m, opt, __VA_ARGS__)
#define omp_for_61(m,opt,V,...) m(61, V, opt, __VA_ARGS__) omp_for_60(m, opt, __VA_ARGS__)
#define omp_for_62(m,opt,V,...) m(62, V, opt, __VA_ARGS__) omp_for_61(m, opt, __VA_ARGS__)
#define omp_for_63(m,opt,V,...) m(63, V, opt, __VA_ARGS__) omp_for_62(m, opt, __VA_ARGS__)
#define omp_for_64(m,opt,V,...) m(64, V, opt, __VA_ARGS__) omp_for_63(m, opt, __VA_ARGS__)
#define omp_for_65(m,opt,V,...) m(65, V, opt, __VA_ARGS__) omp_for_64(m, opt, __VA_ARGS__)
#define omp_for_66(m,opt,V,...) m(66, V, opt, __VA_ARGS__) omp_for_65(m, opt, __VA_ARGS__)
#define omp_for_67(m,opt,V,...) m(67, V, opt, __VA_ARGS__) omp_for_66(m, opt, __VA_ARGS__)
#define omp_for_68(m,opt,V,...) m(68, V, opt, __VA_ARGS__) omp_for_67(m, opt, __VA_ARGS__)
#define omp_for_69(m,opt,V,...) m(69, V, opt, __VA_ARGS__) omp_for_68(m, opt, __VA_ARGS__)
#define omp_for_70(m,opt,V,...) m(70, V, opt, __VA_ARGS__) omp_for_69(m, opt, __VA_ARGS__)
#define omp_for_71(m,opt,V,...) m(71, V, opt, __VA_ARGS__) omp_for_70(m, opt, __VA_ARGS__)
#define omp_for_72(m,opt,V,...) m(72, V, opt, __VA_ARGS__) omp_for_71(m, opt, __VA_ARGS__)
#define omp_for_73(m,opt,V,...) m(73, V, opt, __VA_ARGS__) omp_for_72(m, opt, __VA_ARGS__)
#define omp_for_74(m,opt,V,...) m(74, V, opt, __VA_ARGS__) omp_for_73(m, opt, __VA_ARGS__)
#define omp_for_75(m,opt,V,...) m(75, V, opt, __VA_ARGS__) omp_for_74(m, opt, __VA_ARGS__)
#define omp_for_76(m,opt,V,...) m(76, V, opt, __VA_ARGS__) omp_for_75(m, opt, __VA_ARGS__)
#define omp_for_77(m,opt,V,...) m(77, V, opt, __VA_ARGS__) omp_for_76(m, opt, __VA_ARGS__)
#define omp_for_78(m,opt,V,...) m(78, V, opt, __VA_ARGS__) omp_for_77(m, opt, __VA_ARGS__)
#define omp_for_79(m,opt,V,...) m(79, V, opt, __VA_ARGS__) omp_for_78(m, opt, __VA_ARGS__)
#define omp_for_80(m,opt,V,...) m(80, V, opt, __VA_ARGS__) omp_for_79(m, opt, __VA_ARGS__)
#define omp_for_81(m,opt,V,...) m(81, V, opt, __VA_ARGS__) omp_for_80(m, opt, __VA_ARGS__)
#define omp_for_82(m,opt,V,...) m(82, V, opt, __VA_ARGS__) omp_for_81(m, opt, __VA_ARGS__)
#define omp_for_83(m,opt,V,...) m(83, V, opt, __VA_ARGS__) omp_for_82(m, opt, __VA_ARGS__)
#define omp_for_84(m,opt,V,...) m(84, V, opt, __VA_ARGS__) omp_for_83(m, opt, __VA_ARGS__)
#define omp_for_85(m,opt,V,...) m(85, V, opt, __VA_ARGS__) omp_for_84(m, opt, __VA_ARGS__)
#define omp_for_86(m,opt,V,...) m(86, V, opt, __VA_ARGS__) omp_for_85(m, opt, __VA_ARGS__)
#define omp_for_87(m,opt,V,...) m(87, V, opt, __VA_ARGS__) omp_for_86(m, opt, __VA_ARGS__)
#define omp_for_88(m,opt,V,...) m(88, V, opt, __VA_ARGS__) omp_for_87(m, opt, __VA_ARGS__)
#define omp_for_89(m,opt,V,...) m(89, V, opt, __VA_ARGS__) omp_for_88(m, opt, __VA_ARGS__)
#define omp_for_90(m,opt,V,...) m(90, V, opt, __VA_ARGS__) omp_for_89(m, opt, __VA_ARGS__)
#define omp_for_91(m,opt,V,...) m(91, V, opt, __VA_ARGS__) omp_for_90(m, opt, __VA_ARGS__)
#define omp_for_92(m,opt,V,...) m(92, V, opt, __VA_ARGS__) omp_for_91(m, opt, __VA_ARGS__)
#define omp_for_93(m,opt,V,...) m(93, V, opt, __VA_ARGS__) omp_for_92(m, opt, __VA_ARGS__)
#define omp_for_94(m,opt,V,...) m(94, V, opt, __VA_ARGS__) omp_for_93(m, opt, __VA_ARGS__)
#define omp_for_95(m,opt,V,...) m(95, V, opt, __VA_ARGS__) omp_for_94(m, opt, __VA_ARGS__)
#define omp_for_96(m,opt,V,...) m(96, V, opt, __VA_ARGS__) omp_for_95(m, opt, __VA_ARGS__)

//


// macro love is bittersweet
#define omp_for_2nd_0(m,opt,V,...) 
#define omp_for_2nd_1(m,opt,V,...) m(1, V, opt, __VA_ARGS__)
#define omp_for_2nd_2(m,opt,V,...) m(2, V, opt, __VA_ARGS__) omp_for_2nd_1(m, opt, __VA_ARGS__)
#define omp_for_2nd_3(m,opt,V,...) m(3, V, opt, __VA_ARGS__) omp_for_2nd_2(m, opt, __VA_ARGS__)
#define omp_for_2nd_4(m,opt,V,...) m(4, V, opt, __VA_ARGS__) omp_for_2nd_3(m, opt, __VA_ARGS__)
#define omp_for_2nd_5(m,opt,V,...) m(5, V, opt, __VA_ARGS__) omp_for_2nd_4(m, opt, __VA_ARGS__)
#define omp_for_2nd_6(m,opt,V,...) m(6, V, opt, __VA_ARGS__) omp_for_2nd_5(m, opt, __VA_ARGS__)
#define omp_for_2nd_7(m,opt,V,...) m(7, V, opt, __VA_ARGS__) omp_for_2nd_6(m, opt, __VA_ARGS__)
#define omp_for_2nd_8(m,opt,V,...) m(8, V, opt, __VA_ARGS__) omp_for_2nd_7(m, opt, __VA_ARGS__)
#define omp_for_2nd_9(m,opt,V,...) m(9, V, opt, __VA_ARGS__) omp_for_2nd_8(m, opt, __VA_ARGS__)
#define omp_for_2nd_10(m,opt,V,...) m(10, V, opt, __VA_ARGS__) omp_for_2nd_9(m, opt, __VA_ARGS__)
#define omp_for_2nd_11(m,opt,V,...) m(11, V, opt, __VA_ARGS__) omp_for_2nd_10(m, opt, __VA_ARGS__)
#define omp_for_2nd_12(m,opt,V,...) m(12, V, opt, __VA_ARGS__) omp_for_2nd_11(m, opt, __VA_ARGS__)
#define omp_for_2nd_13(m,opt,V,...) m(13, V, opt, __VA_ARGS__) omp_for_2nd_12(m, opt, __VA_ARGS__)
#define omp_for_2nd_14(m,opt,V,...) m(14, V, opt, __VA_ARGS__) omp_for_2nd_13(m, opt, __VA_ARGS__)
#define omp_for_2nd_15(m,opt,V,...) m(15, V, opt, __VA_ARGS__) omp_for_2nd_14(m, opt, __VA_ARGS__)
#define omp_for_2nd_16(m,opt,V,...) m(16, V, opt, __VA_ARGS__) omp_for_2nd_15(m, opt, __VA_ARGS__)
#define omp_for_2nd_17(m,opt,V,...) m(17, V, opt, __VA_ARGS__) omp_for_2nd_16(m, opt, __VA_ARGS__)
#define omp_for_2nd_18(m,opt,V,...) m(18, V, opt, __VA_ARGS__) omp_for_2nd_17(m, opt, __VA_ARGS__)
#define omp_for_2nd_19(m,opt,V,...) m(19, V, opt, __VA_ARGS__) omp_for_2nd_18(m, opt, __VA_ARGS__)
#define omp_for_2nd_20(m,opt,V,...) m(20, V, opt, __VA_ARGS__) omp_for_2nd_19(m, opt, __VA_ARGS__)
#define omp_for_2nd_21(m,opt,V,...) m(21, V, opt, __VA_ARGS__) omp_for_2nd_20(m, opt, __VA_ARGS__)
#define omp_for_2nd_22(m,opt,V,...) m(22, V, opt, __VA_ARGS__) omp_for_2nd_21(m, opt, __VA_ARGS__)
#define omp_for_2nd_23(m,opt,V,...) m(23, V, opt, __VA_ARGS__) omp_for_2nd_22(m, opt, __VA_ARGS__)
#define omp_for_2nd_24(m,opt,V,...) m(24, V, opt, __VA_ARGS__) omp_for_2nd_23(m, opt, __VA_ARGS__)
#define omp_for_2nd_25(m,opt,V,...) m(25, V, opt, __VA_ARGS__) omp_for_2nd_24(m, opt, __VA_ARGS__)
#define omp_for_2nd_26(m,opt,V,...) m(26, V, opt, __VA_ARGS__) omp_for_2nd_25(m, opt, __VA_ARGS__)
#define omp_for_2nd_27(m,opt,V,...) m(27, V, opt, __VA_ARGS__) omp_for_2nd_26(m, opt, __VA_ARGS__)
#define omp_for_2nd_28(m,opt,V,...) m(28, V, opt, __VA_ARGS__) omp_for_2nd_27(m, opt, __VA_ARGS__)
#define omp_for_2nd_29(m,opt,V,...) m(29, V, opt, __VA_ARGS__) omp_for_2nd_28(m, opt, __VA_ARGS__)
#define omp_for_2nd_30(m,opt,V,...) m(30, V, opt, __VA_ARGS__) omp_for_2nd_29(m, opt, __VA_ARGS__)
#define omp_for_2nd_31(m,opt,V,...) m(31, V, opt, __VA_ARGS__) omp_for_2nd_30(m, opt, __VA_ARGS__)
#define omp_for_2nd_32(m,opt,V,...) m(32, V, opt, __VA_ARGS__) omp_for_2nd_31(m, opt, __VA_ARGS__)
#define omp_for_2nd_33(m,opt,V,...) m(33, V, opt, __VA_ARGS__) omp_for_2nd_32(m, opt, __VA_ARGS__)
#define omp_for_2nd_34(m,opt,V,...) m(34, V, opt, __VA_ARGS__) omp_for_2nd_33(m, opt, __VA_ARGS__)
#define omp_for_2nd_35(m,opt,V,...) m(35, V, opt, __VA_ARGS__) omp_for_2nd_34(m, opt, __VA_ARGS__)
#define omp_for_2nd_36(m,opt,V,...) m(36, V, opt, __VA_ARGS__) omp_for_2nd_35(m, opt, __VA_ARGS__)
#define omp_for_2nd_37(m,opt,V,...) m(37, V, opt, __VA_ARGS__) omp_for_2nd_36(m, opt, __VA_ARGS__)
#define omp_for_2nd_38(m,opt,V,...) m(38, V, opt, __VA_ARGS__) omp_for_2nd_37(m, opt, __VA_ARGS__)
#define omp_for_2nd_39(m,opt,V,...) m(39, V, opt, __VA_ARGS__) omp_for_2nd_38(m, opt, __VA_ARGS__)
#define omp_for_2nd_40(m,opt,V,...) m(40, V, opt, __VA_ARGS__) omp_for_2nd_39(m, opt, __VA_ARGS__)
#define omp_for_2nd_41(m,opt,V,...) m(41, V, opt, __VA_ARGS__) omp_for_2nd_40(m, opt, __VA_ARGS__)
#define omp_for_2nd_42(m,opt,V,...) m(42, V, opt, __VA_ARGS__) omp_for_2nd_41(m, opt, __VA_ARGS__)
#define omp_for_2nd_43(m,opt,V,...) m(43, V, opt, __VA_ARGS__) omp_for_2nd_42(m, opt, __VA_ARGS__)
#define omp_for_2nd_44(m,opt,V,...) m(44, V, opt, __VA_ARGS__) omp_for_2nd_43(m, opt, __VA_ARGS__)
#define omp_for_2nd_45(m,opt,V,...) m(45, V, opt, __VA_ARGS__) omp_for_2nd_44(m, opt, __VA_ARGS__)
#define omp_for_2nd_46(m,opt,V,...) m(46, V, opt, __VA_ARGS__) omp_for_2nd_45(m, opt, __VA_ARGS__)
#define omp_for_2nd_47(m,opt,V,...) m(47, V, opt, __VA_ARGS__) omp_for_2nd_46(m, opt, __VA_ARGS__)
#define omp_for_2nd_48(m,opt,V,...) m(48, V, opt, __VA_ARGS__) omp_for_2nd_47(m, opt, __VA_ARGS__)
#define omp_for_2nd_49(m,opt,V,...) m(49, V, opt, __VA_ARGS__) omp_for_2nd_48(m, opt, __VA_ARGS__)
#define omp_for_2nd_50(m,opt,V,...) m(50, V, opt, __VA_ARGS__) omp_for_2nd_49(m, opt, __VA_ARGS__)
#define omp_for_2nd_51(m,opt,V,...) m(51, V, opt, __VA_ARGS__) omp_for_2nd_50(m, opt, __VA_ARGS__)
#define omp_for_2nd_52(m,opt,V,...) m(52, V, opt, __VA_ARGS__) omp_for_2nd_51(m, opt, __VA_ARGS__)
#define omp_for_2nd_53(m,opt,V,...) m(53, V, opt, __VA_ARGS__) omp_for_2nd_52(m, opt, __VA_ARGS__)
#define omp_for_2nd_54(m,opt,V,...) m(54, V, opt, __VA_ARGS__) omp_for_2nd_53(m, opt, __VA_ARGS__)
#define omp_for_2nd_55(m,opt,V,...) m(55, V, opt, __VA_ARGS__) omp_for_2nd_54(m, opt, __VA_ARGS__)
#define omp_for_2nd_56(m,opt,V,...) m(56, V, opt, __VA_ARGS__) omp_for_2nd_55(m, opt, __VA_ARGS__)
#define omp_for_2nd_57(m,opt,V,...) m(57, V, opt, __VA_ARGS__) omp_for_2nd_56(m, opt, __VA_ARGS__)
#define omp_for_2nd_58(m,opt,V,...) m(58, V, opt, __VA_ARGS__) omp_for_2nd_57(m, opt, __VA_ARGS__)
#define omp_for_2nd_59(m,opt,V,...) m(59, V, opt, __VA_ARGS__) omp_for_2nd_58(m, opt, __VA_ARGS__)
#define omp_for_2nd_60(m,opt,V,...) m(60, V, opt, __VA_ARGS__) omp_for_2nd_59(m, opt, __VA_ARGS__)
#define omp_for_2nd_61(m,opt,V,...) m(61, V, opt, __VA_ARGS__) omp_for_2nd_60(m, opt, __VA_ARGS__)
#define omp_for_2nd_62(m,opt,V,...) m(62, V, opt, __VA_ARGS__) omp_for_2nd_61(m, opt, __VA_ARGS__)
#define omp_for_2nd_63(m,opt,V,...) m(63, V, opt, __VA_ARGS__) omp_for_2nd_62(m, opt, __VA_ARGS__)
#define omp_for_2nd_64(m,opt,V,...) m(64, V, opt, __VA_ARGS__) omp_for_2nd_63(m, opt, __VA_ARGS__)
#define omp_for_2nd_65(m,opt,V,...) m(65, V, opt, __VA_ARGS__) omp_for_2nd_64(m, opt, __VA_ARGS__)
#define omp_for_2nd_66(m,opt,V,...) m(66, V, opt, __VA_ARGS__) omp_for_2nd_65(m, opt, __VA_ARGS__)
#define omp_for_2nd_67(m,opt,V,...) m(67, V, opt, __VA_ARGS__) omp_for_2nd_66(m, opt, __VA_ARGS__)
#define omp_for_2nd_68(m,opt,V,...) m(68, V, opt, __VA_ARGS__) omp_for_2nd_67(m, opt, __VA_ARGS__)
#define omp_for_2nd_69(m,opt,V,...) m(69, V, opt, __VA_ARGS__) omp_for_2nd_68(m, opt, __VA_ARGS__)
#define omp_for_2nd_70(m,opt,V,...) m(70, V, opt, __VA_ARGS__) omp_for_2nd_69(m, opt, __VA_ARGS__)
#define omp_for_2nd_71(m,opt,V,...) m(71, V, opt, __VA_ARGS__) omp_for_2nd_70(m, opt, __VA_ARGS__)
#define omp_for_2nd_72(m,opt,V,...) m(72, V, opt, __VA_ARGS__) omp_for_2nd_71(m, opt, __VA_ARGS__)
#define omp_for_2nd_73(m,opt,V,...) m(73, V, opt, __VA_ARGS__) omp_for_2nd_72(m, opt, __VA_ARGS__)
#define omp_for_2nd_74(m,opt,V,...) m(74, V, opt, __VA_ARGS__) omp_for_2nd_73(m, opt, __VA_ARGS__)
#define omp_for_2nd_75(m,opt,V,...) m(75, V, opt, __VA_ARGS__) omp_for_2nd_74(m, opt, __VA_ARGS__)
#define omp_for_2nd_76(m,opt,V,...) m(76, V, opt, __VA_ARGS__) omp_for_2nd_75(m, opt, __VA_ARGS__)
#define omp_for_2nd_77(m,opt,V,...) m(77, V, opt, __VA_ARGS__) omp_for_2nd_76(m, opt, __VA_ARGS__)
#define omp_for_2nd_78(m,opt,V,...) m(78, V, opt, __VA_ARGS__) omp_for_2nd_77(m, opt, __VA_ARGS__)
#define omp_for_2nd_79(m,opt,V,...) m(79, V, opt, __VA_ARGS__) omp_for_2nd_78(m, opt, __VA_ARGS__)
#define omp_for_2nd_80(m,opt,V,...) m(80, V, opt, __VA_ARGS__) omp_for_2nd_79(m, opt, __VA_ARGS__)
#define omp_for_2nd_81(m,opt,V,...) m(81, V, opt, __VA_ARGS__) omp_for_2nd_80(m, opt, __VA_ARGS__)
#define omp_for_2nd_82(m,opt,V,...) m(82, V, opt, __VA_ARGS__) omp_for_2nd_81(m, opt, __VA_ARGS__)
#define omp_for_2nd_83(m,opt,V,...) m(83, V, opt, __VA_ARGS__) omp_for_2nd_82(m, opt, __VA_ARGS__)
#define omp_for_2nd_84(m,opt,V,...) m(84, V, opt, __VA_ARGS__) omp_for_2nd_83(m, opt, __VA_ARGS__)
#define omp_for_2nd_85(m,opt,V,...) m(85, V, opt, __VA_ARGS__) omp_for_2nd_84(m, opt, __VA_ARGS__)
#define omp_for_2nd_86(m,opt,V,...) m(86, V, opt, __VA_ARGS__) omp_for_2nd_85(m, opt, __VA_ARGS__)
#define omp_for_2nd_87(m,opt,V,...) m(87, V, opt, __VA_ARGS__) omp_for_2nd_86(m, opt, __VA_ARGS__)
#define omp_for_2nd_88(m,opt,V,...) m(88, V, opt, __VA_ARGS__) omp_for_2nd_87(m, opt, __VA_ARGS__)
#define omp_for_2nd_89(m,opt,V,...) m(89, V, opt, __VA_ARGS__) omp_for_2nd_88(m, opt, __VA_ARGS__)
#define omp_for_2nd_90(m,opt,V,...) m(90, V, opt, __VA_ARGS__) omp_for_2nd_89(m, opt, __VA_ARGS__)
#define omp_for_2nd_91(m,opt,V,...) m(91, V, opt, __VA_ARGS__) omp_for_2nd_90(m, opt, __VA_ARGS__)
#define omp_for_2nd_92(m,opt,V,...) m(92, V, opt, __VA_ARGS__) omp_for_2nd_91(m, opt, __VA_ARGS__)
#define omp_for_2nd_93(m,opt,V,...) m(93, V, opt, __VA_ARGS__) omp_for_2nd_92(m, opt, __VA_ARGS__)
#define omp_for_2nd_94(m,opt,V,...) m(94, V, opt, __VA_ARGS__) omp_for_2nd_93(m, opt, __VA_ARGS__)
#define omp_for_2nd_95(m,opt,V,...) m(95, V, opt, __VA_ARGS__) omp_for_2nd_94(m, opt, __VA_ARGS__)
#define omp_for_2nd_96(m,opt,V,...) m(96, V, opt, __VA_ARGS__) omp_for_2nd_95(m, opt, __VA_ARGS__)



#define omp_for_3rd_0(m,opt,V,...) 
#define omp_for_3rd_1(m,opt,V,...) m(1, V, opt, __VA_ARGS__)
#define omp_for_3rd_2(m,opt,V,...) m(2, V, opt, __VA_ARGS__) omp_for_3rd_1(m, opt, __VA_ARGS__)
#define omp_for_3rd_3(m,opt,V,...) m(3, V, opt, __VA_ARGS__) omp_for_3rd_2(m, opt, __VA_ARGS__)
#define omp_for_3rd_4(m,opt,V,...) m(4, V, opt, __VA_ARGS__) omp_for_3rd_3(m, opt, __VA_ARGS__)
#define omp_for_3rd_5(m,opt,V,...) m(5, V, opt, __VA_ARGS__) omp_for_3rd_4(m, opt, __VA_ARGS__)
#define omp_for_3rd_6(m,opt,V,...) m(6, V, opt, __VA_ARGS__) omp_for_3rd_5(m, opt, __VA_ARGS__)
#define omp_for_3rd_7(m,opt,V,...) m(7, V, opt, __VA_ARGS__) omp_for_3rd_6(m, opt, __VA_ARGS__)
#define omp_for_3rd_8(m,opt,V,...) m(8, V, opt, __VA_ARGS__) omp_for_3rd_7(m, opt, __VA_ARGS__)
#define omp_for_3rd_9(m,opt,V,...) m(9, V, opt, __VA_ARGS__) omp_for_3rd_8(m, opt, __VA_ARGS__)
#define omp_for_3rd_10(m,opt,V,...) m(10, V, opt, __VA_ARGS__) omp_for_3rd_9(m, opt, __VA_ARGS__)
#define omp_for_3rd_11(m,opt,V,...) m(11, V, opt, __VA_ARGS__) omp_for_3rd_10(m, opt, __VA_ARGS__)
#define omp_for_3rd_12(m,opt,V,...) m(12, V, opt, __VA_ARGS__) omp_for_3rd_11(m, opt, __VA_ARGS__)
#define omp_for_3rd_13(m,opt,V,...) m(13, V, opt, __VA_ARGS__) omp_for_3rd_12(m, opt, __VA_ARGS__)
#define omp_for_3rd_14(m,opt,V,...) m(14, V, opt, __VA_ARGS__) omp_for_3rd_13(m, opt, __VA_ARGS__)
#define omp_for_3rd_15(m,opt,V,...) m(15, V, opt, __VA_ARGS__) omp_for_3rd_14(m, opt, __VA_ARGS__)
#define omp_for_3rd_16(m,opt,V,...) m(16, V, opt, __VA_ARGS__) omp_for_3rd_15(m, opt, __VA_ARGS__)
#define omp_for_3rd_17(m,opt,V,...) m(17, V, opt, __VA_ARGS__) omp_for_3rd_16(m, opt, __VA_ARGS__)
#define omp_for_3rd_18(m,opt,V,...) m(18, V, opt, __VA_ARGS__) omp_for_3rd_17(m, opt, __VA_ARGS__)
#define omp_for_3rd_19(m,opt,V,...) m(19, V, opt, __VA_ARGS__) omp_for_3rd_18(m, opt, __VA_ARGS__)
#define omp_for_3rd_20(m,opt,V,...) m(20, V, opt, __VA_ARGS__) omp_for_3rd_19(m, opt, __VA_ARGS__)
#define omp_for_3rd_21(m,opt,V,...) m(21, V, opt, __VA_ARGS__) omp_for_3rd_20(m, opt, __VA_ARGS__)
#define omp_for_3rd_22(m,opt,V,...) m(22, V, opt, __VA_ARGS__) omp_for_3rd_21(m, opt, __VA_ARGS__)
#define omp_for_3rd_23(m,opt,V,...) m(23, V, opt, __VA_ARGS__) omp_for_3rd_22(m, opt, __VA_ARGS__)
#define omp_for_3rd_24(m,opt,V,...) m(24, V, opt, __VA_ARGS__) omp_for_3rd_23(m, opt, __VA_ARGS__)
#define omp_for_3rd_25(m,opt,V,...) m(25, V, opt, __VA_ARGS__) omp_for_3rd_24(m, opt, __VA_ARGS__)
#define omp_for_3rd_26(m,opt,V,...) m(26, V, opt, __VA_ARGS__) omp_for_3rd_25(m, opt, __VA_ARGS__)
#define omp_for_3rd_27(m,opt,V,...) m(27, V, opt, __VA_ARGS__) omp_for_3rd_26(m, opt, __VA_ARGS__)
#define omp_for_3rd_28(m,opt,V,...) m(28, V, opt, __VA_ARGS__) omp_for_3rd_27(m, opt, __VA_ARGS__)
#define omp_for_3rd_29(m,opt,V,...) m(29, V, opt, __VA_ARGS__) omp_for_3rd_28(m, opt, __VA_ARGS__)
#define omp_for_3rd_30(m,opt,V,...) m(30, V, opt, __VA_ARGS__) omp_for_3rd_29(m, opt, __VA_ARGS__)
#define omp_for_3rd_31(m,opt,V,...) m(31, V, opt, __VA_ARGS__) omp_for_3rd_30(m, opt, __VA_ARGS__)
#define omp_for_3rd_32(m,opt,V,...) m(32, V, opt, __VA_ARGS__) omp_for_3rd_31(m, opt, __VA_ARGS__)
#define omp_for_3rd_33(m,opt,V,...) m(33, V, opt, __VA_ARGS__) omp_for_3rd_32(m, opt, __VA_ARGS__)
#define omp_for_3rd_34(m,opt,V,...) m(34, V, opt, __VA_ARGS__) omp_for_3rd_33(m, opt, __VA_ARGS__)
#define omp_for_3rd_35(m,opt,V,...) m(35, V, opt, __VA_ARGS__) omp_for_3rd_34(m, opt, __VA_ARGS__)
#define omp_for_3rd_36(m,opt,V,...) m(36, V, opt, __VA_ARGS__) omp_for_3rd_35(m, opt, __VA_ARGS__)
#define omp_for_3rd_37(m,opt,V,...) m(37, V, opt, __VA_ARGS__) omp_for_3rd_36(m, opt, __VA_ARGS__)
#define omp_for_3rd_38(m,opt,V,...) m(38, V, opt, __VA_ARGS__) omp_for_3rd_37(m, opt, __VA_ARGS__)
#define omp_for_3rd_39(m,opt,V,...) m(39, V, opt, __VA_ARGS__) omp_for_3rd_38(m, opt, __VA_ARGS__)
#define omp_for_3rd_40(m,opt,V,...) m(40, V, opt, __VA_ARGS__) omp_for_3rd_39(m, opt, __VA_ARGS__)
#define omp_for_3rd_41(m,opt,V,...) m(41, V, opt, __VA_ARGS__) omp_for_3rd_40(m, opt, __VA_ARGS__)
#define omp_for_3rd_42(m,opt,V,...) m(42, V, opt, __VA_ARGS__) omp_for_3rd_41(m, opt, __VA_ARGS__)
#define omp_for_3rd_43(m,opt,V,...) m(43, V, opt, __VA_ARGS__) omp_for_3rd_42(m, opt, __VA_ARGS__)
#define omp_for_3rd_44(m,opt,V,...) m(44, V, opt, __VA_ARGS__) omp_for_3rd_43(m, opt, __VA_ARGS__)
#define omp_for_3rd_45(m,opt,V,...) m(45, V, opt, __VA_ARGS__) omp_for_3rd_44(m, opt, __VA_ARGS__)
#define omp_for_3rd_46(m,opt,V,...) m(46, V, opt, __VA_ARGS__) omp_for_3rd_45(m, opt, __VA_ARGS__)
#define omp_for_3rd_47(m,opt,V,...) m(47, V, opt, __VA_ARGS__) omp_for_3rd_46(m, opt, __VA_ARGS__)
#define omp_for_3rd_48(m,opt,V,...) m(48, V, opt, __VA_ARGS__) omp_for_3rd_47(m, opt, __VA_ARGS__)
#define omp_for_3rd_49(m,opt,V,...) m(49, V, opt, __VA_ARGS__) omp_for_3rd_48(m, opt, __VA_ARGS__)
#define omp_for_3rd_50(m,opt,V,...) m(50, V, opt, __VA_ARGS__) omp_for_3rd_49(m, opt, __VA_ARGS__)
#define omp_for_3rd_51(m,opt,V,...) m(51, V, opt, __VA_ARGS__) omp_for_3rd_50(m, opt, __VA_ARGS__)
#define omp_for_3rd_52(m,opt,V,...) m(52, V, opt, __VA_ARGS__) omp_for_3rd_51(m, opt, __VA_ARGS__)
#define omp_for_3rd_53(m,opt,V,...) m(53, V, opt, __VA_ARGS__) omp_for_3rd_52(m, opt, __VA_ARGS__)
#define omp_for_3rd_54(m,opt,V,...) m(54, V, opt, __VA_ARGS__) omp_for_3rd_53(m, opt, __VA_ARGS__)
#define omp_for_3rd_55(m,opt,V,...) m(55, V, opt, __VA_ARGS__) omp_for_3rd_54(m, opt, __VA_ARGS__)
#define omp_for_3rd_56(m,opt,V,...) m(56, V, opt, __VA_ARGS__) omp_for_3rd_55(m, opt, __VA_ARGS__)
#define omp_for_3rd_57(m,opt,V,...) m(57, V, opt, __VA_ARGS__) omp_for_3rd_56(m, opt, __VA_ARGS__)
#define omp_for_3rd_58(m,opt,V,...) m(58, V, opt, __VA_ARGS__) omp_for_3rd_57(m, opt, __VA_ARGS__)
#define omp_for_3rd_59(m,opt,V,...) m(59, V, opt, __VA_ARGS__) omp_for_3rd_58(m, opt, __VA_ARGS__)
#define omp_for_3rd_60(m,opt,V,...) m(60, V, opt, __VA_ARGS__) omp_for_3rd_59(m, opt, __VA_ARGS__)
#define omp_for_3rd_61(m,opt,V,...) m(61, V, opt, __VA_ARGS__) omp_for_3rd_60(m, opt, __VA_ARGS__)
#define omp_for_3rd_62(m,opt,V,...) m(62, V, opt, __VA_ARGS__) omp_for_3rd_61(m, opt, __VA_ARGS__)
#define omp_for_3rd_63(m,opt,V,...) m(63, V, opt, __VA_ARGS__) omp_for_3rd_62(m, opt, __VA_ARGS__)
#define omp_for_3rd_64(m,opt,V,...) m(64, V, opt, __VA_ARGS__) omp_for_3rd_63(m, opt, __VA_ARGS__)
#define omp_for_3rd_65(m,opt,V,...) m(65, V, opt, __VA_ARGS__) omp_for_3rd_64(m, opt, __VA_ARGS__)
#define omp_for_3rd_66(m,opt,V,...) m(66, V, opt, __VA_ARGS__) omp_for_3rd_65(m, opt, __VA_ARGS__)
#define omp_for_3rd_67(m,opt,V,...) m(67, V, opt, __VA_ARGS__) omp_for_3rd_66(m, opt, __VA_ARGS__)
#define omp_for_3rd_68(m,opt,V,...) m(68, V, opt, __VA_ARGS__) omp_for_3rd_67(m, opt, __VA_ARGS__)
#define omp_for_3rd_69(m,opt,V,...) m(69, V, opt, __VA_ARGS__) omp_for_3rd_68(m, opt, __VA_ARGS__)
#define omp_for_3rd_70(m,opt,V,...) m(70, V, opt, __VA_ARGS__) omp_for_3rd_69(m, opt, __VA_ARGS__)
#define omp_for_3rd_71(m,opt,V,...) m(71, V, opt, __VA_ARGS__) omp_for_3rd_70(m, opt, __VA_ARGS__)
#define omp_for_3rd_72(m,opt,V,...) m(72, V, opt, __VA_ARGS__) omp_for_3rd_71(m, opt, __VA_ARGS__)
#define omp_for_3rd_73(m,opt,V,...) m(73, V, opt, __VA_ARGS__) omp_for_3rd_72(m, opt, __VA_ARGS__)
#define omp_for_3rd_74(m,opt,V,...) m(74, V, opt, __VA_ARGS__) omp_for_3rd_73(m, opt, __VA_ARGS__)
#define omp_for_3rd_75(m,opt,V,...) m(75, V, opt, __VA_ARGS__) omp_for_3rd_74(m, opt, __VA_ARGS__)
#define omp_for_3rd_76(m,opt,V,...) m(76, V, opt, __VA_ARGS__) omp_for_3rd_75(m, opt, __VA_ARGS__)
#define omp_for_3rd_77(m,opt,V,...) m(77, V, opt, __VA_ARGS__) omp_for_3rd_76(m, opt, __VA_ARGS__)
#define omp_for_3rd_78(m,opt,V,...) m(78, V, opt, __VA_ARGS__) omp_for_3rd_77(m, opt, __VA_ARGS__)
#define omp_for_3rd_79(m,opt,V,...) m(79, V, opt, __VA_ARGS__) omp_for_3rd_78(m, opt, __VA_ARGS__)
#define omp_for_3rd_80(m,opt,V,...) m(80, V, opt, __VA_ARGS__) omp_for_3rd_79(m, opt, __VA_ARGS__)
#define omp_for_3rd_81(m,opt,V,...) m(81, V, opt, __VA_ARGS__) omp_for_3rd_80(m, opt, __VA_ARGS__)
#define omp_for_3rd_82(m,opt,V,...) m(82, V, opt, __VA_ARGS__) omp_for_3rd_81(m, opt, __VA_ARGS__)
#define omp_for_3rd_83(m,opt,V,...) m(83, V, opt, __VA_ARGS__) omp_for_3rd_82(m, opt, __VA_ARGS__)
#define omp_for_3rd_84(m,opt,V,...) m(84, V, opt, __VA_ARGS__) omp_for_3rd_83(m, opt, __VA_ARGS__)
#define omp_for_3rd_85(m,opt,V,...) m(85, V, opt, __VA_ARGS__) omp_for_3rd_84(m, opt, __VA_ARGS__)
#define omp_for_3rd_86(m,opt,V,...) m(86, V, opt, __VA_ARGS__) omp_for_3rd_85(m, opt, __VA_ARGS__)
#define omp_for_3rd_87(m,opt,V,...) m(87, V, opt, __VA_ARGS__) omp_for_3rd_86(m, opt, __VA_ARGS__)
#define omp_for_3rd_88(m,opt,V,...) m(88, V, opt, __VA_ARGS__) omp_for_3rd_87(m, opt, __VA_ARGS__)
#define omp_for_3rd_89(m,opt,V,...) m(89, V, opt, __VA_ARGS__) omp_for_3rd_88(m, opt, __VA_ARGS__)
#define omp_for_3rd_90(m,opt,V,...) m(90, V, opt, __VA_ARGS__) omp_for_3rd_89(m, opt, __VA_ARGS__)
#define omp_for_3rd_91(m,opt,V,...) m(91, V, opt, __VA_ARGS__) omp_for_3rd_90(m, opt, __VA_ARGS__)
#define omp_for_3rd_92(m,opt,V,...) m(92, V, opt, __VA_ARGS__) omp_for_3rd_91(m, opt, __VA_ARGS__)
#define omp_for_3rd_93(m,opt,V,...) m(93, V, opt, __VA_ARGS__) omp_for_3rd_92(m, opt, __VA_ARGS__)
#define omp_for_3rd_94(m,opt,V,...) m(94, V, opt, __VA_ARGS__) omp_for_3rd_93(m, opt, __VA_ARGS__)
#define omp_for_3rd_95(m,opt,V,...) m(95, V, opt, __VA_ARGS__) omp_for_3rd_94(m, opt, __VA_ARGS__)
#define omp_for_3rd_96(m,opt,V,...) m(96, V, opt, __VA_ARGS__) omp_for_3rd_95(m, opt, __VA_ARGS__)

#define omp_if_0(is_zero, not_zero, ...) is_zero(__VA_ARGS__)
#define omp_if_1(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_3(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_4(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_5(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_6(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_7(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_8(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_9(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_10(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_11(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_12(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_13(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_14(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_15(is_zero, not_zero, ...) not_zero(__VA_ARGS__)

#define omp_if_2nd_0(is_zero, not_zero, ...) is_zero(__VA_ARGS__)
#define omp_if_2nd_1(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_2(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_3(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_4(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_5(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_6(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_7(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_8(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_9(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_10(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_11(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_12(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_13(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_14(is_zero, not_zero, ...) not_zero(__VA_ARGS__)
#define omp_if_2nd_15(is_zero, not_zero, ...) not_zero(__VA_ARGS__)

#define omp_decr0 0
#define omp_decr1 0
#define omp_decr2 1
#define omp_decr3 2
#define omp_decr4 3
#define omp_decrement(V) omp_glue2(omp_decr, V)

#define omp_if_zero(V, is_zero, not_zero, ...) omp_glue2(omp_if_, V)(is_zero, not_zero, __VA_ARGS__)
#define omp_if_2nd_zero(V, is_zero, not_zero, ...) omp_glue2(omp_if_2nd_, V)(is_zero, not_zero, __VA_ARGS__)

#define omp_pack_(...) __VA_ARGS__
#define omp_pack__(...) __VA_ARGS__