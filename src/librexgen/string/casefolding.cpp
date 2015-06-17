#include <librexgen/string/uchar.h>
#include <stdio.h>
bool
casefold_common(uint32_t cp, charset cs, binary_character_t* bch) {
  bch[1].ucs4.value = 0xffffffff;
  bch[2].ucs4.value = 0xffffffff;
  fprintf(stderr, "trying to convert 0x%08x\n", cp);
  switch (cp) {
  case 0x0041:
    encode_codepoint(0x0061, cs, &bch[0]);
    fprintf (stderr, "encoded 'a' to 0x%08x\n", bch[0].ucs4.value);
    return true;
  case 0x0042:
    encode_codepoint(0x0062, cs, &bch[0]);
    return true;
  case 0x0043:
    encode_codepoint(0x0063, cs, &bch[0]);
    return true;
  case 0x0044:
    encode_codepoint(0x0064, cs, &bch[0]);
    return true;
  case 0x0045:
    encode_codepoint(0x0065, cs, &bch[0]);
    return true;
  case 0x0046:
    encode_codepoint(0x0066, cs, &bch[0]);
    return true;
  case 0x0047:
    encode_codepoint(0x0067, cs, &bch[0]);
    return true;
  case 0x0048:
    encode_codepoint(0x0068, cs, &bch[0]);
    return true;
  case 0x0049:
    encode_codepoint(0x0069, cs, &bch[0]);
    return true;
  case 0x004A:
    encode_codepoint(0x006A, cs, &bch[0]);
    return true;
  case 0x004B:
    encode_codepoint(0x006B, cs, &bch[0]);
    return true;
  case 0x004C:
    encode_codepoint(0x006C, cs, &bch[0]);
    return true;
  case 0x004D:
    encode_codepoint(0x006D, cs, &bch[0]);
    return true;
  case 0x004E:
    encode_codepoint(0x006E, cs, &bch[0]);
    return true;
  case 0x004F:
    encode_codepoint(0x006F, cs, &bch[0]);
    return true;
  case 0x0050:
    encode_codepoint(0x0070, cs, &bch[0]);
    return true;
  case 0x0051:
    encode_codepoint(0x0071, cs, &bch[0]);
    return true;
  case 0x0052:
    encode_codepoint(0x0072, cs, &bch[0]);
    return true;
  case 0x0053:
    encode_codepoint(0x0073, cs, &bch[0]);
    return true;
  case 0x0054:
    encode_codepoint(0x0074, cs, &bch[0]);
    return true;
  case 0x0055:
    encode_codepoint(0x0075, cs, &bch[0]);
    return true;
  case 0x0056:
    encode_codepoint(0x0076, cs, &bch[0]);
    return true;
  case 0x0057:
    encode_codepoint(0x0077, cs, &bch[0]);
    return true;
  case 0x0058:
    encode_codepoint(0x0078, cs, &bch[0]);
    return true;
  case 0x0059:
    encode_codepoint(0x0079, cs, &bch[0]);
    return true;
  case 0x005A:
    encode_codepoint(0x007A, cs, &bch[0]);
    return true;
  case 0x00B5:
    encode_codepoint(0x03BC, cs, &bch[0]);
    return true;
  case 0x00C0:
    encode_codepoint(0x00E0, cs, &bch[0]);
    return true;
  case 0x00C1:
    encode_codepoint(0x00E1, cs, &bch[0]);
    return true;
  case 0x00C2:
    encode_codepoint(0x00E2, cs, &bch[0]);
    return true;
  case 0x00C3:
    encode_codepoint(0x00E3, cs, &bch[0]);
    return true;
  case 0x00C4:
    encode_codepoint(0x00E4, cs, &bch[0]);
    return true;
  case 0x00C5:
    encode_codepoint(0x00E5, cs, &bch[0]);
    return true;
  case 0x00C6:
    encode_codepoint(0x00E6, cs, &bch[0]);
    return true;
  case 0x00C7:
    encode_codepoint(0x00E7, cs, &bch[0]);
    return true;
  case 0x00C8:
    encode_codepoint(0x00E8, cs, &bch[0]);
    return true;
  case 0x00C9:
    encode_codepoint(0x00E9, cs, &bch[0]);
    return true;
  case 0x00CA:
    encode_codepoint(0x00EA, cs, &bch[0]);
    return true;
  case 0x00CB:
    encode_codepoint(0x00EB, cs, &bch[0]);
    return true;
  case 0x00CC:
    encode_codepoint(0x00EC, cs, &bch[0]);
    return true;
  case 0x00CD:
    encode_codepoint(0x00ED, cs, &bch[0]);
    return true;
  case 0x00CE:
    encode_codepoint(0x00EE, cs, &bch[0]);
    return true;
  case 0x00CF:
    encode_codepoint(0x00EF, cs, &bch[0]);
    return true;
  case 0x00D0:
    encode_codepoint(0x00F0, cs, &bch[0]);
    return true;
  case 0x00D1:
    encode_codepoint(0x00F1, cs, &bch[0]);
    return true;
  case 0x00D2:
    encode_codepoint(0x00F2, cs, &bch[0]);
    return true;
  case 0x00D3:
    encode_codepoint(0x00F3, cs, &bch[0]);
    return true;
  case 0x00D4:
    encode_codepoint(0x00F4, cs, &bch[0]);
    return true;
  case 0x00D5:
    encode_codepoint(0x00F5, cs, &bch[0]);
    return true;
  case 0x00D6:
    encode_codepoint(0x00F6, cs, &bch[0]);
    return true;
  case 0x00D8:
    encode_codepoint(0x00F8, cs, &bch[0]);
    return true;
  case 0x00D9:
    encode_codepoint(0x00F9, cs, &bch[0]);
    return true;
  case 0x00DA:
    encode_codepoint(0x00FA, cs, &bch[0]);
    return true;
  case 0x00DB:
    encode_codepoint(0x00FB, cs, &bch[0]);
    return true;
  case 0x00DC:
    encode_codepoint(0x00FC, cs, &bch[0]);
    return true;
  case 0x00DD:
    encode_codepoint(0x00FD, cs, &bch[0]);
    return true;
  case 0x00DE:
    encode_codepoint(0x00FE, cs, &bch[0]);
    return true;
  case 0x0100:
    encode_codepoint(0x0101, cs, &bch[0]);
    return true;
  case 0x0102:
    encode_codepoint(0x0103, cs, &bch[0]);
    return true;
  case 0x0104:
    encode_codepoint(0x0105, cs, &bch[0]);
    return true;
  case 0x0106:
    encode_codepoint(0x0107, cs, &bch[0]);
    return true;
  case 0x0108:
    encode_codepoint(0x0109, cs, &bch[0]);
    return true;
  case 0x010A:
    encode_codepoint(0x010B, cs, &bch[0]);
    return true;
  case 0x010C:
    encode_codepoint(0x010D, cs, &bch[0]);
    return true;
  case 0x010E:
    encode_codepoint(0x010F, cs, &bch[0]);
    return true;
  case 0x0110:
    encode_codepoint(0x0111, cs, &bch[0]);
    return true;
  case 0x0112:
    encode_codepoint(0x0113, cs, &bch[0]);
    return true;
  case 0x0114:
    encode_codepoint(0x0115, cs, &bch[0]);
    return true;
  case 0x0116:
    encode_codepoint(0x0117, cs, &bch[0]);
    return true;
  case 0x0118:
    encode_codepoint(0x0119, cs, &bch[0]);
    return true;
  case 0x011A:
    encode_codepoint(0x011B, cs, &bch[0]);
    return true;
  case 0x011C:
    encode_codepoint(0x011D, cs, &bch[0]);
    return true;
  case 0x011E:
    encode_codepoint(0x011F, cs, &bch[0]);
    return true;
  case 0x0120:
    encode_codepoint(0x0121, cs, &bch[0]);
    return true;
  case 0x0122:
    encode_codepoint(0x0123, cs, &bch[0]);
    return true;
  case 0x0124:
    encode_codepoint(0x0125, cs, &bch[0]);
    return true;
  case 0x0126:
    encode_codepoint(0x0127, cs, &bch[0]);
    return true;
  case 0x0128:
    encode_codepoint(0x0129, cs, &bch[0]);
    return true;
  case 0x012A:
    encode_codepoint(0x012B, cs, &bch[0]);
    return true;
  case 0x012C:
    encode_codepoint(0x012D, cs, &bch[0]);
    return true;
  case 0x012E:
    encode_codepoint(0x012F, cs, &bch[0]);
    return true;
  case 0x0132:
    encode_codepoint(0x0133, cs, &bch[0]);
    return true;
  case 0x0134:
    encode_codepoint(0x0135, cs, &bch[0]);
    return true;
  case 0x0136:
    encode_codepoint(0x0137, cs, &bch[0]);
    return true;
  case 0x0139:
    encode_codepoint(0x013A, cs, &bch[0]);
    return true;
  case 0x013B:
    encode_codepoint(0x013C, cs, &bch[0]);
    return true;
  case 0x013D:
    encode_codepoint(0x013E, cs, &bch[0]);
    return true;
  case 0x013F:
    encode_codepoint(0x0140, cs, &bch[0]);
    return true;
  case 0x0141:
    encode_codepoint(0x0142, cs, &bch[0]);
    return true;
  case 0x0143:
    encode_codepoint(0x0144, cs, &bch[0]);
    return true;
  case 0x0145:
    encode_codepoint(0x0146, cs, &bch[0]);
    return true;
  case 0x0147:
    encode_codepoint(0x0148, cs, &bch[0]);
    return true;
  case 0x014A:
    encode_codepoint(0x014B, cs, &bch[0]);
    return true;
  case 0x014C:
    encode_codepoint(0x014D, cs, &bch[0]);
    return true;
  case 0x014E:
    encode_codepoint(0x014F, cs, &bch[0]);
    return true;
  case 0x0150:
    encode_codepoint(0x0151, cs, &bch[0]);
    return true;
  case 0x0152:
    encode_codepoint(0x0153, cs, &bch[0]);
    return true;
  case 0x0154:
    encode_codepoint(0x0155, cs, &bch[0]);
    return true;
  case 0x0156:
    encode_codepoint(0x0157, cs, &bch[0]);
    return true;
  case 0x0158:
    encode_codepoint(0x0159, cs, &bch[0]);
    return true;
  case 0x015A:
    encode_codepoint(0x015B, cs, &bch[0]);
    return true;
  case 0x015C:
    encode_codepoint(0x015D, cs, &bch[0]);
    return true;
  case 0x015E:
    encode_codepoint(0x015F, cs, &bch[0]);
    return true;
  case 0x0160:
    encode_codepoint(0x0161, cs, &bch[0]);
    return true;
  case 0x0162:
    encode_codepoint(0x0163, cs, &bch[0]);
    return true;
  case 0x0164:
    encode_codepoint(0x0165, cs, &bch[0]);
    return true;
  case 0x0166:
    encode_codepoint(0x0167, cs, &bch[0]);
    return true;
  case 0x0168:
    encode_codepoint(0x0169, cs, &bch[0]);
    return true;
  case 0x016A:
    encode_codepoint(0x016B, cs, &bch[0]);
    return true;
  case 0x016C:
    encode_codepoint(0x016D, cs, &bch[0]);
    return true;
  case 0x016E:
    encode_codepoint(0x016F, cs, &bch[0]);
    return true;
  case 0x0170:
    encode_codepoint(0x0171, cs, &bch[0]);
    return true;
  case 0x0172:
    encode_codepoint(0x0173, cs, &bch[0]);
    return true;
  case 0x0174:
    encode_codepoint(0x0175, cs, &bch[0]);
    return true;
  case 0x0176:
    encode_codepoint(0x0177, cs, &bch[0]);
    return true;
  case 0x0178:
    encode_codepoint(0x00FF, cs, &bch[0]);
    return true;
  case 0x0179:
    encode_codepoint(0x017A, cs, &bch[0]);
    return true;
  case 0x017B:
    encode_codepoint(0x017C, cs, &bch[0]);
    return true;
  case 0x017D:
    encode_codepoint(0x017E, cs, &bch[0]);
    return true;
  case 0x017F:
    encode_codepoint(0x0073, cs, &bch[0]);
    return true;
  case 0x0181:
    encode_codepoint(0x0253, cs, &bch[0]);
    return true;
  case 0x0182:
    encode_codepoint(0x0183, cs, &bch[0]);
    return true;
  case 0x0184:
    encode_codepoint(0x0185, cs, &bch[0]);
    return true;
  case 0x0186:
    encode_codepoint(0x0254, cs, &bch[0]);
    return true;
  case 0x0187:
    encode_codepoint(0x0188, cs, &bch[0]);
    return true;
  case 0x0189:
    encode_codepoint(0x0256, cs, &bch[0]);
    return true;
  case 0x018A:
    encode_codepoint(0x0257, cs, &bch[0]);
    return true;
  case 0x018B:
    encode_codepoint(0x018C, cs, &bch[0]);
    return true;
  case 0x018E:
    encode_codepoint(0x01DD, cs, &bch[0]);
    return true;
  case 0x018F:
    encode_codepoint(0x0259, cs, &bch[0]);
    return true;
  case 0x0190:
    encode_codepoint(0x025B, cs, &bch[0]);
    return true;
  case 0x0191:
    encode_codepoint(0x0192, cs, &bch[0]);
    return true;
  case 0x0193:
    encode_codepoint(0x0260, cs, &bch[0]);
    return true;
  case 0x0194:
    encode_codepoint(0x0263, cs, &bch[0]);
    return true;
  case 0x0196:
    encode_codepoint(0x0269, cs, &bch[0]);
    return true;
  case 0x0197:
    encode_codepoint(0x0268, cs, &bch[0]);
    return true;
  case 0x0198:
    encode_codepoint(0x0199, cs, &bch[0]);
    return true;
  case 0x019C:
    encode_codepoint(0x026F, cs, &bch[0]);
    return true;
  case 0x019D:
    encode_codepoint(0x0272, cs, &bch[0]);
    return true;
  case 0x019F:
    encode_codepoint(0x0275, cs, &bch[0]);
    return true;
  case 0x01A0:
    encode_codepoint(0x01A1, cs, &bch[0]);
    return true;
  case 0x01A2:
    encode_codepoint(0x01A3, cs, &bch[0]);
    return true;
  case 0x01A4:
    encode_codepoint(0x01A5, cs, &bch[0]);
    return true;
  case 0x01A6:
    encode_codepoint(0x0280, cs, &bch[0]);
    return true;
  case 0x01A7:
    encode_codepoint(0x01A8, cs, &bch[0]);
    return true;
  case 0x01A9:
    encode_codepoint(0x0283, cs, &bch[0]);
    return true;
  case 0x01AC:
    encode_codepoint(0x01AD, cs, &bch[0]);
    return true;
  case 0x01AE:
    encode_codepoint(0x0288, cs, &bch[0]);
    return true;
  case 0x01AF:
    encode_codepoint(0x01B0, cs, &bch[0]);
    return true;
  case 0x01B1:
    encode_codepoint(0x028A, cs, &bch[0]);
    return true;
  case 0x01B2:
    encode_codepoint(0x028B, cs, &bch[0]);
    return true;
  case 0x01B3:
    encode_codepoint(0x01B4, cs, &bch[0]);
    return true;
  case 0x01B5:
    encode_codepoint(0x01B6, cs, &bch[0]);
    return true;
  case 0x01B7:
    encode_codepoint(0x0292, cs, &bch[0]);
    return true;
  case 0x01B8:
    encode_codepoint(0x01B9, cs, &bch[0]);
    return true;
  case 0x01BC:
    encode_codepoint(0x01BD, cs, &bch[0]);
    return true;
  case 0x01C4:
    encode_codepoint(0x01C6, cs, &bch[0]);
    return true;
  case 0x01C5:
    encode_codepoint(0x01C6, cs, &bch[0]);
    return true;
  case 0x01C7:
    encode_codepoint(0x01C9, cs, &bch[0]);
    return true;
  case 0x01C8:
    encode_codepoint(0x01C9, cs, &bch[0]);
    return true;
  case 0x01CA:
    encode_codepoint(0x01CC, cs, &bch[0]);
    return true;
  case 0x01CB:
    encode_codepoint(0x01CC, cs, &bch[0]);
    return true;
  case 0x01CD:
    encode_codepoint(0x01CE, cs, &bch[0]);
    return true;
  case 0x01CF:
    encode_codepoint(0x01D0, cs, &bch[0]);
    return true;
  case 0x01D1:
    encode_codepoint(0x01D2, cs, &bch[0]);
    return true;
  case 0x01D3:
    encode_codepoint(0x01D4, cs, &bch[0]);
    return true;
  case 0x01D5:
    encode_codepoint(0x01D6, cs, &bch[0]);
    return true;
  case 0x01D7:
    encode_codepoint(0x01D8, cs, &bch[0]);
    return true;
  case 0x01D9:
    encode_codepoint(0x01DA, cs, &bch[0]);
    return true;
  case 0x01DB:
    encode_codepoint(0x01DC, cs, &bch[0]);
    return true;
  case 0x01DE:
    encode_codepoint(0x01DF, cs, &bch[0]);
    return true;
  case 0x01E0:
    encode_codepoint(0x01E1, cs, &bch[0]);
    return true;
  case 0x01E2:
    encode_codepoint(0x01E3, cs, &bch[0]);
    return true;
  case 0x01E4:
    encode_codepoint(0x01E5, cs, &bch[0]);
    return true;
  case 0x01E6:
    encode_codepoint(0x01E7, cs, &bch[0]);
    return true;
  case 0x01E8:
    encode_codepoint(0x01E9, cs, &bch[0]);
    return true;
  case 0x01EA:
    encode_codepoint(0x01EB, cs, &bch[0]);
    return true;
  case 0x01EC:
    encode_codepoint(0x01ED, cs, &bch[0]);
    return true;
  case 0x01EE:
    encode_codepoint(0x01EF, cs, &bch[0]);
    return true;
  case 0x01F1:
    encode_codepoint(0x01F3, cs, &bch[0]);
    return true;
  case 0x01F2:
    encode_codepoint(0x01F3, cs, &bch[0]);
    return true;
  case 0x01F4:
    encode_codepoint(0x01F5, cs, &bch[0]);
    return true;
  case 0x01F6:
    encode_codepoint(0x0195, cs, &bch[0]);
    return true;
  case 0x01F7:
    encode_codepoint(0x01BF, cs, &bch[0]);
    return true;
  case 0x01F8:
    encode_codepoint(0x01F9, cs, &bch[0]);
    return true;
  case 0x01FA:
    encode_codepoint(0x01FB, cs, &bch[0]);
    return true;
  case 0x01FC:
    encode_codepoint(0x01FD, cs, &bch[0]);
    return true;
  case 0x01FE:
    encode_codepoint(0x01FF, cs, &bch[0]);
    return true;
  case 0x0200:
    encode_codepoint(0x0201, cs, &bch[0]);
    return true;
  case 0x0202:
    encode_codepoint(0x0203, cs, &bch[0]);
    return true;
  case 0x0204:
    encode_codepoint(0x0205, cs, &bch[0]);
    return true;
  case 0x0206:
    encode_codepoint(0x0207, cs, &bch[0]);
    return true;
  case 0x0208:
    encode_codepoint(0x0209, cs, &bch[0]);
    return true;
  case 0x020A:
    encode_codepoint(0x020B, cs, &bch[0]);
    return true;
  case 0x020C:
    encode_codepoint(0x020D, cs, &bch[0]);
    return true;
  case 0x020E:
    encode_codepoint(0x020F, cs, &bch[0]);
    return true;
  case 0x0210:
    encode_codepoint(0x0211, cs, &bch[0]);
    return true;
  case 0x0212:
    encode_codepoint(0x0213, cs, &bch[0]);
    return true;
  case 0x0214:
    encode_codepoint(0x0215, cs, &bch[0]);
    return true;
  case 0x0216:
    encode_codepoint(0x0217, cs, &bch[0]);
    return true;
  case 0x0218:
    encode_codepoint(0x0219, cs, &bch[0]);
    return true;
  case 0x021A:
    encode_codepoint(0x021B, cs, &bch[0]);
    return true;
  case 0x021C:
    encode_codepoint(0x021D, cs, &bch[0]);
    return true;
  case 0x021E:
    encode_codepoint(0x021F, cs, &bch[0]);
    return true;
  case 0x0220:
    encode_codepoint(0x019E, cs, &bch[0]);
    return true;
  case 0x0222:
    encode_codepoint(0x0223, cs, &bch[0]);
    return true;
  case 0x0224:
    encode_codepoint(0x0225, cs, &bch[0]);
    return true;
  case 0x0226:
    encode_codepoint(0x0227, cs, &bch[0]);
    return true;
  case 0x0228:
    encode_codepoint(0x0229, cs, &bch[0]);
    return true;
  case 0x022A:
    encode_codepoint(0x022B, cs, &bch[0]);
    return true;
  case 0x022C:
    encode_codepoint(0x022D, cs, &bch[0]);
    return true;
  case 0x022E:
    encode_codepoint(0x022F, cs, &bch[0]);
    return true;
  case 0x0230:
    encode_codepoint(0x0231, cs, &bch[0]);
    return true;
  case 0x0232:
    encode_codepoint(0x0233, cs, &bch[0]);
    return true;
  case 0x023A:
    encode_codepoint(0x2C65, cs, &bch[0]);
    return true;
  case 0x023B:
    encode_codepoint(0x023C, cs, &bch[0]);
    return true;
  case 0x023D:
    encode_codepoint(0x019A, cs, &bch[0]);
    return true;
  case 0x023E:
    encode_codepoint(0x2C66, cs, &bch[0]);
    return true;
  case 0x0241:
    encode_codepoint(0x0242, cs, &bch[0]);
    return true;
  case 0x0243:
    encode_codepoint(0x0180, cs, &bch[0]);
    return true;
  case 0x0244:
    encode_codepoint(0x0289, cs, &bch[0]);
    return true;
  case 0x0245:
    encode_codepoint(0x028C, cs, &bch[0]);
    return true;
  case 0x0246:
    encode_codepoint(0x0247, cs, &bch[0]);
    return true;
  case 0x0248:
    encode_codepoint(0x0249, cs, &bch[0]);
    return true;
  case 0x024A:
    encode_codepoint(0x024B, cs, &bch[0]);
    return true;
  case 0x024C:
    encode_codepoint(0x024D, cs, &bch[0]);
    return true;
  case 0x024E:
    encode_codepoint(0x024F, cs, &bch[0]);
    return true;
  case 0x0345:
    encode_codepoint(0x03B9, cs, &bch[0]);
    return true;
  case 0x0370:
    encode_codepoint(0x0371, cs, &bch[0]);
    return true;
  case 0x0372:
    encode_codepoint(0x0373, cs, &bch[0]);
    return true;
  case 0x0376:
    encode_codepoint(0x0377, cs, &bch[0]);
    return true;
  case 0x037F:
    encode_codepoint(0x03F3, cs, &bch[0]);
    return true;
  case 0x0386:
    encode_codepoint(0x03AC, cs, &bch[0]);
    return true;
  case 0x0388:
    encode_codepoint(0x03AD, cs, &bch[0]);
    return true;
  case 0x0389:
    encode_codepoint(0x03AE, cs, &bch[0]);
    return true;
  case 0x038A:
    encode_codepoint(0x03AF, cs, &bch[0]);
    return true;
  case 0x038C:
    encode_codepoint(0x03CC, cs, &bch[0]);
    return true;
  case 0x038E:
    encode_codepoint(0x03CD, cs, &bch[0]);
    return true;
  case 0x038F:
    encode_codepoint(0x03CE, cs, &bch[0]);
    return true;
  case 0x0391:
    encode_codepoint(0x03B1, cs, &bch[0]);
    return true;
  case 0x0392:
    encode_codepoint(0x03B2, cs, &bch[0]);
    return true;
  case 0x0393:
    encode_codepoint(0x03B3, cs, &bch[0]);
    return true;
  case 0x0394:
    encode_codepoint(0x03B4, cs, &bch[0]);
    return true;
  case 0x0395:
    encode_codepoint(0x03B5, cs, &bch[0]);
    return true;
  case 0x0396:
    encode_codepoint(0x03B6, cs, &bch[0]);
    return true;
  case 0x0397:
    encode_codepoint(0x03B7, cs, &bch[0]);
    return true;
  case 0x0398:
    encode_codepoint(0x03B8, cs, &bch[0]);
    return true;
  case 0x0399:
    encode_codepoint(0x03B9, cs, &bch[0]);
    return true;
  case 0x039A:
    encode_codepoint(0x03BA, cs, &bch[0]);
    return true;
  case 0x039B:
    encode_codepoint(0x03BB, cs, &bch[0]);
    return true;
  case 0x039C:
    encode_codepoint(0x03BC, cs, &bch[0]);
    return true;
  case 0x039D:
    encode_codepoint(0x03BD, cs, &bch[0]);
    return true;
  case 0x039E:
    encode_codepoint(0x03BE, cs, &bch[0]);
    return true;
  case 0x039F:
    encode_codepoint(0x03BF, cs, &bch[0]);
    return true;
  case 0x03A0:
    encode_codepoint(0x03C0, cs, &bch[0]);
    return true;
  case 0x03A1:
    encode_codepoint(0x03C1, cs, &bch[0]);
    return true;
  case 0x03A3:
    encode_codepoint(0x03C3, cs, &bch[0]);
    return true;
  case 0x03A4:
    encode_codepoint(0x03C4, cs, &bch[0]);
    return true;
  case 0x03A5:
    encode_codepoint(0x03C5, cs, &bch[0]);
    return true;
  case 0x03A6:
    encode_codepoint(0x03C6, cs, &bch[0]);
    return true;
  case 0x03A7:
    encode_codepoint(0x03C7, cs, &bch[0]);
    return true;
  case 0x03A8:
    encode_codepoint(0x03C8, cs, &bch[0]);
    return true;
  case 0x03A9:
    encode_codepoint(0x03C9, cs, &bch[0]);
    return true;
  case 0x03AA:
    encode_codepoint(0x03CA, cs, &bch[0]);
    return true;
  case 0x03AB:
    encode_codepoint(0x03CB, cs, &bch[0]);
    return true;
  case 0x03C2:
    encode_codepoint(0x03C3, cs, &bch[0]);
    return true;
  case 0x03CF:
    encode_codepoint(0x03D7, cs, &bch[0]);
    return true;
  case 0x03D0:
    encode_codepoint(0x03B2, cs, &bch[0]);
    return true;
  case 0x03D1:
    encode_codepoint(0x03B8, cs, &bch[0]);
    return true;
  case 0x03D5:
    encode_codepoint(0x03C6, cs, &bch[0]);
    return true;
  case 0x03D6:
    encode_codepoint(0x03C0, cs, &bch[0]);
    return true;
  case 0x03D8:
    encode_codepoint(0x03D9, cs, &bch[0]);
    return true;
  case 0x03DA:
    encode_codepoint(0x03DB, cs, &bch[0]);
    return true;
  case 0x03DC:
    encode_codepoint(0x03DD, cs, &bch[0]);
    return true;
  case 0x03DE:
    encode_codepoint(0x03DF, cs, &bch[0]);
    return true;
  case 0x03E0:
    encode_codepoint(0x03E1, cs, &bch[0]);
    return true;
  case 0x03E2:
    encode_codepoint(0x03E3, cs, &bch[0]);
    return true;
  case 0x03E4:
    encode_codepoint(0x03E5, cs, &bch[0]);
    return true;
  case 0x03E6:
    encode_codepoint(0x03E7, cs, &bch[0]);
    return true;
  case 0x03E8:
    encode_codepoint(0x03E9, cs, &bch[0]);
    return true;
  case 0x03EA:
    encode_codepoint(0x03EB, cs, &bch[0]);
    return true;
  case 0x03EC:
    encode_codepoint(0x03ED, cs, &bch[0]);
    return true;
  case 0x03EE:
    encode_codepoint(0x03EF, cs, &bch[0]);
    return true;
  case 0x03F0:
    encode_codepoint(0x03BA, cs, &bch[0]);
    return true;
  case 0x03F1:
    encode_codepoint(0x03C1, cs, &bch[0]);
    return true;
  case 0x03F4:
    encode_codepoint(0x03B8, cs, &bch[0]);
    return true;
  case 0x03F5:
    encode_codepoint(0x03B5, cs, &bch[0]);
    return true;
  case 0x03F7:
    encode_codepoint(0x03F8, cs, &bch[0]);
    return true;
  case 0x03F9:
    encode_codepoint(0x03F2, cs, &bch[0]);
    return true;
  case 0x03FA:
    encode_codepoint(0x03FB, cs, &bch[0]);
    return true;
  case 0x03FD:
    encode_codepoint(0x037B, cs, &bch[0]);
    return true;
  case 0x03FE:
    encode_codepoint(0x037C, cs, &bch[0]);
    return true;
  case 0x03FF:
    encode_codepoint(0x037D, cs, &bch[0]);
    return true;
  case 0x0400:
    encode_codepoint(0x0450, cs, &bch[0]);
    return true;
  case 0x0401:
    encode_codepoint(0x0451, cs, &bch[0]);
    return true;
  case 0x0402:
    encode_codepoint(0x0452, cs, &bch[0]);
    return true;
  case 0x0403:
    encode_codepoint(0x0453, cs, &bch[0]);
    return true;
  case 0x0404:
    encode_codepoint(0x0454, cs, &bch[0]);
    return true;
  case 0x0405:
    encode_codepoint(0x0455, cs, &bch[0]);
    return true;
  case 0x0406:
    encode_codepoint(0x0456, cs, &bch[0]);
    return true;
  case 0x0407:
    encode_codepoint(0x0457, cs, &bch[0]);
    return true;
  case 0x0408:
    encode_codepoint(0x0458, cs, &bch[0]);
    return true;
  case 0x0409:
    encode_codepoint(0x0459, cs, &bch[0]);
    return true;
  case 0x040A:
    encode_codepoint(0x045A, cs, &bch[0]);
    return true;
  case 0x040B:
    encode_codepoint(0x045B, cs, &bch[0]);
    return true;
  case 0x040C:
    encode_codepoint(0x045C, cs, &bch[0]);
    return true;
  case 0x040D:
    encode_codepoint(0x045D, cs, &bch[0]);
    return true;
  case 0x040E:
    encode_codepoint(0x045E, cs, &bch[0]);
    return true;
  case 0x040F:
    encode_codepoint(0x045F, cs, &bch[0]);
    return true;
  case 0x0410:
    encode_codepoint(0x0430, cs, &bch[0]);
    return true;
  case 0x0411:
    encode_codepoint(0x0431, cs, &bch[0]);
    return true;
  case 0x0412:
    encode_codepoint(0x0432, cs, &bch[0]);
    return true;
  case 0x0413:
    encode_codepoint(0x0433, cs, &bch[0]);
    return true;
  case 0x0414:
    encode_codepoint(0x0434, cs, &bch[0]);
    return true;
  case 0x0415:
    encode_codepoint(0x0435, cs, &bch[0]);
    return true;
  case 0x0416:
    encode_codepoint(0x0436, cs, &bch[0]);
    return true;
  case 0x0417:
    encode_codepoint(0x0437, cs, &bch[0]);
    return true;
  case 0x0418:
    encode_codepoint(0x0438, cs, &bch[0]);
    return true;
  case 0x0419:
    encode_codepoint(0x0439, cs, &bch[0]);
    return true;
  case 0x041A:
    encode_codepoint(0x043A, cs, &bch[0]);
    return true;
  case 0x041B:
    encode_codepoint(0x043B, cs, &bch[0]);
    return true;
  case 0x041C:
    encode_codepoint(0x043C, cs, &bch[0]);
    return true;
  case 0x041D:
    encode_codepoint(0x043D, cs, &bch[0]);
    return true;
  case 0x041E:
    encode_codepoint(0x043E, cs, &bch[0]);
    return true;
  case 0x041F:
    encode_codepoint(0x043F, cs, &bch[0]);
    return true;
  case 0x0420:
    encode_codepoint(0x0440, cs, &bch[0]);
    return true;
  case 0x0421:
    encode_codepoint(0x0441, cs, &bch[0]);
    return true;
  case 0x0422:
    encode_codepoint(0x0442, cs, &bch[0]);
    return true;
  case 0x0423:
    encode_codepoint(0x0443, cs, &bch[0]);
    return true;
  case 0x0424:
    encode_codepoint(0x0444, cs, &bch[0]);
    return true;
  case 0x0425:
    encode_codepoint(0x0445, cs, &bch[0]);
    return true;
  case 0x0426:
    encode_codepoint(0x0446, cs, &bch[0]);
    return true;
  case 0x0427:
    encode_codepoint(0x0447, cs, &bch[0]);
    return true;
  case 0x0428:
    encode_codepoint(0x0448, cs, &bch[0]);
    return true;
  case 0x0429:
    encode_codepoint(0x0449, cs, &bch[0]);
    return true;
  case 0x042A:
    encode_codepoint(0x044A, cs, &bch[0]);
    return true;
  case 0x042B:
    encode_codepoint(0x044B, cs, &bch[0]);
    return true;
  case 0x042C:
    encode_codepoint(0x044C, cs, &bch[0]);
    return true;
  case 0x042D:
    encode_codepoint(0x044D, cs, &bch[0]);
    return true;
  case 0x042E:
    encode_codepoint(0x044E, cs, &bch[0]);
    return true;
  case 0x042F:
    encode_codepoint(0x044F, cs, &bch[0]);
    return true;
  case 0x0460:
    encode_codepoint(0x0461, cs, &bch[0]);
    return true;
  case 0x0462:
    encode_codepoint(0x0463, cs, &bch[0]);
    return true;
  case 0x0464:
    encode_codepoint(0x0465, cs, &bch[0]);
    return true;
  case 0x0466:
    encode_codepoint(0x0467, cs, &bch[0]);
    return true;
  case 0x0468:
    encode_codepoint(0x0469, cs, &bch[0]);
    return true;
  case 0x046A:
    encode_codepoint(0x046B, cs, &bch[0]);
    return true;
  case 0x046C:
    encode_codepoint(0x046D, cs, &bch[0]);
    return true;
  case 0x046E:
    encode_codepoint(0x046F, cs, &bch[0]);
    return true;
  case 0x0470:
    encode_codepoint(0x0471, cs, &bch[0]);
    return true;
  case 0x0472:
    encode_codepoint(0x0473, cs, &bch[0]);
    return true;
  case 0x0474:
    encode_codepoint(0x0475, cs, &bch[0]);
    return true;
  case 0x0476:
    encode_codepoint(0x0477, cs, &bch[0]);
    return true;
  case 0x0478:
    encode_codepoint(0x0479, cs, &bch[0]);
    return true;
  case 0x047A:
    encode_codepoint(0x047B, cs, &bch[0]);
    return true;
  case 0x047C:
    encode_codepoint(0x047D, cs, &bch[0]);
    return true;
  case 0x047E:
    encode_codepoint(0x047F, cs, &bch[0]);
    return true;
  case 0x0480:
    encode_codepoint(0x0481, cs, &bch[0]);
    return true;
  case 0x048A:
    encode_codepoint(0x048B, cs, &bch[0]);
    return true;
  case 0x048C:
    encode_codepoint(0x048D, cs, &bch[0]);
    return true;
  case 0x048E:
    encode_codepoint(0x048F, cs, &bch[0]);
    return true;
  case 0x0490:
    encode_codepoint(0x0491, cs, &bch[0]);
    return true;
  case 0x0492:
    encode_codepoint(0x0493, cs, &bch[0]);
    return true;
  case 0x0494:
    encode_codepoint(0x0495, cs, &bch[0]);
    return true;
  case 0x0496:
    encode_codepoint(0x0497, cs, &bch[0]);
    return true;
  case 0x0498:
    encode_codepoint(0x0499, cs, &bch[0]);
    return true;
  case 0x049A:
    encode_codepoint(0x049B, cs, &bch[0]);
    return true;
  case 0x049C:
    encode_codepoint(0x049D, cs, &bch[0]);
    return true;
  case 0x049E:
    encode_codepoint(0x049F, cs, &bch[0]);
    return true;
  case 0x04A0:
    encode_codepoint(0x04A1, cs, &bch[0]);
    return true;
  case 0x04A2:
    encode_codepoint(0x04A3, cs, &bch[0]);
    return true;
  case 0x04A4:
    encode_codepoint(0x04A5, cs, &bch[0]);
    return true;
  case 0x04A6:
    encode_codepoint(0x04A7, cs, &bch[0]);
    return true;
  case 0x04A8:
    encode_codepoint(0x04A9, cs, &bch[0]);
    return true;
  case 0x04AA:
    encode_codepoint(0x04AB, cs, &bch[0]);
    return true;
  case 0x04AC:
    encode_codepoint(0x04AD, cs, &bch[0]);
    return true;
  case 0x04AE:
    encode_codepoint(0x04AF, cs, &bch[0]);
    return true;
  case 0x04B0:
    encode_codepoint(0x04B1, cs, &bch[0]);
    return true;
  case 0x04B2:
    encode_codepoint(0x04B3, cs, &bch[0]);
    return true;
  case 0x04B4:
    encode_codepoint(0x04B5, cs, &bch[0]);
    return true;
  case 0x04B6:
    encode_codepoint(0x04B7, cs, &bch[0]);
    return true;
  case 0x04B8:
    encode_codepoint(0x04B9, cs, &bch[0]);
    return true;
  case 0x04BA:
    encode_codepoint(0x04BB, cs, &bch[0]);
    return true;
  case 0x04BC:
    encode_codepoint(0x04BD, cs, &bch[0]);
    return true;
  case 0x04BE:
    encode_codepoint(0x04BF, cs, &bch[0]);
    return true;
  case 0x04C0:
    encode_codepoint(0x04CF, cs, &bch[0]);
    return true;
  case 0x04C1:
    encode_codepoint(0x04C2, cs, &bch[0]);
    return true;
  case 0x04C3:
    encode_codepoint(0x04C4, cs, &bch[0]);
    return true;
  case 0x04C5:
    encode_codepoint(0x04C6, cs, &bch[0]);
    return true;
  case 0x04C7:
    encode_codepoint(0x04C8, cs, &bch[0]);
    return true;
  case 0x04C9:
    encode_codepoint(0x04CA, cs, &bch[0]);
    return true;
  case 0x04CB:
    encode_codepoint(0x04CC, cs, &bch[0]);
    return true;
  case 0x04CD:
    encode_codepoint(0x04CE, cs, &bch[0]);
    return true;
  case 0x04D0:
    encode_codepoint(0x04D1, cs, &bch[0]);
    return true;
  case 0x04D2:
    encode_codepoint(0x04D3, cs, &bch[0]);
    return true;
  case 0x04D4:
    encode_codepoint(0x04D5, cs, &bch[0]);
    return true;
  case 0x04D6:
    encode_codepoint(0x04D7, cs, &bch[0]);
    return true;
  case 0x04D8:
    encode_codepoint(0x04D9, cs, &bch[0]);
    return true;
  case 0x04DA:
    encode_codepoint(0x04DB, cs, &bch[0]);
    return true;
  case 0x04DC:
    encode_codepoint(0x04DD, cs, &bch[0]);
    return true;
  case 0x04DE:
    encode_codepoint(0x04DF, cs, &bch[0]);
    return true;
  case 0x04E0:
    encode_codepoint(0x04E1, cs, &bch[0]);
    return true;
  case 0x04E2:
    encode_codepoint(0x04E3, cs, &bch[0]);
    return true;
  case 0x04E4:
    encode_codepoint(0x04E5, cs, &bch[0]);
    return true;
  case 0x04E6:
    encode_codepoint(0x04E7, cs, &bch[0]);
    return true;
  case 0x04E8:
    encode_codepoint(0x04E9, cs, &bch[0]);
    return true;
  case 0x04EA:
    encode_codepoint(0x04EB, cs, &bch[0]);
    return true;
  case 0x04EC:
    encode_codepoint(0x04ED, cs, &bch[0]);
    return true;
  case 0x04EE:
    encode_codepoint(0x04EF, cs, &bch[0]);
    return true;
  case 0x04F0:
    encode_codepoint(0x04F1, cs, &bch[0]);
    return true;
  case 0x04F2:
    encode_codepoint(0x04F3, cs, &bch[0]);
    return true;
  case 0x04F4:
    encode_codepoint(0x04F5, cs, &bch[0]);
    return true;
  case 0x04F6:
    encode_codepoint(0x04F7, cs, &bch[0]);
    return true;
  case 0x04F8:
    encode_codepoint(0x04F9, cs, &bch[0]);
    return true;
  case 0x04FA:
    encode_codepoint(0x04FB, cs, &bch[0]);
    return true;
  case 0x04FC:
    encode_codepoint(0x04FD, cs, &bch[0]);
    return true;
  case 0x04FE:
    encode_codepoint(0x04FF, cs, &bch[0]);
    return true;
  case 0x0500:
    encode_codepoint(0x0501, cs, &bch[0]);
    return true;
  case 0x0502:
    encode_codepoint(0x0503, cs, &bch[0]);
    return true;
  case 0x0504:
    encode_codepoint(0x0505, cs, &bch[0]);
    return true;
  case 0x0506:
    encode_codepoint(0x0507, cs, &bch[0]);
    return true;
  case 0x0508:
    encode_codepoint(0x0509, cs, &bch[0]);
    return true;
  case 0x050A:
    encode_codepoint(0x050B, cs, &bch[0]);
    return true;
  case 0x050C:
    encode_codepoint(0x050D, cs, &bch[0]);
    return true;
  case 0x050E:
    encode_codepoint(0x050F, cs, &bch[0]);
    return true;
  case 0x0510:
    encode_codepoint(0x0511, cs, &bch[0]);
    return true;
  case 0x0512:
    encode_codepoint(0x0513, cs, &bch[0]);
    return true;
  case 0x0514:
    encode_codepoint(0x0515, cs, &bch[0]);
    return true;
  case 0x0516:
    encode_codepoint(0x0517, cs, &bch[0]);
    return true;
  case 0x0518:
    encode_codepoint(0x0519, cs, &bch[0]);
    return true;
  case 0x051A:
    encode_codepoint(0x051B, cs, &bch[0]);
    return true;
  case 0x051C:
    encode_codepoint(0x051D, cs, &bch[0]);
    return true;
  case 0x051E:
    encode_codepoint(0x051F, cs, &bch[0]);
    return true;
  case 0x0520:
    encode_codepoint(0x0521, cs, &bch[0]);
    return true;
  case 0x0522:
    encode_codepoint(0x0523, cs, &bch[0]);
    return true;
  case 0x0524:
    encode_codepoint(0x0525, cs, &bch[0]);
    return true;
  case 0x0526:
    encode_codepoint(0x0527, cs, &bch[0]);
    return true;
  case 0x0528:
    encode_codepoint(0x0529, cs, &bch[0]);
    return true;
  case 0x052A:
    encode_codepoint(0x052B, cs, &bch[0]);
    return true;
  case 0x052C:
    encode_codepoint(0x052D, cs, &bch[0]);
    return true;
  case 0x052E:
    encode_codepoint(0x052F, cs, &bch[0]);
    return true;
  case 0x0531:
    encode_codepoint(0x0561, cs, &bch[0]);
    return true;
  case 0x0532:
    encode_codepoint(0x0562, cs, &bch[0]);
    return true;
  case 0x0533:
    encode_codepoint(0x0563, cs, &bch[0]);
    return true;
  case 0x0534:
    encode_codepoint(0x0564, cs, &bch[0]);
    return true;
  case 0x0535:
    encode_codepoint(0x0565, cs, &bch[0]);
    return true;
  case 0x0536:
    encode_codepoint(0x0566, cs, &bch[0]);
    return true;
  case 0x0537:
    encode_codepoint(0x0567, cs, &bch[0]);
    return true;
  case 0x0538:
    encode_codepoint(0x0568, cs, &bch[0]);
    return true;
  case 0x0539:
    encode_codepoint(0x0569, cs, &bch[0]);
    return true;
  case 0x053A:
    encode_codepoint(0x056A, cs, &bch[0]);
    return true;
  case 0x053B:
    encode_codepoint(0x056B, cs, &bch[0]);
    return true;
  case 0x053C:
    encode_codepoint(0x056C, cs, &bch[0]);
    return true;
  case 0x053D:
    encode_codepoint(0x056D, cs, &bch[0]);
    return true;
  case 0x053E:
    encode_codepoint(0x056E, cs, &bch[0]);
    return true;
  case 0x053F:
    encode_codepoint(0x056F, cs, &bch[0]);
    return true;
  case 0x0540:
    encode_codepoint(0x0570, cs, &bch[0]);
    return true;
  case 0x0541:
    encode_codepoint(0x0571, cs, &bch[0]);
    return true;
  case 0x0542:
    encode_codepoint(0x0572, cs, &bch[0]);
    return true;
  case 0x0543:
    encode_codepoint(0x0573, cs, &bch[0]);
    return true;
  case 0x0544:
    encode_codepoint(0x0574, cs, &bch[0]);
    return true;
  case 0x0545:
    encode_codepoint(0x0575, cs, &bch[0]);
    return true;
  case 0x0546:
    encode_codepoint(0x0576, cs, &bch[0]);
    return true;
  case 0x0547:
    encode_codepoint(0x0577, cs, &bch[0]);
    return true;
  case 0x0548:
    encode_codepoint(0x0578, cs, &bch[0]);
    return true;
  case 0x0549:
    encode_codepoint(0x0579, cs, &bch[0]);
    return true;
  case 0x054A:
    encode_codepoint(0x057A, cs, &bch[0]);
    return true;
  case 0x054B:
    encode_codepoint(0x057B, cs, &bch[0]);
    return true;
  case 0x054C:
    encode_codepoint(0x057C, cs, &bch[0]);
    return true;
  case 0x054D:
    encode_codepoint(0x057D, cs, &bch[0]);
    return true;
  case 0x054E:
    encode_codepoint(0x057E, cs, &bch[0]);
    return true;
  case 0x054F:
    encode_codepoint(0x057F, cs, &bch[0]);
    return true;
  case 0x0550:
    encode_codepoint(0x0580, cs, &bch[0]);
    return true;
  case 0x0551:
    encode_codepoint(0x0581, cs, &bch[0]);
    return true;
  case 0x0552:
    encode_codepoint(0x0582, cs, &bch[0]);
    return true;
  case 0x0553:
    encode_codepoint(0x0583, cs, &bch[0]);
    return true;
  case 0x0554:
    encode_codepoint(0x0584, cs, &bch[0]);
    return true;
  case 0x0555:
    encode_codepoint(0x0585, cs, &bch[0]);
    return true;
  case 0x0556:
    encode_codepoint(0x0586, cs, &bch[0]);
    return true;
  case 0x10400:
    encode_codepoint(0x10428, cs, &bch[0]);
    return true;
  case 0x10401:
    encode_codepoint(0x10429, cs, &bch[0]);
    return true;
  case 0x10402:
    encode_codepoint(0x1042A, cs, &bch[0]);
    return true;
  case 0x10403:
    encode_codepoint(0x1042B, cs, &bch[0]);
    return true;
  case 0x10404:
    encode_codepoint(0x1042C, cs, &bch[0]);
    return true;
  case 0x10405:
    encode_codepoint(0x1042D, cs, &bch[0]);
    return true;
  case 0x10406:
    encode_codepoint(0x1042E, cs, &bch[0]);
    return true;
  case 0x10407:
    encode_codepoint(0x1042F, cs, &bch[0]);
    return true;
  case 0x10408:
    encode_codepoint(0x10430, cs, &bch[0]);
    return true;
  case 0x10409:
    encode_codepoint(0x10431, cs, &bch[0]);
    return true;
  case 0x1040A:
    encode_codepoint(0x10432, cs, &bch[0]);
    return true;
  case 0x1040B:
    encode_codepoint(0x10433, cs, &bch[0]);
    return true;
  case 0x1040C:
    encode_codepoint(0x10434, cs, &bch[0]);
    return true;
  case 0x1040D:
    encode_codepoint(0x10435, cs, &bch[0]);
    return true;
  case 0x1040E:
    encode_codepoint(0x10436, cs, &bch[0]);
    return true;
  case 0x1040F:
    encode_codepoint(0x10437, cs, &bch[0]);
    return true;
  case 0x10410:
    encode_codepoint(0x10438, cs, &bch[0]);
    return true;
  case 0x10411:
    encode_codepoint(0x10439, cs, &bch[0]);
    return true;
  case 0x10412:
    encode_codepoint(0x1043A, cs, &bch[0]);
    return true;
  case 0x10413:
    encode_codepoint(0x1043B, cs, &bch[0]);
    return true;
  case 0x10414:
    encode_codepoint(0x1043C, cs, &bch[0]);
    return true;
  case 0x10415:
    encode_codepoint(0x1043D, cs, &bch[0]);
    return true;
  case 0x10416:
    encode_codepoint(0x1043E, cs, &bch[0]);
    return true;
  case 0x10417:
    encode_codepoint(0x1043F, cs, &bch[0]);
    return true;
  case 0x10418:
    encode_codepoint(0x10440, cs, &bch[0]);
    return true;
  case 0x10419:
    encode_codepoint(0x10441, cs, &bch[0]);
    return true;
  case 0x1041A:
    encode_codepoint(0x10442, cs, &bch[0]);
    return true;
  case 0x1041B:
    encode_codepoint(0x10443, cs, &bch[0]);
    return true;
  case 0x1041C:
    encode_codepoint(0x10444, cs, &bch[0]);
    return true;
  case 0x1041D:
    encode_codepoint(0x10445, cs, &bch[0]);
    return true;
  case 0x1041E:
    encode_codepoint(0x10446, cs, &bch[0]);
    return true;
  case 0x1041F:
    encode_codepoint(0x10447, cs, &bch[0]);
    return true;
  case 0x10420:
    encode_codepoint(0x10448, cs, &bch[0]);
    return true;
  case 0x10421:
    encode_codepoint(0x10449, cs, &bch[0]);
    return true;
  case 0x10422:
    encode_codepoint(0x1044A, cs, &bch[0]);
    return true;
  case 0x10423:
    encode_codepoint(0x1044B, cs, &bch[0]);
    return true;
  case 0x10424:
    encode_codepoint(0x1044C, cs, &bch[0]);
    return true;
  case 0x10425:
    encode_codepoint(0x1044D, cs, &bch[0]);
    return true;
  case 0x10426:
    encode_codepoint(0x1044E, cs, &bch[0]);
    return true;
  case 0x10427:
    encode_codepoint(0x1044F, cs, &bch[0]);
    return true;
  case 0x10A0:
    encode_codepoint(0x2D00, cs, &bch[0]);
    return true;
  case 0x10A1:
    encode_codepoint(0x2D01, cs, &bch[0]);
    return true;
  case 0x10A2:
    encode_codepoint(0x2D02, cs, &bch[0]);
    return true;
  case 0x10A3:
    encode_codepoint(0x2D03, cs, &bch[0]);
    return true;
  case 0x10A4:
    encode_codepoint(0x2D04, cs, &bch[0]);
    return true;
  case 0x10A5:
    encode_codepoint(0x2D05, cs, &bch[0]);
    return true;
  case 0x10A6:
    encode_codepoint(0x2D06, cs, &bch[0]);
    return true;
  case 0x10A7:
    encode_codepoint(0x2D07, cs, &bch[0]);
    return true;
  case 0x10A8:
    encode_codepoint(0x2D08, cs, &bch[0]);
    return true;
  case 0x10A9:
    encode_codepoint(0x2D09, cs, &bch[0]);
    return true;
  case 0x10AA:
    encode_codepoint(0x2D0A, cs, &bch[0]);
    return true;
  case 0x10AB:
    encode_codepoint(0x2D0B, cs, &bch[0]);
    return true;
  case 0x10AC:
    encode_codepoint(0x2D0C, cs, &bch[0]);
    return true;
  case 0x10AD:
    encode_codepoint(0x2D0D, cs, &bch[0]);
    return true;
  case 0x10AE:
    encode_codepoint(0x2D0E, cs, &bch[0]);
    return true;
  case 0x10AF:
    encode_codepoint(0x2D0F, cs, &bch[0]);
    return true;
  case 0x10B0:
    encode_codepoint(0x2D10, cs, &bch[0]);
    return true;
  case 0x10B1:
    encode_codepoint(0x2D11, cs, &bch[0]);
    return true;
  case 0x10B2:
    encode_codepoint(0x2D12, cs, &bch[0]);
    return true;
  case 0x10B3:
    encode_codepoint(0x2D13, cs, &bch[0]);
    return true;
  case 0x10B4:
    encode_codepoint(0x2D14, cs, &bch[0]);
    return true;
  case 0x10B5:
    encode_codepoint(0x2D15, cs, &bch[0]);
    return true;
  case 0x10B6:
    encode_codepoint(0x2D16, cs, &bch[0]);
    return true;
  case 0x10B7:
    encode_codepoint(0x2D17, cs, &bch[0]);
    return true;
  case 0x10B8:
    encode_codepoint(0x2D18, cs, &bch[0]);
    return true;
  case 0x10B9:
    encode_codepoint(0x2D19, cs, &bch[0]);
    return true;
  case 0x10BA:
    encode_codepoint(0x2D1A, cs, &bch[0]);
    return true;
  case 0x10BB:
    encode_codepoint(0x2D1B, cs, &bch[0]);
    return true;
  case 0x10BC:
    encode_codepoint(0x2D1C, cs, &bch[0]);
    return true;
  case 0x10BD:
    encode_codepoint(0x2D1D, cs, &bch[0]);
    return true;
  case 0x10BE:
    encode_codepoint(0x2D1E, cs, &bch[0]);
    return true;
  case 0x10BF:
    encode_codepoint(0x2D1F, cs, &bch[0]);
    return true;
  case 0x10C0:
    encode_codepoint(0x2D20, cs, &bch[0]);
    return true;
  case 0x10C1:
    encode_codepoint(0x2D21, cs, &bch[0]);
    return true;
  case 0x10C2:
    encode_codepoint(0x2D22, cs, &bch[0]);
    return true;
  case 0x10C3:
    encode_codepoint(0x2D23, cs, &bch[0]);
    return true;
  case 0x10C4:
    encode_codepoint(0x2D24, cs, &bch[0]);
    return true;
  case 0x10C5:
    encode_codepoint(0x2D25, cs, &bch[0]);
    return true;
  case 0x10C7:
    encode_codepoint(0x2D27, cs, &bch[0]);
    return true;
  case 0x10CD:
    encode_codepoint(0x2D2D, cs, &bch[0]);
    return true;
  case 0x118A0:
    encode_codepoint(0x118C0, cs, &bch[0]);
    return true;
  case 0x118A1:
    encode_codepoint(0x118C1, cs, &bch[0]);
    return true;
  case 0x118A2:
    encode_codepoint(0x118C2, cs, &bch[0]);
    return true;
  case 0x118A3:
    encode_codepoint(0x118C3, cs, &bch[0]);
    return true;
  case 0x118A4:
    encode_codepoint(0x118C4, cs, &bch[0]);
    return true;
  case 0x118A5:
    encode_codepoint(0x118C5, cs, &bch[0]);
    return true;
  case 0x118A6:
    encode_codepoint(0x118C6, cs, &bch[0]);
    return true;
  case 0x118A7:
    encode_codepoint(0x118C7, cs, &bch[0]);
    return true;
  case 0x118A8:
    encode_codepoint(0x118C8, cs, &bch[0]);
    return true;
  case 0x118A9:
    encode_codepoint(0x118C9, cs, &bch[0]);
    return true;
  case 0x118AA:
    encode_codepoint(0x118CA, cs, &bch[0]);
    return true;
  case 0x118AB:
    encode_codepoint(0x118CB, cs, &bch[0]);
    return true;
  case 0x118AC:
    encode_codepoint(0x118CC, cs, &bch[0]);
    return true;
  case 0x118AD:
    encode_codepoint(0x118CD, cs, &bch[0]);
    return true;
  case 0x118AE:
    encode_codepoint(0x118CE, cs, &bch[0]);
    return true;
  case 0x118AF:
    encode_codepoint(0x118CF, cs, &bch[0]);
    return true;
  case 0x118B0:
    encode_codepoint(0x118D0, cs, &bch[0]);
    return true;
  case 0x118B1:
    encode_codepoint(0x118D1, cs, &bch[0]);
    return true;
  case 0x118B2:
    encode_codepoint(0x118D2, cs, &bch[0]);
    return true;
  case 0x118B3:
    encode_codepoint(0x118D3, cs, &bch[0]);
    return true;
  case 0x118B4:
    encode_codepoint(0x118D4, cs, &bch[0]);
    return true;
  case 0x118B5:
    encode_codepoint(0x118D5, cs, &bch[0]);
    return true;
  case 0x118B6:
    encode_codepoint(0x118D6, cs, &bch[0]);
    return true;
  case 0x118B7:
    encode_codepoint(0x118D7, cs, &bch[0]);
    return true;
  case 0x118B8:
    encode_codepoint(0x118D8, cs, &bch[0]);
    return true;
  case 0x118B9:
    encode_codepoint(0x118D9, cs, &bch[0]);
    return true;
  case 0x118BA:
    encode_codepoint(0x118DA, cs, &bch[0]);
    return true;
  case 0x118BB:
    encode_codepoint(0x118DB, cs, &bch[0]);
    return true;
  case 0x118BC:
    encode_codepoint(0x118DC, cs, &bch[0]);
    return true;
  case 0x118BD:
    encode_codepoint(0x118DD, cs, &bch[0]);
    return true;
  case 0x118BE:
    encode_codepoint(0x118DE, cs, &bch[0]);
    return true;
  case 0x118BF:
    encode_codepoint(0x118DF, cs, &bch[0]);
    return true;
  case 0x1E00:
    encode_codepoint(0x1E01, cs, &bch[0]);
    return true;
  case 0x1E02:
    encode_codepoint(0x1E03, cs, &bch[0]);
    return true;
  case 0x1E04:
    encode_codepoint(0x1E05, cs, &bch[0]);
    return true;
  case 0x1E06:
    encode_codepoint(0x1E07, cs, &bch[0]);
    return true;
  case 0x1E08:
    encode_codepoint(0x1E09, cs, &bch[0]);
    return true;
  case 0x1E0A:
    encode_codepoint(0x1E0B, cs, &bch[0]);
    return true;
  case 0x1E0C:
    encode_codepoint(0x1E0D, cs, &bch[0]);
    return true;
  case 0x1E0E:
    encode_codepoint(0x1E0F, cs, &bch[0]);
    return true;
  case 0x1E10:
    encode_codepoint(0x1E11, cs, &bch[0]);
    return true;
  case 0x1E12:
    encode_codepoint(0x1E13, cs, &bch[0]);
    return true;
  case 0x1E14:
    encode_codepoint(0x1E15, cs, &bch[0]);
    return true;
  case 0x1E16:
    encode_codepoint(0x1E17, cs, &bch[0]);
    return true;
  case 0x1E18:
    encode_codepoint(0x1E19, cs, &bch[0]);
    return true;
  case 0x1E1A:
    encode_codepoint(0x1E1B, cs, &bch[0]);
    return true;
  case 0x1E1C:
    encode_codepoint(0x1E1D, cs, &bch[0]);
    return true;
  case 0x1E1E:
    encode_codepoint(0x1E1F, cs, &bch[0]);
    return true;
  case 0x1E20:
    encode_codepoint(0x1E21, cs, &bch[0]);
    return true;
  case 0x1E22:
    encode_codepoint(0x1E23, cs, &bch[0]);
    return true;
  case 0x1E24:
    encode_codepoint(0x1E25, cs, &bch[0]);
    return true;
  case 0x1E26:
    encode_codepoint(0x1E27, cs, &bch[0]);
    return true;
  case 0x1E28:
    encode_codepoint(0x1E29, cs, &bch[0]);
    return true;
  case 0x1E2A:
    encode_codepoint(0x1E2B, cs, &bch[0]);
    return true;
  case 0x1E2C:
    encode_codepoint(0x1E2D, cs, &bch[0]);
    return true;
  case 0x1E2E:
    encode_codepoint(0x1E2F, cs, &bch[0]);
    return true;
  case 0x1E30:
    encode_codepoint(0x1E31, cs, &bch[0]);
    return true;
  case 0x1E32:
    encode_codepoint(0x1E33, cs, &bch[0]);
    return true;
  case 0x1E34:
    encode_codepoint(0x1E35, cs, &bch[0]);
    return true;
  case 0x1E36:
    encode_codepoint(0x1E37, cs, &bch[0]);
    return true;
  case 0x1E38:
    encode_codepoint(0x1E39, cs, &bch[0]);
    return true;
  case 0x1E3A:
    encode_codepoint(0x1E3B, cs, &bch[0]);
    return true;
  case 0x1E3C:
    encode_codepoint(0x1E3D, cs, &bch[0]);
    return true;
  case 0x1E3E:
    encode_codepoint(0x1E3F, cs, &bch[0]);
    return true;
  case 0x1E40:
    encode_codepoint(0x1E41, cs, &bch[0]);
    return true;
  case 0x1E42:
    encode_codepoint(0x1E43, cs, &bch[0]);
    return true;
  case 0x1E44:
    encode_codepoint(0x1E45, cs, &bch[0]);
    return true;
  case 0x1E46:
    encode_codepoint(0x1E47, cs, &bch[0]);
    return true;
  case 0x1E48:
    encode_codepoint(0x1E49, cs, &bch[0]);
    return true;
  case 0x1E4A:
    encode_codepoint(0x1E4B, cs, &bch[0]);
    return true;
  case 0x1E4C:
    encode_codepoint(0x1E4D, cs, &bch[0]);
    return true;
  case 0x1E4E:
    encode_codepoint(0x1E4F, cs, &bch[0]);
    return true;
  case 0x1E50:
    encode_codepoint(0x1E51, cs, &bch[0]);
    return true;
  case 0x1E52:
    encode_codepoint(0x1E53, cs, &bch[0]);
    return true;
  case 0x1E54:
    encode_codepoint(0x1E55, cs, &bch[0]);
    return true;
  case 0x1E56:
    encode_codepoint(0x1E57, cs, &bch[0]);
    return true;
  case 0x1E58:
    encode_codepoint(0x1E59, cs, &bch[0]);
    return true;
  case 0x1E5A:
    encode_codepoint(0x1E5B, cs, &bch[0]);
    return true;
  case 0x1E5C:
    encode_codepoint(0x1E5D, cs, &bch[0]);
    return true;
  case 0x1E5E:
    encode_codepoint(0x1E5F, cs, &bch[0]);
    return true;
  case 0x1E60:
    encode_codepoint(0x1E61, cs, &bch[0]);
    return true;
  case 0x1E62:
    encode_codepoint(0x1E63, cs, &bch[0]);
    return true;
  case 0x1E64:
    encode_codepoint(0x1E65, cs, &bch[0]);
    return true;
  case 0x1E66:
    encode_codepoint(0x1E67, cs, &bch[0]);
    return true;
  case 0x1E68:
    encode_codepoint(0x1E69, cs, &bch[0]);
    return true;
  case 0x1E6A:
    encode_codepoint(0x1E6B, cs, &bch[0]);
    return true;
  case 0x1E6C:
    encode_codepoint(0x1E6D, cs, &bch[0]);
    return true;
  case 0x1E6E:
    encode_codepoint(0x1E6F, cs, &bch[0]);
    return true;
  case 0x1E70:
    encode_codepoint(0x1E71, cs, &bch[0]);
    return true;
  case 0x1E72:
    encode_codepoint(0x1E73, cs, &bch[0]);
    return true;
  case 0x1E74:
    encode_codepoint(0x1E75, cs, &bch[0]);
    return true;
  case 0x1E76:
    encode_codepoint(0x1E77, cs, &bch[0]);
    return true;
  case 0x1E78:
    encode_codepoint(0x1E79, cs, &bch[0]);
    return true;
  case 0x1E7A:
    encode_codepoint(0x1E7B, cs, &bch[0]);
    return true;
  case 0x1E7C:
    encode_codepoint(0x1E7D, cs, &bch[0]);
    return true;
  case 0x1E7E:
    encode_codepoint(0x1E7F, cs, &bch[0]);
    return true;
  case 0x1E80:
    encode_codepoint(0x1E81, cs, &bch[0]);
    return true;
  case 0x1E82:
    encode_codepoint(0x1E83, cs, &bch[0]);
    return true;
  case 0x1E84:
    encode_codepoint(0x1E85, cs, &bch[0]);
    return true;
  case 0x1E86:
    encode_codepoint(0x1E87, cs, &bch[0]);
    return true;
  case 0x1E88:
    encode_codepoint(0x1E89, cs, &bch[0]);
    return true;
  case 0x1E8A:
    encode_codepoint(0x1E8B, cs, &bch[0]);
    return true;
  case 0x1E8C:
    encode_codepoint(0x1E8D, cs, &bch[0]);
    return true;
  case 0x1E8E:
    encode_codepoint(0x1E8F, cs, &bch[0]);
    return true;
  case 0x1E90:
    encode_codepoint(0x1E91, cs, &bch[0]);
    return true;
  case 0x1E92:
    encode_codepoint(0x1E93, cs, &bch[0]);
    return true;
  case 0x1E94:
    encode_codepoint(0x1E95, cs, &bch[0]);
    return true;
  case 0x1E9B:
    encode_codepoint(0x1E61, cs, &bch[0]);
    return true;
  case 0x1EA0:
    encode_codepoint(0x1EA1, cs, &bch[0]);
    return true;
  case 0x1EA2:
    encode_codepoint(0x1EA3, cs, &bch[0]);
    return true;
  case 0x1EA4:
    encode_codepoint(0x1EA5, cs, &bch[0]);
    return true;
  case 0x1EA6:
    encode_codepoint(0x1EA7, cs, &bch[0]);
    return true;
  case 0x1EA8:
    encode_codepoint(0x1EA9, cs, &bch[0]);
    return true;
  case 0x1EAA:
    encode_codepoint(0x1EAB, cs, &bch[0]);
    return true;
  case 0x1EAC:
    encode_codepoint(0x1EAD, cs, &bch[0]);
    return true;
  case 0x1EAE:
    encode_codepoint(0x1EAF, cs, &bch[0]);
    return true;
  case 0x1EB0:
    encode_codepoint(0x1EB1, cs, &bch[0]);
    return true;
  case 0x1EB2:
    encode_codepoint(0x1EB3, cs, &bch[0]);
    return true;
  case 0x1EB4:
    encode_codepoint(0x1EB5, cs, &bch[0]);
    return true;
  case 0x1EB6:
    encode_codepoint(0x1EB7, cs, &bch[0]);
    return true;
  case 0x1EB8:
    encode_codepoint(0x1EB9, cs, &bch[0]);
    return true;
  case 0x1EBA:
    encode_codepoint(0x1EBB, cs, &bch[0]);
    return true;
  case 0x1EBC:
    encode_codepoint(0x1EBD, cs, &bch[0]);
    return true;
  case 0x1EBE:
    encode_codepoint(0x1EBF, cs, &bch[0]);
    return true;
  case 0x1EC0:
    encode_codepoint(0x1EC1, cs, &bch[0]);
    return true;
  case 0x1EC2:
    encode_codepoint(0x1EC3, cs, &bch[0]);
    return true;
  case 0x1EC4:
    encode_codepoint(0x1EC5, cs, &bch[0]);
    return true;
  case 0x1EC6:
    encode_codepoint(0x1EC7, cs, &bch[0]);
    return true;
  case 0x1EC8:
    encode_codepoint(0x1EC9, cs, &bch[0]);
    return true;
  case 0x1ECA:
    encode_codepoint(0x1ECB, cs, &bch[0]);
    return true;
  case 0x1ECC:
    encode_codepoint(0x1ECD, cs, &bch[0]);
    return true;
  case 0x1ECE:
    encode_codepoint(0x1ECF, cs, &bch[0]);
    return true;
  case 0x1ED0:
    encode_codepoint(0x1ED1, cs, &bch[0]);
    return true;
  case 0x1ED2:
    encode_codepoint(0x1ED3, cs, &bch[0]);
    return true;
  case 0x1ED4:
    encode_codepoint(0x1ED5, cs, &bch[0]);
    return true;
  case 0x1ED6:
    encode_codepoint(0x1ED7, cs, &bch[0]);
    return true;
  case 0x1ED8:
    encode_codepoint(0x1ED9, cs, &bch[0]);
    return true;
  case 0x1EDA:
    encode_codepoint(0x1EDB, cs, &bch[0]);
    return true;
  case 0x1EDC:
    encode_codepoint(0x1EDD, cs, &bch[0]);
    return true;
  case 0x1EDE:
    encode_codepoint(0x1EDF, cs, &bch[0]);
    return true;
  case 0x1EE0:
    encode_codepoint(0x1EE1, cs, &bch[0]);
    return true;
  case 0x1EE2:
    encode_codepoint(0x1EE3, cs, &bch[0]);
    return true;
  case 0x1EE4:
    encode_codepoint(0x1EE5, cs, &bch[0]);
    return true;
  case 0x1EE6:
    encode_codepoint(0x1EE7, cs, &bch[0]);
    return true;
  case 0x1EE8:
    encode_codepoint(0x1EE9, cs, &bch[0]);
    return true;
  case 0x1EEA:
    encode_codepoint(0x1EEB, cs, &bch[0]);
    return true;
  case 0x1EEC:
    encode_codepoint(0x1EED, cs, &bch[0]);
    return true;
  case 0x1EEE:
    encode_codepoint(0x1EEF, cs, &bch[0]);
    return true;
  case 0x1EF0:
    encode_codepoint(0x1EF1, cs, &bch[0]);
    return true;
  case 0x1EF2:
    encode_codepoint(0x1EF3, cs, &bch[0]);
    return true;
  case 0x1EF4:
    encode_codepoint(0x1EF5, cs, &bch[0]);
    return true;
  case 0x1EF6:
    encode_codepoint(0x1EF7, cs, &bch[0]);
    return true;
  case 0x1EF8:
    encode_codepoint(0x1EF9, cs, &bch[0]);
    return true;
  case 0x1EFA:
    encode_codepoint(0x1EFB, cs, &bch[0]);
    return true;
  case 0x1EFC:
    encode_codepoint(0x1EFD, cs, &bch[0]);
    return true;
  case 0x1EFE:
    encode_codepoint(0x1EFF, cs, &bch[0]);
    return true;
  case 0x1F08:
    encode_codepoint(0x1F00, cs, &bch[0]);
    return true;
  case 0x1F09:
    encode_codepoint(0x1F01, cs, &bch[0]);
    return true;
  case 0x1F0A:
    encode_codepoint(0x1F02, cs, &bch[0]);
    return true;
  case 0x1F0B:
    encode_codepoint(0x1F03, cs, &bch[0]);
    return true;
  case 0x1F0C:
    encode_codepoint(0x1F04, cs, &bch[0]);
    return true;
  case 0x1F0D:
    encode_codepoint(0x1F05, cs, &bch[0]);
    return true;
  case 0x1F0E:
    encode_codepoint(0x1F06, cs, &bch[0]);
    return true;
  case 0x1F0F:
    encode_codepoint(0x1F07, cs, &bch[0]);
    return true;
  case 0x1F18:
    encode_codepoint(0x1F10, cs, &bch[0]);
    return true;
  case 0x1F19:
    encode_codepoint(0x1F11, cs, &bch[0]);
    return true;
  case 0x1F1A:
    encode_codepoint(0x1F12, cs, &bch[0]);
    return true;
  case 0x1F1B:
    encode_codepoint(0x1F13, cs, &bch[0]);
    return true;
  case 0x1F1C:
    encode_codepoint(0x1F14, cs, &bch[0]);
    return true;
  case 0x1F1D:
    encode_codepoint(0x1F15, cs, &bch[0]);
    return true;
  case 0x1F28:
    encode_codepoint(0x1F20, cs, &bch[0]);
    return true;
  case 0x1F29:
    encode_codepoint(0x1F21, cs, &bch[0]);
    return true;
  case 0x1F2A:
    encode_codepoint(0x1F22, cs, &bch[0]);
    return true;
  case 0x1F2B:
    encode_codepoint(0x1F23, cs, &bch[0]);
    return true;
  case 0x1F2C:
    encode_codepoint(0x1F24, cs, &bch[0]);
    return true;
  case 0x1F2D:
    encode_codepoint(0x1F25, cs, &bch[0]);
    return true;
  case 0x1F2E:
    encode_codepoint(0x1F26, cs, &bch[0]);
    return true;
  case 0x1F2F:
    encode_codepoint(0x1F27, cs, &bch[0]);
    return true;
  case 0x1F38:
    encode_codepoint(0x1F30, cs, &bch[0]);
    return true;
  case 0x1F39:
    encode_codepoint(0x1F31, cs, &bch[0]);
    return true;
  case 0x1F3A:
    encode_codepoint(0x1F32, cs, &bch[0]);
    return true;
  case 0x1F3B:
    encode_codepoint(0x1F33, cs, &bch[0]);
    return true;
  case 0x1F3C:
    encode_codepoint(0x1F34, cs, &bch[0]);
    return true;
  case 0x1F3D:
    encode_codepoint(0x1F35, cs, &bch[0]);
    return true;
  case 0x1F3E:
    encode_codepoint(0x1F36, cs, &bch[0]);
    return true;
  case 0x1F3F:
    encode_codepoint(0x1F37, cs, &bch[0]);
    return true;
  case 0x1F48:
    encode_codepoint(0x1F40, cs, &bch[0]);
    return true;
  case 0x1F49:
    encode_codepoint(0x1F41, cs, &bch[0]);
    return true;
  case 0x1F4A:
    encode_codepoint(0x1F42, cs, &bch[0]);
    return true;
  case 0x1F4B:
    encode_codepoint(0x1F43, cs, &bch[0]);
    return true;
  case 0x1F4C:
    encode_codepoint(0x1F44, cs, &bch[0]);
    return true;
  case 0x1F4D:
    encode_codepoint(0x1F45, cs, &bch[0]);
    return true;
  case 0x1F59:
    encode_codepoint(0x1F51, cs, &bch[0]);
    return true;
  case 0x1F5B:
    encode_codepoint(0x1F53, cs, &bch[0]);
    return true;
  case 0x1F5D:
    encode_codepoint(0x1F55, cs, &bch[0]);
    return true;
  case 0x1F5F:
    encode_codepoint(0x1F57, cs, &bch[0]);
    return true;
  case 0x1F68:
    encode_codepoint(0x1F60, cs, &bch[0]);
    return true;
  case 0x1F69:
    encode_codepoint(0x1F61, cs, &bch[0]);
    return true;
  case 0x1F6A:
    encode_codepoint(0x1F62, cs, &bch[0]);
    return true;
  case 0x1F6B:
    encode_codepoint(0x1F63, cs, &bch[0]);
    return true;
  case 0x1F6C:
    encode_codepoint(0x1F64, cs, &bch[0]);
    return true;
  case 0x1F6D:
    encode_codepoint(0x1F65, cs, &bch[0]);
    return true;
  case 0x1F6E:
    encode_codepoint(0x1F66, cs, &bch[0]);
    return true;
  case 0x1F6F:
    encode_codepoint(0x1F67, cs, &bch[0]);
    return true;
  case 0x1FB8:
    encode_codepoint(0x1FB0, cs, &bch[0]);
    return true;
  case 0x1FB9:
    encode_codepoint(0x1FB1, cs, &bch[0]);
    return true;
  case 0x1FBA:
    encode_codepoint(0x1F70, cs, &bch[0]);
    return true;
  case 0x1FBB:
    encode_codepoint(0x1F71, cs, &bch[0]);
    return true;
  case 0x1FBE:
    encode_codepoint(0x03B9, cs, &bch[0]);
    return true;
  case 0x1FC8:
    encode_codepoint(0x1F72, cs, &bch[0]);
    return true;
  case 0x1FC9:
    encode_codepoint(0x1F73, cs, &bch[0]);
    return true;
  case 0x1FCA:
    encode_codepoint(0x1F74, cs, &bch[0]);
    return true;
  case 0x1FCB:
    encode_codepoint(0x1F75, cs, &bch[0]);
    return true;
  case 0x1FD8:
    encode_codepoint(0x1FD0, cs, &bch[0]);
    return true;
  case 0x1FD9:
    encode_codepoint(0x1FD1, cs, &bch[0]);
    return true;
  case 0x1FDA:
    encode_codepoint(0x1F76, cs, &bch[0]);
    return true;
  case 0x1FDB:
    encode_codepoint(0x1F77, cs, &bch[0]);
    return true;
  case 0x1FE8:
    encode_codepoint(0x1FE0, cs, &bch[0]);
    return true;
  case 0x1FE9:
    encode_codepoint(0x1FE1, cs, &bch[0]);
    return true;
  case 0x1FEA:
    encode_codepoint(0x1F7A, cs, &bch[0]);
    return true;
  case 0x1FEB:
    encode_codepoint(0x1F7B, cs, &bch[0]);
    return true;
  case 0x1FEC:
    encode_codepoint(0x1FE5, cs, &bch[0]);
    return true;
  case 0x1FF8:
    encode_codepoint(0x1F78, cs, &bch[0]);
    return true;
  case 0x1FF9:
    encode_codepoint(0x1F79, cs, &bch[0]);
    return true;
  case 0x1FFA:
    encode_codepoint(0x1F7C, cs, &bch[0]);
    return true;
  case 0x1FFB:
    encode_codepoint(0x1F7D, cs, &bch[0]);
    return true;
  case 0x2126:
    encode_codepoint(0x03C9, cs, &bch[0]);
    return true;
  case 0x212A:
    encode_codepoint(0x006B, cs, &bch[0]);
    return true;
  case 0x212B:
    encode_codepoint(0x00E5, cs, &bch[0]);
    return true;
  case 0x2132:
    encode_codepoint(0x214E, cs, &bch[0]);
    return true;
  case 0x2160:
    encode_codepoint(0x2170, cs, &bch[0]);
    return true;
  case 0x2161:
    encode_codepoint(0x2171, cs, &bch[0]);
    return true;
  case 0x2162:
    encode_codepoint(0x2172, cs, &bch[0]);
    return true;
  case 0x2163:
    encode_codepoint(0x2173, cs, &bch[0]);
    return true;
  case 0x2164:
    encode_codepoint(0x2174, cs, &bch[0]);
    return true;
  case 0x2165:
    encode_codepoint(0x2175, cs, &bch[0]);
    return true;
  case 0x2166:
    encode_codepoint(0x2176, cs, &bch[0]);
    return true;
  case 0x2167:
    encode_codepoint(0x2177, cs, &bch[0]);
    return true;
  case 0x2168:
    encode_codepoint(0x2178, cs, &bch[0]);
    return true;
  case 0x2169:
    encode_codepoint(0x2179, cs, &bch[0]);
    return true;
  case 0x216A:
    encode_codepoint(0x217A, cs, &bch[0]);
    return true;
  case 0x216B:
    encode_codepoint(0x217B, cs, &bch[0]);
    return true;
  case 0x216C:
    encode_codepoint(0x217C, cs, &bch[0]);
    return true;
  case 0x216D:
    encode_codepoint(0x217D, cs, &bch[0]);
    return true;
  case 0x216E:
    encode_codepoint(0x217E, cs, &bch[0]);
    return true;
  case 0x216F:
    encode_codepoint(0x217F, cs, &bch[0]);
    return true;
  case 0x2183:
    encode_codepoint(0x2184, cs, &bch[0]);
    return true;
  case 0x24B6:
    encode_codepoint(0x24D0, cs, &bch[0]);
    return true;
  case 0x24B7:
    encode_codepoint(0x24D1, cs, &bch[0]);
    return true;
  case 0x24B8:
    encode_codepoint(0x24D2, cs, &bch[0]);
    return true;
  case 0x24B9:
    encode_codepoint(0x24D3, cs, &bch[0]);
    return true;
  case 0x24BA:
    encode_codepoint(0x24D4, cs, &bch[0]);
    return true;
  case 0x24BB:
    encode_codepoint(0x24D5, cs, &bch[0]);
    return true;
  case 0x24BC:
    encode_codepoint(0x24D6, cs, &bch[0]);
    return true;
  case 0x24BD:
    encode_codepoint(0x24D7, cs, &bch[0]);
    return true;
  case 0x24BE:
    encode_codepoint(0x24D8, cs, &bch[0]);
    return true;
  case 0x24BF:
    encode_codepoint(0x24D9, cs, &bch[0]);
    return true;
  case 0x24C0:
    encode_codepoint(0x24DA, cs, &bch[0]);
    return true;
  case 0x24C1:
    encode_codepoint(0x24DB, cs, &bch[0]);
    return true;
  case 0x24C2:
    encode_codepoint(0x24DC, cs, &bch[0]);
    return true;
  case 0x24C3:
    encode_codepoint(0x24DD, cs, &bch[0]);
    return true;
  case 0x24C4:
    encode_codepoint(0x24DE, cs, &bch[0]);
    return true;
  case 0x24C5:
    encode_codepoint(0x24DF, cs, &bch[0]);
    return true;
  case 0x24C6:
    encode_codepoint(0x24E0, cs, &bch[0]);
    return true;
  case 0x24C7:
    encode_codepoint(0x24E1, cs, &bch[0]);
    return true;
  case 0x24C8:
    encode_codepoint(0x24E2, cs, &bch[0]);
    return true;
  case 0x24C9:
    encode_codepoint(0x24E3, cs, &bch[0]);
    return true;
  case 0x24CA:
    encode_codepoint(0x24E4, cs, &bch[0]);
    return true;
  case 0x24CB:
    encode_codepoint(0x24E5, cs, &bch[0]);
    return true;
  case 0x24CC:
    encode_codepoint(0x24E6, cs, &bch[0]);
    return true;
  case 0x24CD:
    encode_codepoint(0x24E7, cs, &bch[0]);
    return true;
  case 0x24CE:
    encode_codepoint(0x24E8, cs, &bch[0]);
    return true;
  case 0x24CF:
    encode_codepoint(0x24E9, cs, &bch[0]);
    return true;
  case 0x2C00:
    encode_codepoint(0x2C30, cs, &bch[0]);
    return true;
  case 0x2C01:
    encode_codepoint(0x2C31, cs, &bch[0]);
    return true;
  case 0x2C02:
    encode_codepoint(0x2C32, cs, &bch[0]);
    return true;
  case 0x2C03:
    encode_codepoint(0x2C33, cs, &bch[0]);
    return true;
  case 0x2C04:
    encode_codepoint(0x2C34, cs, &bch[0]);
    return true;
  case 0x2C05:
    encode_codepoint(0x2C35, cs, &bch[0]);
    return true;
  case 0x2C06:
    encode_codepoint(0x2C36, cs, &bch[0]);
    return true;
  case 0x2C07:
    encode_codepoint(0x2C37, cs, &bch[0]);
    return true;
  case 0x2C08:
    encode_codepoint(0x2C38, cs, &bch[0]);
    return true;
  case 0x2C09:
    encode_codepoint(0x2C39, cs, &bch[0]);
    return true;
  case 0x2C0A:
    encode_codepoint(0x2C3A, cs, &bch[0]);
    return true;
  case 0x2C0B:
    encode_codepoint(0x2C3B, cs, &bch[0]);
    return true;
  case 0x2C0C:
    encode_codepoint(0x2C3C, cs, &bch[0]);
    return true;
  case 0x2C0D:
    encode_codepoint(0x2C3D, cs, &bch[0]);
    return true;
  case 0x2C0E:
    encode_codepoint(0x2C3E, cs, &bch[0]);
    return true;
  case 0x2C0F:
    encode_codepoint(0x2C3F, cs, &bch[0]);
    return true;
  case 0x2C10:
    encode_codepoint(0x2C40, cs, &bch[0]);
    return true;
  case 0x2C11:
    encode_codepoint(0x2C41, cs, &bch[0]);
    return true;
  case 0x2C12:
    encode_codepoint(0x2C42, cs, &bch[0]);
    return true;
  case 0x2C13:
    encode_codepoint(0x2C43, cs, &bch[0]);
    return true;
  case 0x2C14:
    encode_codepoint(0x2C44, cs, &bch[0]);
    return true;
  case 0x2C15:
    encode_codepoint(0x2C45, cs, &bch[0]);
    return true;
  case 0x2C16:
    encode_codepoint(0x2C46, cs, &bch[0]);
    return true;
  case 0x2C17:
    encode_codepoint(0x2C47, cs, &bch[0]);
    return true;
  case 0x2C18:
    encode_codepoint(0x2C48, cs, &bch[0]);
    return true;
  case 0x2C19:
    encode_codepoint(0x2C49, cs, &bch[0]);
    return true;
  case 0x2C1A:
    encode_codepoint(0x2C4A, cs, &bch[0]);
    return true;
  case 0x2C1B:
    encode_codepoint(0x2C4B, cs, &bch[0]);
    return true;
  case 0x2C1C:
    encode_codepoint(0x2C4C, cs, &bch[0]);
    return true;
  case 0x2C1D:
    encode_codepoint(0x2C4D, cs, &bch[0]);
    return true;
  case 0x2C1E:
    encode_codepoint(0x2C4E, cs, &bch[0]);
    return true;
  case 0x2C1F:
    encode_codepoint(0x2C4F, cs, &bch[0]);
    return true;
  case 0x2C20:
    encode_codepoint(0x2C50, cs, &bch[0]);
    return true;
  case 0x2C21:
    encode_codepoint(0x2C51, cs, &bch[0]);
    return true;
  case 0x2C22:
    encode_codepoint(0x2C52, cs, &bch[0]);
    return true;
  case 0x2C23:
    encode_codepoint(0x2C53, cs, &bch[0]);
    return true;
  case 0x2C24:
    encode_codepoint(0x2C54, cs, &bch[0]);
    return true;
  case 0x2C25:
    encode_codepoint(0x2C55, cs, &bch[0]);
    return true;
  case 0x2C26:
    encode_codepoint(0x2C56, cs, &bch[0]);
    return true;
  case 0x2C27:
    encode_codepoint(0x2C57, cs, &bch[0]);
    return true;
  case 0x2C28:
    encode_codepoint(0x2C58, cs, &bch[0]);
    return true;
  case 0x2C29:
    encode_codepoint(0x2C59, cs, &bch[0]);
    return true;
  case 0x2C2A:
    encode_codepoint(0x2C5A, cs, &bch[0]);
    return true;
  case 0x2C2B:
    encode_codepoint(0x2C5B, cs, &bch[0]);
    return true;
  case 0x2C2C:
    encode_codepoint(0x2C5C, cs, &bch[0]);
    return true;
  case 0x2C2D:
    encode_codepoint(0x2C5D, cs, &bch[0]);
    return true;
  case 0x2C2E:
    encode_codepoint(0x2C5E, cs, &bch[0]);
    return true;
  case 0x2C60:
    encode_codepoint(0x2C61, cs, &bch[0]);
    return true;
  case 0x2C62:
    encode_codepoint(0x026B, cs, &bch[0]);
    return true;
  case 0x2C63:
    encode_codepoint(0x1D7D, cs, &bch[0]);
    return true;
  case 0x2C64:
    encode_codepoint(0x027D, cs, &bch[0]);
    return true;
  case 0x2C67:
    encode_codepoint(0x2C68, cs, &bch[0]);
    return true;
  case 0x2C69:
    encode_codepoint(0x2C6A, cs, &bch[0]);
    return true;
  case 0x2C6B:
    encode_codepoint(0x2C6C, cs, &bch[0]);
    return true;
  case 0x2C6D:
    encode_codepoint(0x0251, cs, &bch[0]);
    return true;
  case 0x2C6E:
    encode_codepoint(0x0271, cs, &bch[0]);
    return true;
  case 0x2C6F:
    encode_codepoint(0x0250, cs, &bch[0]);
    return true;
  case 0x2C70:
    encode_codepoint(0x0252, cs, &bch[0]);
    return true;
  case 0x2C72:
    encode_codepoint(0x2C73, cs, &bch[0]);
    return true;
  case 0x2C75:
    encode_codepoint(0x2C76, cs, &bch[0]);
    return true;
  case 0x2C7E:
    encode_codepoint(0x023F, cs, &bch[0]);
    return true;
  case 0x2C7F:
    encode_codepoint(0x0240, cs, &bch[0]);
    return true;
  case 0x2C80:
    encode_codepoint(0x2C81, cs, &bch[0]);
    return true;
  case 0x2C82:
    encode_codepoint(0x2C83, cs, &bch[0]);
    return true;
  case 0x2C84:
    encode_codepoint(0x2C85, cs, &bch[0]);
    return true;
  case 0x2C86:
    encode_codepoint(0x2C87, cs, &bch[0]);
    return true;
  case 0x2C88:
    encode_codepoint(0x2C89, cs, &bch[0]);
    return true;
  case 0x2C8A:
    encode_codepoint(0x2C8B, cs, &bch[0]);
    return true;
  case 0x2C8C:
    encode_codepoint(0x2C8D, cs, &bch[0]);
    return true;
  case 0x2C8E:
    encode_codepoint(0x2C8F, cs, &bch[0]);
    return true;
  case 0x2C90:
    encode_codepoint(0x2C91, cs, &bch[0]);
    return true;
  case 0x2C92:
    encode_codepoint(0x2C93, cs, &bch[0]);
    return true;
  case 0x2C94:
    encode_codepoint(0x2C95, cs, &bch[0]);
    return true;
  case 0x2C96:
    encode_codepoint(0x2C97, cs, &bch[0]);
    return true;
  case 0x2C98:
    encode_codepoint(0x2C99, cs, &bch[0]);
    return true;
  case 0x2C9A:
    encode_codepoint(0x2C9B, cs, &bch[0]);
    return true;
  case 0x2C9C:
    encode_codepoint(0x2C9D, cs, &bch[0]);
    return true;
  case 0x2C9E:
    encode_codepoint(0x2C9F, cs, &bch[0]);
    return true;
  case 0x2CA0:
    encode_codepoint(0x2CA1, cs, &bch[0]);
    return true;
  case 0x2CA2:
    encode_codepoint(0x2CA3, cs, &bch[0]);
    return true;
  case 0x2CA4:
    encode_codepoint(0x2CA5, cs, &bch[0]);
    return true;
  case 0x2CA6:
    encode_codepoint(0x2CA7, cs, &bch[0]);
    return true;
  case 0x2CA8:
    encode_codepoint(0x2CA9, cs, &bch[0]);
    return true;
  case 0x2CAA:
    encode_codepoint(0x2CAB, cs, &bch[0]);
    return true;
  case 0x2CAC:
    encode_codepoint(0x2CAD, cs, &bch[0]);
    return true;
  case 0x2CAE:
    encode_codepoint(0x2CAF, cs, &bch[0]);
    return true;
  case 0x2CB0:
    encode_codepoint(0x2CB1, cs, &bch[0]);
    return true;
  case 0x2CB2:
    encode_codepoint(0x2CB3, cs, &bch[0]);
    return true;
  case 0x2CB4:
    encode_codepoint(0x2CB5, cs, &bch[0]);
    return true;
  case 0x2CB6:
    encode_codepoint(0x2CB7, cs, &bch[0]);
    return true;
  case 0x2CB8:
    encode_codepoint(0x2CB9, cs, &bch[0]);
    return true;
  case 0x2CBA:
    encode_codepoint(0x2CBB, cs, &bch[0]);
    return true;
  case 0x2CBC:
    encode_codepoint(0x2CBD, cs, &bch[0]);
    return true;
  case 0x2CBE:
    encode_codepoint(0x2CBF, cs, &bch[0]);
    return true;
  case 0x2CC0:
    encode_codepoint(0x2CC1, cs, &bch[0]);
    return true;
  case 0x2CC2:
    encode_codepoint(0x2CC3, cs, &bch[0]);
    return true;
  case 0x2CC4:
    encode_codepoint(0x2CC5, cs, &bch[0]);
    return true;
  case 0x2CC6:
    encode_codepoint(0x2CC7, cs, &bch[0]);
    return true;
  case 0x2CC8:
    encode_codepoint(0x2CC9, cs, &bch[0]);
    return true;
  case 0x2CCA:
    encode_codepoint(0x2CCB, cs, &bch[0]);
    return true;
  case 0x2CCC:
    encode_codepoint(0x2CCD, cs, &bch[0]);
    return true;
  case 0x2CCE:
    encode_codepoint(0x2CCF, cs, &bch[0]);
    return true;
  case 0x2CD0:
    encode_codepoint(0x2CD1, cs, &bch[0]);
    return true;
  case 0x2CD2:
    encode_codepoint(0x2CD3, cs, &bch[0]);
    return true;
  case 0x2CD4:
    encode_codepoint(0x2CD5, cs, &bch[0]);
    return true;
  case 0x2CD6:
    encode_codepoint(0x2CD7, cs, &bch[0]);
    return true;
  case 0x2CD8:
    encode_codepoint(0x2CD9, cs, &bch[0]);
    return true;
  case 0x2CDA:
    encode_codepoint(0x2CDB, cs, &bch[0]);
    return true;
  case 0x2CDC:
    encode_codepoint(0x2CDD, cs, &bch[0]);
    return true;
  case 0x2CDE:
    encode_codepoint(0x2CDF, cs, &bch[0]);
    return true;
  case 0x2CE0:
    encode_codepoint(0x2CE1, cs, &bch[0]);
    return true;
  case 0x2CE2:
    encode_codepoint(0x2CE3, cs, &bch[0]);
    return true;
  case 0x2CEB:
    encode_codepoint(0x2CEC, cs, &bch[0]);
    return true;
  case 0x2CED:
    encode_codepoint(0x2CEE, cs, &bch[0]);
    return true;
  case 0x2CF2:
    encode_codepoint(0x2CF3, cs, &bch[0]);
    return true;
  case 0xA640:
    encode_codepoint(0xA641, cs, &bch[0]);
    return true;
  case 0xA642:
    encode_codepoint(0xA643, cs, &bch[0]);
    return true;
  case 0xA644:
    encode_codepoint(0xA645, cs, &bch[0]);
    return true;
  case 0xA646:
    encode_codepoint(0xA647, cs, &bch[0]);
    return true;
  case 0xA648:
    encode_codepoint(0xA649, cs, &bch[0]);
    return true;
  case 0xA64A:
    encode_codepoint(0xA64B, cs, &bch[0]);
    return true;
  case 0xA64C:
    encode_codepoint(0xA64D, cs, &bch[0]);
    return true;
  case 0xA64E:
    encode_codepoint(0xA64F, cs, &bch[0]);
    return true;
  case 0xA650:
    encode_codepoint(0xA651, cs, &bch[0]);
    return true;
  case 0xA652:
    encode_codepoint(0xA653, cs, &bch[0]);
    return true;
  case 0xA654:
    encode_codepoint(0xA655, cs, &bch[0]);
    return true;
  case 0xA656:
    encode_codepoint(0xA657, cs, &bch[0]);
    return true;
  case 0xA658:
    encode_codepoint(0xA659, cs, &bch[0]);
    return true;
  case 0xA65A:
    encode_codepoint(0xA65B, cs, &bch[0]);
    return true;
  case 0xA65C:
    encode_codepoint(0xA65D, cs, &bch[0]);
    return true;
  case 0xA65E:
    encode_codepoint(0xA65F, cs, &bch[0]);
    return true;
  case 0xA660:
    encode_codepoint(0xA661, cs, &bch[0]);
    return true;
  case 0xA662:
    encode_codepoint(0xA663, cs, &bch[0]);
    return true;
  case 0xA664:
    encode_codepoint(0xA665, cs, &bch[0]);
    return true;
  case 0xA666:
    encode_codepoint(0xA667, cs, &bch[0]);
    return true;
  case 0xA668:
    encode_codepoint(0xA669, cs, &bch[0]);
    return true;
  case 0xA66A:
    encode_codepoint(0xA66B, cs, &bch[0]);
    return true;
  case 0xA66C:
    encode_codepoint(0xA66D, cs, &bch[0]);
    return true;
  case 0xA680:
    encode_codepoint(0xA681, cs, &bch[0]);
    return true;
  case 0xA682:
    encode_codepoint(0xA683, cs, &bch[0]);
    return true;
  case 0xA684:
    encode_codepoint(0xA685, cs, &bch[0]);
    return true;
  case 0xA686:
    encode_codepoint(0xA687, cs, &bch[0]);
    return true;
  case 0xA688:
    encode_codepoint(0xA689, cs, &bch[0]);
    return true;
  case 0xA68A:
    encode_codepoint(0xA68B, cs, &bch[0]);
    return true;
  case 0xA68C:
    encode_codepoint(0xA68D, cs, &bch[0]);
    return true;
  case 0xA68E:
    encode_codepoint(0xA68F, cs, &bch[0]);
    return true;
  case 0xA690:
    encode_codepoint(0xA691, cs, &bch[0]);
    return true;
  case 0xA692:
    encode_codepoint(0xA693, cs, &bch[0]);
    return true;
  case 0xA694:
    encode_codepoint(0xA695, cs, &bch[0]);
    return true;
  case 0xA696:
    encode_codepoint(0xA697, cs, &bch[0]);
    return true;
  case 0xA698:
    encode_codepoint(0xA699, cs, &bch[0]);
    return true;
  case 0xA69A:
    encode_codepoint(0xA69B, cs, &bch[0]);
    return true;
  case 0xA722:
    encode_codepoint(0xA723, cs, &bch[0]);
    return true;
  case 0xA724:
    encode_codepoint(0xA725, cs, &bch[0]);
    return true;
  case 0xA726:
    encode_codepoint(0xA727, cs, &bch[0]);
    return true;
  case 0xA728:
    encode_codepoint(0xA729, cs, &bch[0]);
    return true;
  case 0xA72A:
    encode_codepoint(0xA72B, cs, &bch[0]);
    return true;
  case 0xA72C:
    encode_codepoint(0xA72D, cs, &bch[0]);
    return true;
  case 0xA72E:
    encode_codepoint(0xA72F, cs, &bch[0]);
    return true;
  case 0xA732:
    encode_codepoint(0xA733, cs, &bch[0]);
    return true;
  case 0xA734:
    encode_codepoint(0xA735, cs, &bch[0]);
    return true;
  case 0xA736:
    encode_codepoint(0xA737, cs, &bch[0]);
    return true;
  case 0xA738:
    encode_codepoint(0xA739, cs, &bch[0]);
    return true;
  case 0xA73A:
    encode_codepoint(0xA73B, cs, &bch[0]);
    return true;
  case 0xA73C:
    encode_codepoint(0xA73D, cs, &bch[0]);
    return true;
  case 0xA73E:
    encode_codepoint(0xA73F, cs, &bch[0]);
    return true;
  case 0xA740:
    encode_codepoint(0xA741, cs, &bch[0]);
    return true;
  case 0xA742:
    encode_codepoint(0xA743, cs, &bch[0]);
    return true;
  case 0xA744:
    encode_codepoint(0xA745, cs, &bch[0]);
    return true;
  case 0xA746:
    encode_codepoint(0xA747, cs, &bch[0]);
    return true;
  case 0xA748:
    encode_codepoint(0xA749, cs, &bch[0]);
    return true;
  case 0xA74A:
    encode_codepoint(0xA74B, cs, &bch[0]);
    return true;
  case 0xA74C:
    encode_codepoint(0xA74D, cs, &bch[0]);
    return true;
  case 0xA74E:
    encode_codepoint(0xA74F, cs, &bch[0]);
    return true;
  case 0xA750:
    encode_codepoint(0xA751, cs, &bch[0]);
    return true;
  case 0xA752:
    encode_codepoint(0xA753, cs, &bch[0]);
    return true;
  case 0xA754:
    encode_codepoint(0xA755, cs, &bch[0]);
    return true;
  case 0xA756:
    encode_codepoint(0xA757, cs, &bch[0]);
    return true;
  case 0xA758:
    encode_codepoint(0xA759, cs, &bch[0]);
    return true;
  case 0xA75A:
    encode_codepoint(0xA75B, cs, &bch[0]);
    return true;
  case 0xA75C:
    encode_codepoint(0xA75D, cs, &bch[0]);
    return true;
  case 0xA75E:
    encode_codepoint(0xA75F, cs, &bch[0]);
    return true;
  case 0xA760:
    encode_codepoint(0xA761, cs, &bch[0]);
    return true;
  case 0xA762:
    encode_codepoint(0xA763, cs, &bch[0]);
    return true;
  case 0xA764:
    encode_codepoint(0xA765, cs, &bch[0]);
    return true;
  case 0xA766:
    encode_codepoint(0xA767, cs, &bch[0]);
    return true;
  case 0xA768:
    encode_codepoint(0xA769, cs, &bch[0]);
    return true;
  case 0xA76A:
    encode_codepoint(0xA76B, cs, &bch[0]);
    return true;
  case 0xA76C:
    encode_codepoint(0xA76D, cs, &bch[0]);
    return true;
  case 0xA76E:
    encode_codepoint(0xA76F, cs, &bch[0]);
    return true;
  case 0xA779:
    encode_codepoint(0xA77A, cs, &bch[0]);
    return true;
  case 0xA77B:
    encode_codepoint(0xA77C, cs, &bch[0]);
    return true;
  case 0xA77D:
    encode_codepoint(0x1D79, cs, &bch[0]);
    return true;
  case 0xA77E:
    encode_codepoint(0xA77F, cs, &bch[0]);
    return true;
  case 0xA780:
    encode_codepoint(0xA781, cs, &bch[0]);
    return true;
  case 0xA782:
    encode_codepoint(0xA783, cs, &bch[0]);
    return true;
  case 0xA784:
    encode_codepoint(0xA785, cs, &bch[0]);
    return true;
  case 0xA786:
    encode_codepoint(0xA787, cs, &bch[0]);
    return true;
  case 0xA78B:
    encode_codepoint(0xA78C, cs, &bch[0]);
    return true;
  case 0xA78D:
    encode_codepoint(0x0265, cs, &bch[0]);
    return true;
  case 0xA790:
    encode_codepoint(0xA791, cs, &bch[0]);
    return true;
  case 0xA792:
    encode_codepoint(0xA793, cs, &bch[0]);
    return true;
  case 0xA796:
    encode_codepoint(0xA797, cs, &bch[0]);
    return true;
  case 0xA798:
    encode_codepoint(0xA799, cs, &bch[0]);
    return true;
  case 0xA79A:
    encode_codepoint(0xA79B, cs, &bch[0]);
    return true;
  case 0xA79C:
    encode_codepoint(0xA79D, cs, &bch[0]);
    return true;
  case 0xA79E:
    encode_codepoint(0xA79F, cs, &bch[0]);
    return true;
  case 0xA7A0:
    encode_codepoint(0xA7A1, cs, &bch[0]);
    return true;
  case 0xA7A2:
    encode_codepoint(0xA7A3, cs, &bch[0]);
    return true;
  case 0xA7A4:
    encode_codepoint(0xA7A5, cs, &bch[0]);
    return true;
  case 0xA7A6:
    encode_codepoint(0xA7A7, cs, &bch[0]);
    return true;
  case 0xA7A8:
    encode_codepoint(0xA7A9, cs, &bch[0]);
    return true;
  case 0xA7AA:
    encode_codepoint(0x0266, cs, &bch[0]);
    return true;
  case 0xA7AB:
    encode_codepoint(0x025C, cs, &bch[0]);
    return true;
  case 0xA7AC:
    encode_codepoint(0x0261, cs, &bch[0]);
    return true;
  case 0xA7AD:
    encode_codepoint(0x026C, cs, &bch[0]);
    return true;
  case 0xA7B0:
    encode_codepoint(0x029E, cs, &bch[0]);
    return true;
  case 0xA7B1:
    encode_codepoint(0x0287, cs, &bch[0]);
    return true;
  case 0xFF21:
    encode_codepoint(0xFF41, cs, &bch[0]);
    return true;
  case 0xFF22:
    encode_codepoint(0xFF42, cs, &bch[0]);
    return true;
  case 0xFF23:
    encode_codepoint(0xFF43, cs, &bch[0]);
    return true;
  case 0xFF24:
    encode_codepoint(0xFF44, cs, &bch[0]);
    return true;
  case 0xFF25:
    encode_codepoint(0xFF45, cs, &bch[0]);
    return true;
  case 0xFF26:
    encode_codepoint(0xFF46, cs, &bch[0]);
    return true;
  case 0xFF27:
    encode_codepoint(0xFF47, cs, &bch[0]);
    return true;
  case 0xFF28:
    encode_codepoint(0xFF48, cs, &bch[0]);
    return true;
  case 0xFF29:
    encode_codepoint(0xFF49, cs, &bch[0]);
    return true;
  case 0xFF2A:
    encode_codepoint(0xFF4A, cs, &bch[0]);
    return true;
  case 0xFF2B:
    encode_codepoint(0xFF4B, cs, &bch[0]);
    return true;
  case 0xFF2C:
    encode_codepoint(0xFF4C, cs, &bch[0]);
    return true;
  case 0xFF2D:
    encode_codepoint(0xFF4D, cs, &bch[0]);
    return true;
  case 0xFF2E:
    encode_codepoint(0xFF4E, cs, &bch[0]);
    return true;
  case 0xFF2F:
    encode_codepoint(0xFF4F, cs, &bch[0]);
    return true;
  case 0xFF30:
    encode_codepoint(0xFF50, cs, &bch[0]);
    return true;
  case 0xFF31:
    encode_codepoint(0xFF51, cs, &bch[0]);
    return true;
  case 0xFF32:
    encode_codepoint(0xFF52, cs, &bch[0]);
    return true;
  case 0xFF33:
    encode_codepoint(0xFF53, cs, &bch[0]);
    return true;
  case 0xFF34:
    encode_codepoint(0xFF54, cs, &bch[0]);
    return true;
  case 0xFF35:
    encode_codepoint(0xFF55, cs, &bch[0]);
    return true;
  case 0xFF36:
    encode_codepoint(0xFF56, cs, &bch[0]);
    return true;
  case 0xFF37:
    encode_codepoint(0xFF57, cs, &bch[0]);
    return true;
  case 0xFF38:
    encode_codepoint(0xFF58, cs, &bch[0]);
    return true;
  case 0xFF39:
    encode_codepoint(0xFF59, cs, &bch[0]);
    return true;
  case 0xFF3A:
    encode_codepoint(0xFF5A, cs, &bch[0]);
    return true;
  }
  bch[0].ucs4.value=0xffffffff;
  return false;
}

bool
casefold_full(uint32_t cp, charset cs, binary_character_t* bch) {
  bch[1].ucs4.value = 0xffffffff;
  bch[2].ucs4.value = 0xffffffff;
  switch (cp) {
  case 0x00DF:
    encode_codepoint(0x0073, cs, &bch[0]);
    encode_codepoint(0x0073, cs, &bch[1]);
    return true;
  case 0x0130:
    encode_codepoint(0x0069, cs, &bch[0]);
    encode_codepoint(0x0307, cs, &bch[1]);
    return true;
  case 0x0149:
    encode_codepoint(0x02BC, cs, &bch[0]);
    encode_codepoint(0x006E, cs, &bch[1]);
    return true;
  case 0x01F0:
    encode_codepoint(0x006A, cs, &bch[0]);
    encode_codepoint(0x030C, cs, &bch[1]);
    return true;
  case 0x0390:
    encode_codepoint(0x03B9, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0301, cs, &bch[2]);
    return true;
  case 0x03B0:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0301, cs, &bch[2]);
    return true;
  case 0x0587:
    encode_codepoint(0x0565, cs, &bch[0]);
    encode_codepoint(0x0582, cs, &bch[1]);
    return true;
  case 0x1E96:
    encode_codepoint(0x0068, cs, &bch[0]);
    encode_codepoint(0x0331, cs, &bch[1]);
    return true;
  case 0x1E97:
    encode_codepoint(0x0074, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    return true;
  case 0x1E98:
    encode_codepoint(0x0077, cs, &bch[0]);
    encode_codepoint(0x030A, cs, &bch[1]);
    return true;
  case 0x1E99:
    encode_codepoint(0x0079, cs, &bch[0]);
    encode_codepoint(0x030A, cs, &bch[1]);
    return true;
  case 0x1E9A:
    encode_codepoint(0x0061, cs, &bch[0]);
    encode_codepoint(0x02BE, cs, &bch[1]);
    return true;
  case 0x1E9E:
    encode_codepoint(0x0073, cs, &bch[0]);
    encode_codepoint(0x0073, cs, &bch[1]);
    return true;
  case 0x1F50:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0313, cs, &bch[1]);
    return true;
  case 0x1F52:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0313, cs, &bch[1]);
    encode_codepoint(0x0300, cs, &bch[2]);
    return true;
  case 0x1F54:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0313, cs, &bch[1]);
    encode_codepoint(0x0301, cs, &bch[2]);
    return true;
  case 0x1F56:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0313, cs, &bch[1]);
    encode_codepoint(0x0342, cs, &bch[2]);
    return true;
  case 0x1F80:
    encode_codepoint(0x1F00, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F81:
    encode_codepoint(0x1F01, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F82:
    encode_codepoint(0x1F02, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F83:
    encode_codepoint(0x1F03, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F84:
    encode_codepoint(0x1F04, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F85:
    encode_codepoint(0x1F05, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F86:
    encode_codepoint(0x1F06, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F87:
    encode_codepoint(0x1F07, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F88:
    encode_codepoint(0x1F00, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F89:
    encode_codepoint(0x1F01, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8A:
    encode_codepoint(0x1F02, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8B:
    encode_codepoint(0x1F03, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8C:
    encode_codepoint(0x1F04, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8D:
    encode_codepoint(0x1F05, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8E:
    encode_codepoint(0x1F06, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F8F:
    encode_codepoint(0x1F07, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F90:
    encode_codepoint(0x1F20, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F91:
    encode_codepoint(0x1F21, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F92:
    encode_codepoint(0x1F22, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F93:
    encode_codepoint(0x1F23, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F94:
    encode_codepoint(0x1F24, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F95:
    encode_codepoint(0x1F25, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F96:
    encode_codepoint(0x1F26, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F97:
    encode_codepoint(0x1F27, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F98:
    encode_codepoint(0x1F20, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F99:
    encode_codepoint(0x1F21, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9A:
    encode_codepoint(0x1F22, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9B:
    encode_codepoint(0x1F23, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9C:
    encode_codepoint(0x1F24, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9D:
    encode_codepoint(0x1F25, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9E:
    encode_codepoint(0x1F26, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1F9F:
    encode_codepoint(0x1F27, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA0:
    encode_codepoint(0x1F60, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA1:
    encode_codepoint(0x1F61, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA2:
    encode_codepoint(0x1F62, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA3:
    encode_codepoint(0x1F63, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA4:
    encode_codepoint(0x1F64, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA5:
    encode_codepoint(0x1F65, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA6:
    encode_codepoint(0x1F66, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA7:
    encode_codepoint(0x1F67, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA8:
    encode_codepoint(0x1F60, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FA9:
    encode_codepoint(0x1F61, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAA:
    encode_codepoint(0x1F62, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAB:
    encode_codepoint(0x1F63, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAC:
    encode_codepoint(0x1F64, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAD:
    encode_codepoint(0x1F65, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAE:
    encode_codepoint(0x1F66, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FAF:
    encode_codepoint(0x1F67, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FB2:
    encode_codepoint(0x1F70, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FB3:
    encode_codepoint(0x03B1, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FB4:
    encode_codepoint(0x03AC, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FB6:
    encode_codepoint(0x03B1, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    return true;
  case 0x1FB7:
    encode_codepoint(0x03B1, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    encode_codepoint(0x03B9, cs, &bch[2]);
    return true;
  case 0x1FBC:
    encode_codepoint(0x03B1, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FC2:
    encode_codepoint(0x1F74, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FC3:
    encode_codepoint(0x03B7, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FC4:
    encode_codepoint(0x03AE, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FC6:
    encode_codepoint(0x03B7, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    return true;
  case 0x1FC7:
    encode_codepoint(0x03B7, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    encode_codepoint(0x03B9, cs, &bch[2]);
    return true;
  case 0x1FCC:
    encode_codepoint(0x03B7, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FD2:
    encode_codepoint(0x03B9, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0300, cs, &bch[2]);
    return true;
  case 0x1FD3:
    encode_codepoint(0x03B9, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0301, cs, &bch[2]);
    return true;
  case 0x1FD6:
    encode_codepoint(0x03B9, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    return true;
  case 0x1FD7:
    encode_codepoint(0x03B9, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0342, cs, &bch[2]);
    return true;
  case 0x1FE2:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0300, cs, &bch[2]);
    return true;
  case 0x1FE3:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0301, cs, &bch[2]);
    return true;
  case 0x1FE4:
    encode_codepoint(0x03C1, cs, &bch[0]);
    encode_codepoint(0x0313, cs, &bch[1]);
    return true;
  case 0x1FE6:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    return true;
  case 0x1FE7:
    encode_codepoint(0x03C5, cs, &bch[0]);
    encode_codepoint(0x0308, cs, &bch[1]);
    encode_codepoint(0x0342, cs, &bch[2]);
    return true;
  case 0x1FF2:
    encode_codepoint(0x1F7C, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FF3:
    encode_codepoint(0x03C9, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FF4:
    encode_codepoint(0x03CE, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0x1FF6:
    encode_codepoint(0x03C9, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    return true;
  case 0x1FF7:
    encode_codepoint(0x03C9, cs, &bch[0]);
    encode_codepoint(0x0342, cs, &bch[1]);
    encode_codepoint(0x03B9, cs, &bch[2]);
    return true;
  case 0x1FFC:
    encode_codepoint(0x03C9, cs, &bch[0]);
    encode_codepoint(0x03B9, cs, &bch[1]);
    return true;
  case 0xFB00:
    encode_codepoint(0x0066, cs, &bch[0]);
    encode_codepoint(0x0066, cs, &bch[1]);
    return true;
  case 0xFB01:
    encode_codepoint(0x0066, cs, &bch[0]);
    encode_codepoint(0x0069, cs, &bch[1]);
    return true;
  case 0xFB02:
    encode_codepoint(0x0066, cs, &bch[0]);
    encode_codepoint(0x006C, cs, &bch[1]);
    return true;
  case 0xFB03:
    encode_codepoint(0x0066, cs, &bch[0]);
    encode_codepoint(0x0066, cs, &bch[1]);
    encode_codepoint(0x0069, cs, &bch[2]);
    return true;
  case 0xFB04:
    encode_codepoint(0x0066, cs, &bch[0]);
    encode_codepoint(0x0066, cs, &bch[1]);
    encode_codepoint(0x006C, cs, &bch[2]);
    return true;
  case 0xFB05:
    encode_codepoint(0x0073, cs, &bch[0]);
    encode_codepoint(0x0074, cs, &bch[1]);
    return true;
  case 0xFB06:
    encode_codepoint(0x0073, cs, &bch[0]);
    encode_codepoint(0x0074, cs, &bch[1]);
    return true;
  case 0xFB13:
    encode_codepoint(0x0574, cs, &bch[0]);
    encode_codepoint(0x0576, cs, &bch[1]);
    return true;
  case 0xFB14:
    encode_codepoint(0x0574, cs, &bch[0]);
    encode_codepoint(0x0565, cs, &bch[1]);
    return true;
  case 0xFB15:
    encode_codepoint(0x0574, cs, &bch[0]);
    encode_codepoint(0x056B, cs, &bch[1]);
    return true;
  case 0xFB16:
    encode_codepoint(0x057E, cs, &bch[0]);
    encode_codepoint(0x0576, cs, &bch[1]);
    return true;
  case 0xFB17:
    encode_codepoint(0x0574, cs, &bch[0]);
    encode_codepoint(0x056D, cs, &bch[1]);
    return true;
  }
  bch[0].ucs4.value=0xffffffff;
  return false;
}

bool
casefold_simple(uint32_t cp, charset cs, binary_character_t* bch) {
  bch[1].ucs4.value = 0xffffffff;
  bch[2].ucs4.value = 0xffffffff;
  switch (cp) {
  case 0x1E9E:
    encode_codepoint(0x00DF, cs, &bch[0]);
    return true;
  case 0x1F88:
    encode_codepoint(0x1F80, cs, &bch[0]);
    return true;
  case 0x1F89:
    encode_codepoint(0x1F81, cs, &bch[0]);
    return true;
  case 0x1F8A:
    encode_codepoint(0x1F82, cs, &bch[0]);
    return true;
  case 0x1F8B:
    encode_codepoint(0x1F83, cs, &bch[0]);
    return true;
  case 0x1F8C:
    encode_codepoint(0x1F84, cs, &bch[0]);
    return true;
  case 0x1F8D:
    encode_codepoint(0x1F85, cs, &bch[0]);
    return true;
  case 0x1F8E:
    encode_codepoint(0x1F86, cs, &bch[0]);
    return true;
  case 0x1F8F:
    encode_codepoint(0x1F87, cs, &bch[0]);
    return true;
  case 0x1F98:
    encode_codepoint(0x1F90, cs, &bch[0]);
    return true;
  case 0x1F99:
    encode_codepoint(0x1F91, cs, &bch[0]);
    return true;
  case 0x1F9A:
    encode_codepoint(0x1F92, cs, &bch[0]);
    return true;
  case 0x1F9B:
    encode_codepoint(0x1F93, cs, &bch[0]);
    return true;
  case 0x1F9C:
    encode_codepoint(0x1F94, cs, &bch[0]);
    return true;
  case 0x1F9D:
    encode_codepoint(0x1F95, cs, &bch[0]);
    return true;
  case 0x1F9E:
    encode_codepoint(0x1F96, cs, &bch[0]);
    return true;
  case 0x1F9F:
    encode_codepoint(0x1F97, cs, &bch[0]);
    return true;
  case 0x1FA8:
    encode_codepoint(0x1FA0, cs, &bch[0]);
    return true;
  case 0x1FA9:
    encode_codepoint(0x1FA1, cs, &bch[0]);
    return true;
  case 0x1FAA:
    encode_codepoint(0x1FA2, cs, &bch[0]);
    return true;
  case 0x1FAB:
    encode_codepoint(0x1FA3, cs, &bch[0]);
    return true;
  case 0x1FAC:
    encode_codepoint(0x1FA4, cs, &bch[0]);
    return true;
  case 0x1FAD:
    encode_codepoint(0x1FA5, cs, &bch[0]);
    return true;
  case 0x1FAE:
    encode_codepoint(0x1FA6, cs, &bch[0]);
    return true;
  case 0x1FAF:
    encode_codepoint(0x1FA7, cs, &bch[0]);
    return true;
  case 0x1FBC:
    encode_codepoint(0x1FB3, cs, &bch[0]);
    return true;
  case 0x1FCC:
    encode_codepoint(0x1FC3, cs, &bch[0]);
    return true;
  case 0x1FFC:
    encode_codepoint(0x1FF3, cs, &bch[0]);
    return true;
  }
  bch[0].ucs4.value=0xffffffff;
  return false;
}

bool
casefold_special(uint32_t cp, charset cs, binary_character_t* bch) {
  bch[1].ucs4.value = 0xffffffff;
  bch[2].ucs4.value = 0xffffffff;
  switch (cp) {
  case 0x0049:
    encode_codepoint(0x0131, cs, &bch[0]);
    return true;
  case 0x0130:
    encode_codepoint(0x0069, cs, &bch[0]);
    return true;
  }
  bch[0].ucs4.value=0xffffffff;
  return false;
}

