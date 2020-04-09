long switch1(long *p1, long *p2, long action)
{
long result = 0;
switch(action) {
case 27:
 *p2 = *p1;
 result = *p2;
 break;
case 25:
 *p1 += *p2;
 result = *p1;
 break;
case 29:
case 30:
 *p1 -= 59;
 *p2 -= *p1;
 break;
case 23:
 *p1 += 60;
case 21:
 result = *p2;
 result *= result;
 break;
case 31:
 result = *p2;
 result >>= *p1;
 break;
default:
 result = 12;
 result <<= 3;
}
 return result;
}
