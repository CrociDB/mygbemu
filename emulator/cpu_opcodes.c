#include "cpu_opcodes.h"

void cpu_init_table()
{
    log_message("Initializing CPU OP Table");

    optable[0x00] = (opfunc_t) { &cpu_op_00, 1, 4, 0 };
    optable[0x01] = (opfunc_t) { &cpu_op_01, 3, 12, 2 };
    optable[0x02] = (opfunc_t) { &cpu_op_02, 1, 8, 0 };
    optable[0x03] = (opfunc_t) { &cpu_op_03, 1, 8, 0 };
    optable[0x04] = (opfunc_t) { &cpu_op_04, 1, 4, 0 };
    optable[0x05] = (opfunc_t) { &cpu_op_05, 1, 4, 0 };
    optable[0x06] = (opfunc_t) { &cpu_op_06, 2, 8, 1 };
    optable[0x07] = (opfunc_t) { &cpu_op_07, 1, 4, 0 };
    optable[0x08] = (opfunc_t) { &cpu_op_08, 5, 20, 2 };
    optable[0x09] = (opfunc_t) { &cpu_op_09, 2, 8, 0 };
    optable[0x0A] = (opfunc_t) { &cpu_op_0a, 1, 8, 0 };
    optable[0x0B] = (opfunc_t) { &cpu_op_0b, 1, 8, 0 };
    optable[0x0C] = (opfunc_t) { &cpu_op_0c, 1, 4, 0 };
    optable[0x0D] = (opfunc_t) { &cpu_op_0d, 1, 4, 0 };
    optable[0x0E] = (opfunc_t) { &cpu_op_0e, 2, 8, 1 };
    optable[0x0F] = (opfunc_t) { &cpu_op_0f, 1, 4, 0 };

    optable[0x11] = (opfunc_t) { &cpu_op_11, 3, 12, 2 };
    optable[0x12] = (opfunc_t) { &cpu_op_12, 1, 8, 0 };
    optable[0x13] = (opfunc_t) { &cpu_op_13, 1, 8, 0 };
    optable[0x14] = (opfunc_t) { &cpu_op_14, 1, 4, 0 };
    optable[0x15] = (opfunc_t) { &cpu_op_15, 1, 4, 0 };
    optable[0x16] = (opfunc_t) { &cpu_op_16, 2, 8, 1 };
    optable[0x17] = (opfunc_t) { &cpu_op_17, 1, 4, 0 };
    optable[0x19] = (opfunc_t) { &cpu_op_19, 2, 8, 0 };
    optable[0x18] = (opfunc_t) { &cpu_op_18, 2, 12, 1 };
    optable[0x1A] = (opfunc_t) { &cpu_op_1a, 1, 8, 0 };
    optable[0x1B] = (opfunc_t) { &cpu_op_1b, 1, 8, 0 };
    optable[0x1C] = (opfunc_t) { &cpu_op_1c, 1, 4, 0 };
    optable[0x1D] = (opfunc_t) { &cpu_op_1d, 1, 4, 0 };
    optable[0x1E] = (opfunc_t) { &cpu_op_1e, 2, 8, 1 };
    optable[0x1F] = (opfunc_t) { &cpu_op_1f, 1, 4, 0 };

    optable[0x20] = (opfunc_t) { &cpu_op_20, 2, 8, 1 };
    optable[0x21] = (opfunc_t) { &cpu_op_21, 3, 12, 2 };
    optable[0x22] = (opfunc_t) { &cpu_op_22, 1, 8, 0 };
    optable[0x23] = (opfunc_t) { &cpu_op_23, 1, 8, 0 };
    optable[0x24] = (opfunc_t) { &cpu_op_24, 1, 4, 0 };
    optable[0x25] = (opfunc_t) { &cpu_op_25, 1, 4, 0 };
    optable[0x26] = (opfunc_t) { &cpu_op_26, 2, 8, 1 };
    optable[0x27] = (opfunc_t) { &cpu_op_27, 1, 4, 0 };
    optable[0x28] = (opfunc_t) { &cpu_op_28, 2, 8, 1 };
    optable[0x29] = (opfunc_t) { &cpu_op_29, 2, 8, 0 };
    optable[0x2A] = (opfunc_t) { &cpu_op_2a, 1, 8, 0 };
    optable[0x2B] = (opfunc_t) { &cpu_op_2b, 1, 8, 0 };
    optable[0x2C] = (opfunc_t) { &cpu_op_2c, 1, 4, 0 };
    optable[0x2D] = (opfunc_t) { &cpu_op_2d, 1, 4, 0 };
    optable[0x2E] = (opfunc_t) { &cpu_op_2e, 2, 8, 1 };
    optable[0x2F] = (opfunc_t) { &cpu_op_2f, 1, 4, 0 };

    optable[0x30] = (opfunc_t) { &cpu_op_30, 2, 8, 1 };
    optable[0x31] = (opfunc_t) { &cpu_op_31, 3, 13, 2 };
    optable[0x32] = (opfunc_t) { &cpu_op_32, 1, 8, 0 };
    optable[0x33] = (opfunc_t) { &cpu_op_33, 1, 8, 0 };
    optable[0x34] = (opfunc_t) { &cpu_op_34, 1, 12, 0 };
    optable[0x35] = (opfunc_t) { &cpu_op_35, 1, 12, 0 };
    optable[0x36] = (opfunc_t) { &cpu_op_36, 2, 12, 1 };
    optable[0x37] = (opfunc_t) { &cpu_op_37, 1, 4, 0 };
    optable[0x38] = (opfunc_t) { &cpu_op_38, 2, 8, 1 };
    optable[0x39] = (opfunc_t) { &cpu_op_39, 2, 8, 0 };
    optable[0x3A] = (opfunc_t) { &cpu_op_3a, 1, 8, 0 };
    optable[0x3B] = (opfunc_t) { &cpu_op_3b, 1, 8, 0 };
    optable[0x3C] = (opfunc_t) { &cpu_op_3c, 1, 4, 0 };
    optable[0x3D] = (opfunc_t) { &cpu_op_3d, 1, 4, 0 };
    optable[0x3E] = (opfunc_t) { &cpu_op_3e, 2, 8, 1 };
    optable[0x3F] = (opfunc_t) { &cpu_op_3f, 1, 4, 0 };

    optable[0x40] = (opfunc_t) { &cpu_op_40, 1, 4, 0 };
    optable[0x41] = (opfunc_t) { &cpu_op_41, 1, 4, 0 };
    optable[0x42] = (opfunc_t) { &cpu_op_42, 1, 4, 0 };
    optable[0x43] = (opfunc_t) { &cpu_op_43, 1, 4, 0 };
    optable[0x44] = (opfunc_t) { &cpu_op_44, 1, 4, 0 };
    optable[0x45] = (opfunc_t) { &cpu_op_45, 1, 4, 0 };
    optable[0x46] = (opfunc_t) { &cpu_op_46, 1, 8, 0 };
    optable[0x47] = (opfunc_t) { &cpu_op_47, 1, 4, 0 };
    optable[0x48] = (opfunc_t) { &cpu_op_48, 1, 4, 0 };
    optable[0x49] = (opfunc_t) { &cpu_op_49, 1, 4, 0 };
    optable[0x4A] = (opfunc_t) { &cpu_op_4a, 1, 4, 0 };
    optable[0x4B] = (opfunc_t) { &cpu_op_4b, 1, 4, 0 };
    optable[0x4C] = (opfunc_t) { &cpu_op_4c, 1, 4, 0 };
    optable[0x4D] = (opfunc_t) { &cpu_op_4d, 1, 4, 0 };
    optable[0x4E] = (opfunc_t) { &cpu_op_4e, 1, 8, 0 };
    optable[0x4F] = (opfunc_t) { &cpu_op_4f, 1, 4, 0 };

    optable[0x50] = (opfunc_t) { &cpu_op_50, 1, 4, 0 };
    optable[0x51] = (opfunc_t) { &cpu_op_51, 1, 4, 0 };
    optable[0x52] = (opfunc_t) { &cpu_op_52, 1, 4, 0 };
    optable[0x53] = (opfunc_t) { &cpu_op_53, 1, 4, 0 };
    optable[0x54] = (opfunc_t) { &cpu_op_54, 1, 4, 0 };
    optable[0x55] = (opfunc_t) { &cpu_op_55, 1, 4, 0 };
    optable[0x56] = (opfunc_t) { &cpu_op_56, 1, 8, 0 };
    optable[0x57] = (opfunc_t) { &cpu_op_57, 1, 4, 0 };
    optable[0x58] = (opfunc_t) { &cpu_op_58, 1, 4, 0 };
    optable[0x59] = (opfunc_t) { &cpu_op_59, 1, 4, 0 };
    optable[0x5A] = (opfunc_t) { &cpu_op_5a, 1, 4, 0 };
    optable[0x5B] = (opfunc_t) { &cpu_op_5b, 1, 4, 0 };
    optable[0x5C] = (opfunc_t) { &cpu_op_5c, 1, 4, 0 };
    optable[0x5D] = (opfunc_t) { &cpu_op_5d, 1, 4, 0 };
    optable[0x5E] = (opfunc_t) { &cpu_op_5e, 1, 8, 0 };
    optable[0x5F] = (opfunc_t) { &cpu_op_5f, 1, 4, 0 };

    optable[0x60] = (opfunc_t) { &cpu_op_60, 1, 4, 0 };
    optable[0x61] = (opfunc_t) { &cpu_op_61, 1, 4, 0 };
    optable[0x62] = (opfunc_t) { &cpu_op_62, 1, 4, 0 };
    optable[0x63] = (opfunc_t) { &cpu_op_63, 1, 4, 0 };
    optable[0x64] = (opfunc_t) { &cpu_op_64, 1, 4, 0 };
    optable[0x65] = (opfunc_t) { &cpu_op_65, 1, 4, 0 };
    optable[0x66] = (opfunc_t) { &cpu_op_66, 1, 8, 0 };
    optable[0x67] = (opfunc_t) { &cpu_op_67, 1, 4, 0 };
    optable[0x68] = (opfunc_t) { &cpu_op_68, 1, 4, 0 };
    optable[0x69] = (opfunc_t) { &cpu_op_69, 1, 4, 0 };
    optable[0x6A] = (opfunc_t) { &cpu_op_6a, 1, 4, 0 };
    optable[0x6B] = (opfunc_t) { &cpu_op_6b, 1, 4, 0 };
    optable[0x6C] = (opfunc_t) { &cpu_op_6c, 1, 4, 0 };
    optable[0x6D] = (opfunc_t) { &cpu_op_6d, 1, 4, 0 };
    optable[0x6E] = (opfunc_t) { &cpu_op_6e, 1, 8, 0 };
    optable[0x6F] = (opfunc_t) { &cpu_op_6f, 1, 4, 0 };

    optable[0x70] = (opfunc_t) { &cpu_op_70, 1, 8, 0 };
    optable[0x71] = (opfunc_t) { &cpu_op_71, 1, 8, 0 };
    optable[0x72] = (opfunc_t) { &cpu_op_72, 1, 8, 0 };
    optable[0x73] = (opfunc_t) { &cpu_op_73, 1, 8, 0 };
    optable[0x74] = (opfunc_t) { &cpu_op_74, 1, 8, 0 };
    optable[0x75] = (opfunc_t) { &cpu_op_75, 1, 8, 0 };
    //optable[0x76] = (opfunc_t) { &cpu_op_76, 1, 4, 0 };
    optable[0x77] = (opfunc_t) { &cpu_op_77, 1, 8, 0 };
    optable[0x78] = (opfunc_t) { &cpu_op_78, 1, 4, 0 };
    optable[0x79] = (opfunc_t) { &cpu_op_79, 1, 4, 0 };
    optable[0x7A] = (opfunc_t) { &cpu_op_7a, 1, 4, 0 };
    optable[0x7B] = (opfunc_t) { &cpu_op_7b, 1, 4, 0 };
    optable[0x7C] = (opfunc_t) { &cpu_op_7c, 1, 4, 0 };
    optable[0x7D] = (opfunc_t) { &cpu_op_7d, 1, 4, 0 };
    optable[0x7E] = (opfunc_t) { &cpu_op_7e, 1, 8, 0 };
    optable[0x7F] = (opfunc_t) { &cpu_op_7f, 1, 4, 0 };

    optable[0x80] = (opfunc_t) { &cpu_op_80, 1, 4, 0 };
    optable[0x81] = (opfunc_t) { &cpu_op_81, 1, 4, 0 };
    optable[0x82] = (opfunc_t) { &cpu_op_82, 1, 4, 0 };
    optable[0x83] = (opfunc_t) { &cpu_op_83, 1, 4, 0 };
    optable[0x84] = (opfunc_t) { &cpu_op_84, 1, 4, 0 };
    optable[0x85] = (opfunc_t) { &cpu_op_85, 1, 4, 0 };
    optable[0x86] = (opfunc_t) { &cpu_op_86, 1, 8, 0 };
    optable[0x87] = (opfunc_t) { &cpu_op_87, 1, 4, 0 };
    optable[0x88] = (opfunc_t) { &cpu_op_88, 1, 4, 0 };
    optable[0x89] = (opfunc_t) { &cpu_op_89, 1, 4, 0 };
    optable[0x8A] = (opfunc_t) { &cpu_op_8a, 1, 4, 0 };
    optable[0x8B] = (opfunc_t) { &cpu_op_8b, 1, 4, 0 };
    optable[0x8C] = (opfunc_t) { &cpu_op_8c, 1, 4, 0 };
    optable[0x8D] = (opfunc_t) { &cpu_op_8d, 1, 4, 0 };
    optable[0x8E] = (opfunc_t) { &cpu_op_8e, 2, 8, 0 };
    optable[0x8F] = (opfunc_t) { &cpu_op_8f, 1, 4, 0 };

    optable[0x90] = (opfunc_t) { &cpu_op_90, 1, 4, 0 };
    optable[0x91] = (opfunc_t) { &cpu_op_91, 1, 4, 0 };
    optable[0x92] = (opfunc_t) { &cpu_op_92, 1, 4, 0 };
    optable[0x93] = (opfunc_t) { &cpu_op_93, 1, 4, 0 };
    optable[0x94] = (opfunc_t) { &cpu_op_94, 1, 4, 0 };
    optable[0x95] = (opfunc_t) { &cpu_op_95, 1, 4, 0 };
    optable[0x96] = (opfunc_t) { &cpu_op_96, 1, 8, 0 };
    optable[0x97] = (opfunc_t) { &cpu_op_97, 1, 4, 0 };
    optable[0x98] = (opfunc_t) { &cpu_op_98, 1, 4, 0 };
    optable[0x99] = (opfunc_t) { &cpu_op_99, 1, 4, 0 };
    optable[0x9A] = (opfunc_t) { &cpu_op_9a, 1, 4, 0 };
    optable[0x9B] = (opfunc_t) { &cpu_op_9b, 1, 4, 0 };
    optable[0x9C] = (opfunc_t) { &cpu_op_9c, 1, 4, 0 };
    optable[0x9D] = (opfunc_t) { &cpu_op_9d, 1, 4, 0 };
    optable[0x9E] = (opfunc_t) { &cpu_op_9e, 1, 8, 0 };
    optable[0x9F] = (opfunc_t) { &cpu_op_9f, 1, 4, 0 };

    optable[0xA0] = (opfunc_t) { &cpu_op_a0, 1, 4, 0 };
    optable[0xA1] = (opfunc_t) { &cpu_op_a1, 1, 4, 0 };
    optable[0xA2] = (opfunc_t) { &cpu_op_a2, 1, 4, 0 };
    optable[0xA3] = (opfunc_t) { &cpu_op_a3, 1, 4, 0 };
    optable[0xA4] = (opfunc_t) { &cpu_op_a4, 1, 4, 0 };
    optable[0xA5] = (opfunc_t) { &cpu_op_a5, 1, 4, 0 };
    optable[0xA6] = (opfunc_t) { &cpu_op_a6, 2, 8, 0 };
    optable[0xA7] = (opfunc_t) { &cpu_op_a7, 1, 4, 0 };
    optable[0xA8] = (opfunc_t) { &cpu_op_a8, 1, 4, 0 };
    optable[0xA9] = (opfunc_t) { &cpu_op_a9, 1, 4, 0 };
    optable[0xAA] = (opfunc_t) { &cpu_op_aa, 1, 4, 0 };
    optable[0xAB] = (opfunc_t) { &cpu_op_ab, 1, 4, 0 };
    optable[0xAC] = (opfunc_t) { &cpu_op_ac, 1, 4, 0 };
    optable[0xAD] = (opfunc_t) { &cpu_op_ad, 1, 4, 0 };
    optable[0xAE] = (opfunc_t) { &cpu_op_ae, 2, 8, 0 };
    optable[0xAF] = (opfunc_t) { &cpu_op_af, 1, 4, 0 };

    optable[0xB0] = (opfunc_t) { &cpu_op_b0, 1, 4, 0 };
    optable[0xB1] = (opfunc_t) { &cpu_op_b1, 1, 4, 0 };
    optable[0xB2] = (opfunc_t) { &cpu_op_b2, 1, 4, 0 };
    optable[0xB3] = (opfunc_t) { &cpu_op_b3, 1, 4, 0 };
    optable[0xB4] = (opfunc_t) { &cpu_op_b4, 1, 4, 0 };
    optable[0xB5] = (opfunc_t) { &cpu_op_b5, 1, 4, 0 };
    optable[0xB6] = (opfunc_t) { &cpu_op_b6, 2, 8, 0 };
    optable[0xB7] = (opfunc_t) { &cpu_op_b7, 1, 4, 0 };
    optable[0xB8] = (opfunc_t) { &cpu_op_b8, 1, 4, 0 };
    optable[0xB9] = (opfunc_t) { &cpu_op_b9, 1, 4, 0 };
    optable[0xBA] = (opfunc_t) { &cpu_op_ba, 1, 4, 0 };
    optable[0xBB] = (opfunc_t) { &cpu_op_bb, 1, 4, 0 };
    optable[0xBC] = (opfunc_t) { &cpu_op_bc, 1, 4, 0 };
    optable[0xBD] = (opfunc_t) { &cpu_op_bd, 1, 4, 0 };
    optable[0xBE] = (opfunc_t) { &cpu_op_be, 1, 8, 0 };
    optable[0xBF] = (opfunc_t) { &cpu_op_bf, 1, 4, 0 };

    optable[0xC0] = (opfunc_t) { &cpu_op_c0, 2, 8, 0 };
    optable[0xC1] = (opfunc_t) { &cpu_op_c1, 1, 12, 0 };
    optable[0xC2] = (opfunc_t) { &cpu_op_c2, 3, 12, 2 };
    optable[0xC3] = (opfunc_t) { &cpu_op_c3, 3, 12, 2 };
    optable[0xC5] = (opfunc_t) { &cpu_op_c5, 1, 16, 0 };
    optable[0xC6] = (opfunc_t) { &cpu_op_c6, 2, 8, 1 };
    optable[0xC7] = (opfunc_t) { &cpu_op_c7, 4, 16, 0 };
    optable[0xC8] = (opfunc_t) { &cpu_op_c8, 2, 8, 0 };
    optable[0xC9] = (opfunc_t) { &cpu_op_c9, 1, 16, 0 };
    optable[0xCA] = (opfunc_t) { &cpu_op_ca, 3, 12, 2 };
    optable[0xCD] = (opfunc_t) { &cpu_op_cd, 3, 24, 0 };
    optable[0xCF] = (opfunc_t) { &cpu_op_cf, 4, 16, 0 };

    optable[0xD0] = (opfunc_t) { &cpu_op_d0, 2, 8, 0 };
    optable[0xD1] = (opfunc_t) { &cpu_op_d1, 1, 12, 0 };
    optable[0xD2] = (opfunc_t) { &cpu_op_d2, 3, 12, 2 };
    optable[0xD5] = (opfunc_t) { &cpu_op_d5, 1, 16, 0 };
    optable[0xD7] = (opfunc_t) { &cpu_op_d7, 4, 16, 0 };
    optable[0xD8] = (opfunc_t) { &cpu_op_d8, 2, 8, 0 };
    optable[0xD9] = (opfunc_t) { &cpu_op_d9, 4, 16, 0 };
    optable[0xDA] = (opfunc_t) { &cpu_op_da, 3, 12, 2 };
    optable[0xDF] = (opfunc_t) { &cpu_op_df, 4, 16, 0 };

    optable[0xE0] = (opfunc_t) { &cpu_op_e0, 2, 12, 1 };
    optable[0xE1] = (opfunc_t) { &cpu_op_e1, 1, 12, 0 };
    optable[0xE2] = (opfunc_t) { &cpu_op_e2, 2, 8, 0 };
    optable[0xE5] = (opfunc_t) { &cpu_op_e5, 1, 16, 0 };
    optable[0xE6] = (opfunc_t) { &cpu_op_e6, 2, 8, 1 };
    optable[0xE7] = (opfunc_t) { &cpu_op_e7, 4, 16, 0 };
    optable[0xE8] = (opfunc_t) { &cpu_op_e8, 2, 16, 1 };
    optable[0xE9] = (opfunc_t) { &cpu_op_e9, 0, 0, 0 }; // ZEROES because JP already fill 4t when condition is met
    optable[0xEA] = (opfunc_t) { &cpu_op_ea, 3, 16, 2 };
    optable[0xEF] = (opfunc_t) { &cpu_op_ef, 4, 16, 0 };

    optable[0xF0] = (opfunc_t) { &cpu_op_f0, 2, 12, 1 };
    optable[0xF1] = (opfunc_t) { &cpu_op_f1, 1, 12, 0 };
    optable[0xF2] = (opfunc_t) { &cpu_op_f2, 2, 8, 0 };
    optable[0xF3] = (opfunc_t) { &cpu_op_f3, 1, 4, 0 };
    optable[0xF5] = (opfunc_t) { &cpu_op_f5, 1, 16, 0 };
    optable[0xF7] = (opfunc_t) { &cpu_op_f7, 4, 16, 0 };
    optable[0xFA] = (opfunc_t) { &cpu_op_fa, 3, 16, 2 };
    optable[0xFB] = (opfunc_t) { &cpu_op_fb, 1, 4, 0 };
    optable[0xFE] = (opfunc_t) { &cpu_op_fe, 2, 8, 1 };
    optable[0xFF] = (opfunc_t) { &cpu_op_ff, 4, 16, 0 };

    _cpu_init_table_cb();
    optable[0xCB] = (opfunc_t) { &cpu_op_cb, 0, 0, 0 };
}

void _cpu_init_table_cb()
{
    optable_cb[0x00] = (opfunc_t) { &cpu_op_cb_00, 2, 8, 0 };
    optable_cb[0x01] = (opfunc_t) { &cpu_op_cb_01, 2, 8, 0 };
    optable_cb[0x02] = (opfunc_t) { &cpu_op_cb_02, 2, 8, 0 };
    optable_cb[0x03] = (opfunc_t) { &cpu_op_cb_03, 2, 8, 0 };
    optable_cb[0x04] = (opfunc_t) { &cpu_op_cb_04, 2, 8, 0 };
    optable_cb[0x05] = (opfunc_t) { &cpu_op_cb_05, 2, 8, 0 };
    optable_cb[0x06] = (opfunc_t) { &cpu_op_cb_06, 4, 16, 0 };
    optable_cb[0x07] = (opfunc_t) { &cpu_op_cb_07, 2, 8, 0 };
    optable_cb[0x08] = (opfunc_t) { &cpu_op_cb_08, 2, 8, 0 };
    optable_cb[0x09] = (opfunc_t) { &cpu_op_cb_09, 2, 8, 0 };
    optable_cb[0x0a] = (opfunc_t) { &cpu_op_cb_0a, 2, 8, 0 };
    optable_cb[0x0b] = (opfunc_t) { &cpu_op_cb_0b, 2, 8, 0 };
    optable_cb[0x0c] = (opfunc_t) { &cpu_op_cb_0c, 2, 8, 0 };
    optable_cb[0x0d] = (opfunc_t) { &cpu_op_cb_0d, 2, 8, 0 };
    optable_cb[0x0e] = (opfunc_t) { &cpu_op_cb_0e, 4, 16, 0 };
    optable_cb[0x0f] = (opfunc_t) { &cpu_op_cb_0f, 2, 8, 0 };

    optable_cb[0x10] = (opfunc_t) { &cpu_op_cb_10, 2, 8, 0 };
    optable_cb[0x11] = (opfunc_t) { &cpu_op_cb_11, 2, 8, 0 };
    optable_cb[0x12] = (opfunc_t) { &cpu_op_cb_12, 2, 8, 0 };
    optable_cb[0x13] = (opfunc_t) { &cpu_op_cb_13, 2, 8, 0 };
    optable_cb[0x14] = (opfunc_t) { &cpu_op_cb_14, 2, 8, 0 };
    optable_cb[0x15] = (opfunc_t) { &cpu_op_cb_15, 2, 8, 0 };
    optable_cb[0x16] = (opfunc_t) { &cpu_op_cb_16, 4, 16, 0 };
    optable_cb[0x17] = (opfunc_t) { &cpu_op_cb_17, 2, 8, 0 };
    optable_cb[0x18] = (opfunc_t) { &cpu_op_cb_18, 2, 8, 0 };
    optable_cb[0x19] = (opfunc_t) { &cpu_op_cb_19, 2, 8, 0 };
    optable_cb[0x1A] = (opfunc_t) { &cpu_op_cb_1a, 2, 8, 0 };
    optable_cb[0x1B] = (opfunc_t) { &cpu_op_cb_1b, 2, 8, 0 };
    optable_cb[0x1C] = (opfunc_t) { &cpu_op_cb_1c, 2, 8, 0 };
    optable_cb[0x1D] = (opfunc_t) { &cpu_op_cb_1d, 2, 8, 0 };
    optable_cb[0x1E] = (opfunc_t) { &cpu_op_cb_1e, 2, 16, 0 };
    optable_cb[0x1F] = (opfunc_t) { &cpu_op_cb_1f, 2, 8, 0 };

    optable_cb[0x20] = (opfunc_t) { &cpu_op_cb_20, 2, 8, 0 };
    optable_cb[0x21] = (opfunc_t) { &cpu_op_cb_21, 2, 8, 0 };
    optable_cb[0x22] = (opfunc_t) { &cpu_op_cb_22, 2, 8, 0 };
    optable_cb[0x23] = (opfunc_t) { &cpu_op_cb_23, 2, 8, 0 };
    optable_cb[0x24] = (opfunc_t) { &cpu_op_cb_24, 2, 8, 0 };
    optable_cb[0x25] = (opfunc_t) { &cpu_op_cb_25, 2, 8, 0 };
    optable_cb[0x26] = (opfunc_t) { &cpu_op_cb_26, 4, 16, 0 };
    optable_cb[0x27] = (opfunc_t) { &cpu_op_cb_27, 2, 8, 0 };
    optable_cb[0x28] = (opfunc_t) { &cpu_op_cb_28, 2, 8, 0 };
    optable_cb[0x29] = (opfunc_t) { &cpu_op_cb_29, 2, 8, 0 };
    optable_cb[0x2A] = (opfunc_t) { &cpu_op_cb_2a, 2, 8, 0 };
    optable_cb[0x2B] = (opfunc_t) { &cpu_op_cb_2b, 2, 8, 0 };
    optable_cb[0x2C] = (opfunc_t) { &cpu_op_cb_2c, 2, 8, 0 };
    optable_cb[0x2D] = (opfunc_t) { &cpu_op_cb_2d, 2, 8, 0 };
    optable_cb[0x2E] = (opfunc_t) { &cpu_op_cb_2e, 2, 16, 0 };
    optable_cb[0x2F] = (opfunc_t) { &cpu_op_cb_2f, 2, 8, 0 };

    optable_cb[0x30] = (opfunc_t) { &cpu_op_cb_30, 2, 8, 0 };
    optable_cb[0x31] = (opfunc_t) { &cpu_op_cb_31, 2, 8, 0 };
    optable_cb[0x32] = (opfunc_t) { &cpu_op_cb_32, 2, 8, 0 };
    optable_cb[0x33] = (opfunc_t) { &cpu_op_cb_33, 2, 8, 0 };
    optable_cb[0x34] = (opfunc_t) { &cpu_op_cb_34, 2, 8, 0 };
    optable_cb[0x35] = (opfunc_t) { &cpu_op_cb_35, 2, 8, 0 };
    optable_cb[0x36] = (opfunc_t) { &cpu_op_cb_36, 4, 16, 0 };
    optable_cb[0x37] = (opfunc_t) { &cpu_op_cb_37, 2, 8, 0 };
    optable_cb[0x38] = (opfunc_t) { &cpu_op_cb_38, 2, 8, 0 };
    optable_cb[0x39] = (opfunc_t) { &cpu_op_cb_39, 2, 8, 0 };
    optable_cb[0x3A] = (opfunc_t) { &cpu_op_cb_3a, 2, 8, 0 };
    optable_cb[0x3B] = (opfunc_t) { &cpu_op_cb_3b, 2, 8, 0 };
    optable_cb[0x3C] = (opfunc_t) { &cpu_op_cb_3c, 2, 8, 0 };
    optable_cb[0x3D] = (opfunc_t) { &cpu_op_cb_3d, 2, 8, 0 };
    optable_cb[0x3E] = (opfunc_t) { &cpu_op_cb_3e, 2, 16, 0 };
    optable_cb[0x3F] = (opfunc_t) { &cpu_op_cb_3f, 2, 8, 0 };

    optable_cb[0x7C] = (opfunc_t) { &cpu_op_cb_7c, 2, 8, 0 };
}

// OPs implementation

void cpu_op_00(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "NOP");
}

void cpu_op_01(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD BC, $%04x", word);
    cpu->reg.bc.word = word;
}

void cpu_op_02(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (BC), A");
    mmu_write_byte(mmu, cpu->reg.bc.word, cpu->reg.af.hi);
}

void cpu_op_03(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC BC");
    cpu->reg.bc.word++;
}

void cpu_op_04(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC B");
    cpu_ins_inc8(cpu, &cpu->reg.bc.hi);
}

void cpu_op_05(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC B");
    cpu_ins_dec8(cpu, &cpu->reg.bc.hi);
}

void cpu_op_0c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC C");
    cpu_ins_inc8(cpu, &cpu->reg.bc.lo);
}

void cpu_op_06(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD B, $%02X", byte);
    cpu->reg.bc.hi = byte;
}

void cpu_op_07(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLCA");
    cpu_ins_rlc(cpu, &cpu->reg.af.hi);
    cpu_flag_set_zero(cpu, false);
}

void cpu_op_08(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD ($%02X), SP");
    mmu_write_word(mmu, addr, cpu->reg.sp.word);
}

void cpu_op_09(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "ADD HL, BC");
    cpu_ins_add16(cpu, &cpu->reg.hl.word, cpu->reg.bc.word, false);
}

void cpu_op_0b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC BC");
    cpu->reg.bc.word--;
}

void cpu_op_0a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (BC)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.bc.word);
}

void cpu_op_0d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC C");
    cpu_ins_dec8(cpu, &cpu->reg.bc.lo);
}

void cpu_op_0e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD C, $%02X", byte);
    cpu->reg.bc.lo = byte;
}

void cpu_op_0f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRCA");
    cpu_ins_rrc(cpu, &cpu->reg.af.hi);
    cpu_flag_set_zero(cpu, false);
}


void cpu_op_11(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD DE, $%04x", word);
    cpu->reg.de.word = word;
}

void cpu_op_12(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (DE), A");
    mmu_write_byte(mmu, cpu->reg.de.word, cpu->reg.af.hi);
}

void cpu_op_13(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC DE");
    cpu->reg.de.word++;
}

void cpu_op_14(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC D");
    cpu_ins_inc8(cpu, &cpu->reg.de.hi);
}

void cpu_op_15(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC D");
    cpu_ins_dec8(cpu, &cpu->reg.de.hi);
}

void cpu_op_16(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD D, $%02X", byte);
    cpu->reg.de.hi = byte;
}

void cpu_op_17(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLA");
    cpu_ins_rl(cpu, &cpu->reg.af.hi);
    cpu_flag_set_zero(cpu, false);
}

void cpu_op_18(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR $%02x", (uint8_t)offset);
    cpu->reg.pc.word += offset;
}

void cpu_op_19(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD HL, DE");
    cpu_ins_add16(cpu, &cpu->reg.hl.word, cpu->reg.de.word, false);
}

void cpu_op_1a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (DE)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.de.word);
}

void cpu_op_1b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC DE");
    cpu->reg.de.word--;
}

void cpu_op_1c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC E");
    cpu_ins_inc8(cpu, &cpu->reg.de.lo);
}

void cpu_op_1d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC E");
    cpu_ins_dec8(cpu, &cpu->reg.de.lo);
}

void cpu_op_1e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD E, $%02X", byte);
    cpu->reg.de.lo = byte;
}

void cpu_op_1f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRA");
    cpu_ins_rr(cpu, &cpu->reg.af.hi);
    cpu_flag_set_zero(cpu, false);
}

void cpu_op_20(cpu_t* cpu, mmu_t* mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR NZ, $%2X", (uint8_t)offset);
    cpu_ins_jr(cpu, offset, CPU_CONDITION_NZ);
}

void cpu_op_21(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD HL, $%04X", word);
    cpu->reg.hl.word = word;
}

void cpu_op_22(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL+), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word++;
}

void cpu_op_23(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC HL");
    cpu->reg.hl.word++;
}

void cpu_op_24(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC H");
    cpu_ins_inc8(cpu, &cpu->reg.hl.hi);
}

void cpu_op_25(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC H");
    cpu_ins_dec8(cpu, &cpu->reg.hl.hi);
}

void cpu_op_26(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD H, $%02X", byte);
    cpu->reg.hl.hi = byte;
}

void cpu_op_27(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DAA");
    uint8_t a = cpu->reg.af.hi;

    if (cpu_flag(cpu, CPU_FLAG_SUB_BIT))
    {
        if (cpu_flag(cpu, CPU_FLAG_HC_BIT))
            a = (a - 0x06) & 0xFF;
        if (cpu_flag(cpu, CPU_FLAG_CARRY_BIT))
            a -= 0x60;
    }
    else
    {
        if (cpu_flag(cpu, CPU_FLAG_HC_BIT) || (a & 0xF) > 9)
            a += 0x06;
        if (cpu_flag(cpu, CPU_FLAG_CARRY_BIT) || a > 0x9F)
            a += 0x60;
    }

    cpu->reg.af.hi = a;

    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_zero(cpu, a == 0);
    cpu_flag_set_carry(cpu, a >= 0x100);
}

void cpu_op_28(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR Z, $%2X", (uint8_t)offset);
    cpu_ins_jr(cpu, offset, CPU_CONDITION_Z);
}

void cpu_op_29(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD HL, HL");
    cpu_ins_add16(cpu, &cpu->reg.hl.word, cpu->reg.hl.word, false);
}

void cpu_op_2a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL+)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.word++;
}

void cpu_op_2b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC HL");
    cpu->reg.hl.word--;
}

void cpu_op_2c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC L");
    cpu_ins_inc8(cpu, &cpu->reg.hl.lo);
}

void cpu_op_2d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC L");
    cpu_ins_dec8(cpu, &cpu->reg.hl.lo);
}

void cpu_op_2e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD L, $%02X", byte);
    cpu->reg.hl.lo = byte;
}

void cpu_op_2f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CPL");
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu->reg.af.hi = ~cpu->reg.af.hi;
}

void cpu_op_30(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR NC, $%2X", (uint8_t)offset);
    cpu_ins_jr(cpu, offset, CPU_CONDITION_NC);
}

void cpu_op_31(cpu_t* cpu, mmu_t* mmu)
{
    uint16_t word = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD SP, $%04X", word);

    cpu->reg.sp.word = word;
}

void cpu_op_32(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "LD (HL-), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
    cpu->reg.hl.word--;
}

void cpu_op_33(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC SP");
    cpu->reg.sp.word++;
}

void cpu_op_34(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_inc8(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_35(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_dec8(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_36(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD (HL), $%02X", byte);
    mmu_write_byte(mmu, cpu->reg.hl.word, byte);
}

void cpu_op_37(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SCF");
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_carry(cpu, true);
}

void cpu_op_38(cpu_t * cpu, mmu_t * mmu)
{
    int8_t offset = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JR C, $%2X", (uint8_t)offset);
    cpu_ins_jr(cpu, offset, CPU_CONDITION_C);
}

void cpu_op_39(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD HL, SP");
    cpu_ins_add16(cpu, &cpu->reg.hl.word, cpu->reg.sp.word, false);
}

void cpu_op_3a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL-)");
    cpu->reg.af.hi = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.word--;
}

void cpu_op_3b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC SP");
    cpu->reg.sp.word--;
}

void cpu_op_3c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "INC A");
    cpu_ins_inc8(cpu, &cpu->reg.af.hi);
}

void cpu_op_3d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DEC A");
    cpu_ins_dec8(cpu, &cpu->reg.af.hi);
}

void cpu_op_3e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, $%02X", byte);
    cpu->reg.af.hi = byte;
}

void cpu_op_3f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CCF");
    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_halfcarry(cpu, false);
    cpu_flag_set_carry(cpu, !cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}


void cpu_op_40(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, B");
    cpu->reg.bc.hi = cpu->reg.bc.hi;
}

void cpu_op_41(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, C");
    cpu->reg.bc.hi = cpu->reg.bc.lo;
}

void cpu_op_42(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, D");
    cpu->reg.bc.hi = cpu->reg.de.hi;
}

void cpu_op_43(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, E");
    cpu->reg.bc.hi = cpu->reg.de.lo;
}

void cpu_op_44(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, H");
    cpu->reg.bc.hi = cpu->reg.hl.hi;
}

void cpu_op_45(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, L");
    cpu->reg.bc.hi = cpu->reg.hl.lo;
}

void cpu_op_46(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.bc.hi = byte;
}

void cpu_op_47(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD B, A");
    cpu->reg.bc.hi = cpu->reg.af.hi;
}

void cpu_op_48(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, B");
    cpu->reg.bc.lo = cpu->reg.bc.hi;
}

void cpu_op_49(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, C");
    cpu->reg.bc.lo = cpu->reg.bc.lo;
}

void cpu_op_4a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, D");
    cpu->reg.bc.lo = cpu->reg.de.hi;
}

void cpu_op_4b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, E");
    cpu->reg.bc.lo = cpu->reg.de.lo;
}

void cpu_op_4c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, H");
    cpu->reg.bc.lo = cpu->reg.hl.hi;
}

void cpu_op_4d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, L");
    cpu->reg.bc.lo = cpu->reg.hl.lo;
}

void cpu_op_4e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.bc.lo = byte;
}

void cpu_op_4f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD C, A");
    cpu->reg.bc.lo = cpu->reg.af.hi;
}



void cpu_op_50(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, B");
    cpu->reg.de.hi = cpu->reg.bc.hi;
}

void cpu_op_51(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, C");
    cpu->reg.de.hi = cpu->reg.bc.lo;
}

void cpu_op_52(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, D");
    cpu->reg.de.hi = cpu->reg.de.hi;
}

void cpu_op_53(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, E");
    cpu->reg.de.hi = cpu->reg.de.lo;
}

void cpu_op_54(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, H");
    cpu->reg.de.hi = cpu->reg.hl.hi;
}

void cpu_op_55(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, L");
    cpu->reg.de.hi = cpu->reg.hl.lo;
}

void cpu_op_56(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.de.hi = byte;
}

void cpu_op_57(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD D, A");
    cpu->reg.de.hi = cpu->reg.af.hi;
}

void cpu_op_58(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, B");
    cpu->reg.de.lo = cpu->reg.bc.hi;
}

void cpu_op_59(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, C");
    cpu->reg.de.lo = cpu->reg.bc.lo;
}

void cpu_op_5a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, D");
    cpu->reg.de.lo = cpu->reg.de.hi;
}

void cpu_op_5b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, E");
    cpu->reg.de.lo = cpu->reg.de.lo;
}

void cpu_op_5c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, H");
    cpu->reg.de.lo = cpu->reg.hl.hi;
}

void cpu_op_5d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, L");
    cpu->reg.de.lo = cpu->reg.hl.lo;
}

void cpu_op_5e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.de.lo = byte;
}

void cpu_op_5f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD E, A");
    cpu->reg.de.lo = cpu->reg.af.hi;
}



void cpu_op_60(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, B");
    cpu->reg.hl.hi = cpu->reg.bc.hi;
}

void cpu_op_61(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, C");
    cpu->reg.hl.hi = cpu->reg.bc.lo;
}

void cpu_op_62(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, D");
    cpu->reg.hl.hi = cpu->reg.de.hi;
}

void cpu_op_63(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, E");
    cpu->reg.hl.hi = cpu->reg.de.lo;
}

void cpu_op_64(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, H");
    cpu->reg.hl.hi = cpu->reg.hl.hi;
}

void cpu_op_65(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, L");
    cpu->reg.hl.hi = cpu->reg.hl.lo;
}

void cpu_op_66(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.hi = byte;
}

void cpu_op_67(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD H, A");
    cpu->reg.hl.hi = cpu->reg.af.hi;
}

void cpu_op_68(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, B");
    cpu->reg.hl.lo = cpu->reg.bc.hi;
}

void cpu_op_69(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, C");
    cpu->reg.hl.lo = cpu->reg.bc.lo;
}

void cpu_op_6a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, D");
    cpu->reg.hl.lo = cpu->reg.de.hi;
}

void cpu_op_6b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, E");
    cpu->reg.hl.lo = cpu->reg.de.lo;
}

void cpu_op_6c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, H");
    cpu->reg.hl.lo = cpu->reg.hl.hi;
}

void cpu_op_6d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, L");
    cpu->reg.hl.lo = cpu->reg.hl.lo;
}

void cpu_op_6e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.hl.lo = byte;
}

void cpu_op_6f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD L, A");
    cpu->reg.hl.lo = cpu->reg.af.hi;
}



void cpu_op_70(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), B");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.bc.hi);
}

void cpu_op_71(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), C");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.bc.lo);
}

void cpu_op_72(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), D");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.de.hi);
}

void cpu_op_73(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), E");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.de.lo);
}

void cpu_op_74(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), H");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.hl.hi);
}

void cpu_op_75(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), L");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.hl.lo);
}

void cpu_op_77(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD (HL), A");
    mmu_write_byte(mmu, cpu->reg.hl.word, cpu->reg.af.hi);
}

void cpu_op_78(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, B");
    cpu->reg.af.hi = cpu->reg.bc.hi;
}

void cpu_op_79(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, C");
    cpu->reg.af.hi = cpu->reg.bc.lo;
}

void cpu_op_7a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, D");
    cpu->reg.af.hi = cpu->reg.de.hi;
}

void cpu_op_7b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, E");
    cpu->reg.af.hi = cpu->reg.de.lo;
}

void cpu_op_7c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, H");
    cpu->reg.af.hi = cpu->reg.hl.hi;
}

void cpu_op_7d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, L");
    cpu->reg.af.hi = cpu->reg.hl.lo;
}

void cpu_op_7e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, (HL)");
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu->reg.af.hi = byte;
}

void cpu_op_7f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, A");
    cpu->reg.af.hi = cpu->reg.af.hi;
}

void cpu_op_80(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, B");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.bc.hi);
}

void cpu_op_81(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, C");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.bc.lo);
}

void cpu_op_82(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, D");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.de.hi);
}

void cpu_op_83(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, E");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.de.lo);
}

void cpu_op_84(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, H");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.hl.hi);
}

void cpu_op_85(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, L");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.hl.lo);
}

void cpu_op_86(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "ADD A, (HL)");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, value);
}

void cpu_op_87(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADD A, A");
    cpu_ins_add8(cpu, &cpu->reg.af.hi, cpu->reg.af.hi);
}

void cpu_op_88(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, B");
    cpu_ins_adc(cpu, cpu->reg.bc.hi);
}

void cpu_op_89(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, C");
    cpu_ins_adc(cpu, cpu->reg.bc.lo);
}

void cpu_op_8a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, D");
    cpu_ins_adc(cpu, cpu->reg.de.hi);
}

void cpu_op_8b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, E");
    cpu_ins_adc(cpu, cpu->reg.de.lo);
}

void cpu_op_8c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, H");
    cpu_ins_adc(cpu, cpu->reg.hl.hi);
}

void cpu_op_8d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, L");
    cpu_ins_adc(cpu, cpu->reg.hl.lo);
}

void cpu_op_8e(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "ADC A, (HL)");
    cpu_ins_adc(cpu, byte);
}

void cpu_op_8f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "ADC A, A");
    cpu_ins_adc(cpu, cpu->reg.af.hi);
}

void cpu_op_90(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB B");
    cpu_ins_sub8(cpu, cpu->reg.bc.hi);
}

void cpu_op_91(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB C");
    cpu_ins_sub8(cpu, cpu->reg.bc.lo);
}

void cpu_op_92(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB D");
    cpu_ins_sub8(cpu, cpu->reg.de.hi);
}

void cpu_op_93(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB E");
    cpu_ins_sub8(cpu, cpu->reg.de.lo);
}

void cpu_op_94(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB H");
    cpu_ins_sub8(cpu, cpu->reg.hl.hi);
}

void cpu_op_95(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB L");
    cpu_ins_sub8(cpu, cpu->reg.hl.lo);
}

void cpu_op_96(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB (HL)");
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sub8(cpu, value);
}

void cpu_op_97(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SUB A");
    cpu_ins_sub8(cpu, cpu->reg.af.hi);
}

void cpu_op_98(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, B");
    cpu_ins_sub8(cpu, cpu->reg.bc.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_99(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, C");
    cpu_ins_sub8(cpu, cpu->reg.bc.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, D");
    cpu_ins_sub8(cpu, cpu->reg.de.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, E");
    cpu_ins_sub8(cpu, cpu->reg.de.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, H");
    cpu_ins_sub8(cpu, cpu->reg.hl.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, L");
    cpu_ins_sub8(cpu, cpu->reg.hl.lo + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, (HL)");
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sub8(cpu, value + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_9f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SBC A, A");
    cpu_ins_sub8(cpu, cpu->reg.af.hi + cpu_flag(cpu, CPU_FLAG_CARRY_BIT));
}

void cpu_op_a0(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND B");
    cpu_ins_and(cpu, cpu->reg.bc.hi);
}

void cpu_op_a1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND C");
    cpu_ins_and(cpu, cpu->reg.bc.lo);
}

void cpu_op_a2(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND D");
    cpu_ins_and(cpu, cpu->reg.de.hi);
}

void cpu_op_a3(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND E");
    cpu_ins_and(cpu, cpu->reg.de.lo);
}

void cpu_op_a4(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND H");
    cpu_ins_and(cpu, cpu->reg.hl.hi);
}

void cpu_op_a5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND L");
    cpu_ins_and(cpu, cpu->reg.hl.lo);
}

void cpu_op_a6(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "AND (HL)");
    cpu_ins_and(cpu, value);
}

void cpu_op_a7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "AND A");
    cpu_ins_and(cpu, cpu->reg.af.hi);
}

void cpu_op_a8(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR B");
    cpu_ins_xor(cpu, cpu->reg.bc.hi);
}

void cpu_op_a9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR C");
    cpu_ins_xor(cpu, cpu->reg.bc.lo);
}

void cpu_op_aa(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR D");
    cpu_ins_xor(cpu, cpu->reg.de.hi);
}

void cpu_op_ab(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR E");
    cpu_ins_xor(cpu, cpu->reg.de.lo);
}

void cpu_op_ac(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR H");
    cpu_ins_xor(cpu, cpu->reg.hl.hi);
}

void cpu_op_ad(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "XOR L");
    cpu_ins_xor(cpu, cpu->reg.hl.lo);
}

void cpu_op_ae(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "XOR (HL)");
    cpu_ins_xor(cpu, value);
}

void cpu_op_af(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "XOR A");
    cpu_ins_xor(cpu, cpu->reg.af.hi);
}

void cpu_op_b0(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR B");
    cpu_ins_or(cpu, cpu->reg.bc.hi);
}

void cpu_op_b1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR C");
    cpu_ins_or(cpu, cpu->reg.bc.lo);
}

void cpu_op_b2(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR D");
    cpu_ins_or(cpu, cpu->reg.de.hi);
}

void cpu_op_b3(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR E");
    cpu_ins_or(cpu, cpu->reg.de.lo);
}

void cpu_op_b4(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR H");
    cpu_ins_or(cpu, cpu->reg.hl.hi);
}

void cpu_op_b5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR L");
    cpu_ins_or(cpu, cpu->reg.hl.lo);
}

void cpu_op_b6(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "OR (HL)");
    cpu_ins_or(cpu, value);
}

void cpu_op_b7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "OR A");
    cpu_ins_or(cpu, cpu->reg.af.hi);
}

void cpu_op_b8(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP B");
    cpu_ins_cp(cpu, cpu->reg.bc.hi);
}

void cpu_op_b9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP C");
    cpu_ins_cp(cpu, cpu->reg.bc.lo);
}

void cpu_op_ba(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP D");
    cpu_ins_cp(cpu, cpu->reg.de.hi);
}

void cpu_op_bb(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP E");
    cpu_ins_cp(cpu, cpu->reg.de.lo);
}

void cpu_op_bc(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP H");
    cpu_ins_cp(cpu, cpu->reg.hl.hi);
}

void cpu_op_bd(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP L");
    cpu_ins_cp(cpu, cpu->reg.hl.lo);
}

void cpu_op_be(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.hl.word);
    debug_instruction(cpu, mmu, "CP (HL)");
    cpu_ins_cp(cpu, value);
}

void cpu_op_bf(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "CP A");
    cpu_ins_cp(cpu, cpu->reg.af.hi);
}

void cpu_op_c0(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET NZ");
    cpu_ins_ret_condition(cpu, mmu, CPU_CONDITION_NZ);
}

void cpu_op_c1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP BC");
    cpu->reg.bc.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_c2(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JP NZ, $%04x", addr);
    cpu_ins_jp(cpu, addr, CPU_CONDITION_NZ);
}

void cpu_op_c3(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JP $%04x", addr);
    cpu_ins_jp(cpu, addr, CPU_CONDITION_ALWAYS);
}

void cpu_op_c5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH BC");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.bc.word);
}

void cpu_op_c6(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "ADD A, $%02x", value);
    cpu_ins_add8(cpu, &cpu->reg.af.hi, value);
}

void cpu_op_c7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 00h");
    cpu_ins_call(cpu, mmu, 0x0000, 1);
}

void cpu_op_c8(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET Z");
    cpu_ins_ret_condition(cpu, mmu, CPU_CONDITION_Z);
}

void cpu_op_c9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET");
    cpu_ins_ret(cpu, mmu);
}

void cpu_op_ca(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JP Z, $%04x", addr);
    cpu_ins_jp(cpu, addr, CPU_CONDITION_Z);
}

void cpu_op_cd(cpu_t* cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "CALL $%04x", addr);

    cpu_ins_call(cpu, mmu, addr, 2);
}

void cpu_op_cf(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 08h");
    cpu_ins_call(cpu, mmu, 0x0008, 0);
}

void cpu_op_d0(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET NC");
    cpu_ins_ret_condition(cpu, mmu, CPU_CONDITION_NC);
}

void cpu_op_d1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP DE");
    cpu->reg.de.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_d2(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JP NC, $%04x", addr);
    cpu_ins_jp(cpu, addr, CPU_CONDITION_NC);
}

void cpu_op_d5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH DE");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.de.word);
}

void cpu_op_d7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 10h");
    cpu_ins_call(cpu, mmu, 0x0010, 0);
}

void cpu_op_d8(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RET C");
    cpu_ins_ret_condition(cpu, mmu, CPU_CONDITION_C);
}

void cpu_op_d9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RETI");
    cpu_ins_ret(cpu, mmu);
    cpu->ime = true;
}

void cpu_op_da(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "JP C, $%04x", addr);
    cpu_ins_jp(cpu, addr, CPU_CONDITION_C);
}

void cpu_op_df(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 18h");
    cpu_ins_call(cpu, mmu, 0x0018, 0);
}

void cpu_op_e0(cpu_t* cpu, mmu_t* mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD ($FF00+$%02x), A", byte);
    uint16_t addr = 0xFF00 + byte;
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_e1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP HL");
    cpu->reg.hl.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_e2(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "LD ($FF00+C), A");
    uint16_t addr = 0xFF00 + cpu->reg.bc.lo;
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_e5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH HL");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.hl.word);
}

void cpu_op_e6(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t value = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "AND $%02X", value);
    cpu_ins_and(cpu, value);
}

void cpu_op_e7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 20h");
    cpu_ins_call(cpu, mmu, 0x0020, 0);
}

void cpu_op_e8(cpu_t * cpu, mmu_t * mmu)
{
    int8_t value = (int8_t)mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "ADD SP, $%02x", value);

    cpu_flag_set_sub(cpu, false);
    cpu_flag_set_zero(cpu, false);

    cpu_flag_set_carry(cpu, ((cpu->reg.sp.word) + value) > 0xFFFF);
    cpu_flag_set_halfcarry(cpu, ((cpu->reg.sp.word & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);

    cpu->reg.sp.word += value;
}

void cpu_op_e9(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "JP HL");
    cpu_ins_jp(cpu, cpu->reg.hl.word, CPU_CONDITION_ALWAYS);
}

void cpu_op_ea(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD ($%04x), A", addr);
    mmu_write_byte(mmu, addr, cpu->reg.af.hi);
}

void cpu_op_ef(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 28h");
    cpu_ins_call(cpu, mmu, 0x0028, 0);
}

void cpu_op_f0(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t byte = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, ($FF00+$%02x)", byte);
    uint16_t addr = 0xFF00 + byte;
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_f1(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "POP AF");
    cpu->reg.af.word = mmu_read_word(mmu, cpu->reg.sp.word);
    cpu->reg.sp.word += 2;
}

void cpu_op_f2(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "LD A, ($FF00+C)");
    uint16_t addr = 0xFF00 + cpu->reg.bc.lo;
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_f3(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "DI");
    cpu->ime = false;
}

void cpu_op_f5(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "PUSH AF");
    cpu->reg.sp.word -= 2;
    mmu_write_word(mmu, cpu->reg.sp.word, cpu->reg.af.word);
}

void cpu_op_f7(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 30h");
    cpu_ins_call(cpu, mmu, 0x0030, 0);
}

void cpu_op_fa(cpu_t * cpu, mmu_t * mmu)
{
    uint16_t addr = mmu_read_word(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "LD A, ($%04x)", addr);
    cpu->reg.af.hi = mmu_read_byte(mmu, addr);
}

void cpu_op_fb(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "EI");
    cpu->ime = true;
}

void cpu_op_fe(cpu_t * cpu, mmu_t * mmu)
{
    uint8_t v = mmu_read_byte(mmu, cpu->reg.pc.word);
    debug_instruction(cpu, mmu, "CP $%02x", v);
    cpu_ins_cp(cpu, v);
}

void cpu_op_ff(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RST 38h");
    cpu_ins_call(cpu, mmu, 0x0038, 0);
}

void cpu_op_cb_00(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC B");
    cpu_ins_rlc(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_01(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC C");
    cpu_ins_rlc(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_02(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC D");
    cpu_ins_rlc(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_03(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC E");
    cpu_ins_rlc(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_04(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC H");
    cpu_ins_rlc(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_05(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC L");
    cpu_ins_rlc(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_06(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rlc(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_07(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RLC A");
    cpu_ins_rlc(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_08(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC B");
    cpu_ins_rrc(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_09(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC C");
    cpu_ins_rrc(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_0a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC D");
    cpu_ins_rrc(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_0b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC E");
    cpu_ins_rrc(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_0c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC H");
    cpu_ins_rrc(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_0d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC L");
    cpu_ins_rrc(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_0e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rrc(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_0f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RRC A");
    cpu_ins_rrc(cpu, &cpu->reg.af.hi);
}

// CB OP Codes

void cpu_op_cb_10(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL B");
    cpu_ins_rl(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_11(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL C");
    cpu_ins_rl(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_12(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL D");
    cpu_ins_rl(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_13(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL E");
    cpu_ins_rl(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_14(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL H");
    cpu_ins_rl(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_15(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL L");
    cpu_ins_rl(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_16(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rl(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_17(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RL A");
    cpu_ins_rl(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_18(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR B");
    cpu_ins_rr(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_19(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR C");
    cpu_ins_rr(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_1a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR D");
    cpu_ins_rr(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_1b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR E");
    cpu_ins_rr(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_1c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR H");
    cpu_ins_rr(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_1d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR L");
    cpu_ins_rr(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_1e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_rr(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_1f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "RR A");
    cpu_ins_rr(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_20(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA B");
    cpu_ins_sla(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_21(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA C");
    cpu_ins_sla(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_22(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA D");
    cpu_ins_sla(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_23(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA E");
    cpu_ins_sla(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_24(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA H");
    cpu_ins_sla(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_25(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA L");
    cpu_ins_sla(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_26(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sla(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_27(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SLA A");
    cpu_ins_sla(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_28(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA B");
    cpu_ins_sra(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_29(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA C");
    cpu_ins_sra(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_2a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA D");
    cpu_ins_sra(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_2b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA E");
    cpu_ins_sra(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_2c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA H");
    cpu_ins_sra(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_2d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA L");
    cpu_ins_sra(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_2e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_sra(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_2f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRA A");
    cpu_ins_sra(cpu, &cpu->reg.af.hi);
}


void cpu_op_cb_30(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP B");
    cpu_ins_swap(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_31(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP C");
    cpu_ins_swap(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_32(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP D");
    cpu_ins_swap(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_33(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP E");
    cpu_ins_swap(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_34(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP H");
    cpu_ins_swap(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_35(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP L");
    cpu_ins_swap(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_36(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_swap(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_37(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SWAP A");
    cpu_ins_swap(cpu, &cpu->reg.af.hi);
}

void cpu_op_cb_38(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL B");
    cpu_ins_srl(cpu, &cpu->reg.bc.hi);
}

void cpu_op_cb_39(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL C");
    cpu_ins_srl(cpu, &cpu->reg.bc.lo);
}

void cpu_op_cb_3a(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL D");
    cpu_ins_srl(cpu, &cpu->reg.de.hi);
}

void cpu_op_cb_3b(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL E");
    cpu_ins_srl(cpu, &cpu->reg.de.lo);
}

void cpu_op_cb_3c(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL H");
    cpu_ins_srl(cpu, &cpu->reg.hl.hi);
}

void cpu_op_cb_3d(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL L");
    cpu_ins_srl(cpu, &cpu->reg.hl.lo);
}

void cpu_op_cb_3e(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL (HL)");
    uint8_t v = mmu_read_byte(mmu, cpu->reg.hl.word);
    cpu_ins_srl(cpu, &v);
    mmu_write_byte(mmu, cpu->reg.hl.word, v);
}

void cpu_op_cb_3f(cpu_t * cpu, mmu_t * mmu)
{
    debug_instruction(cpu, mmu, "SRL A");
    cpu_ins_srl(cpu, &cpu->reg.af.hi);
}



void cpu_op_cb_7c(cpu_t* cpu, mmu_t* mmu)
{
    debug_instruction(cpu, mmu, "BIT 7, H");
    cpu_ins_bit(cpu, 7, cpu->reg.hl.hi);
}

