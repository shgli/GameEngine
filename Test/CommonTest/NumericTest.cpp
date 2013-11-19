#if 0
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameEngineTest
#include <boost/test/unit_test.hpp>
#include "Common/Common.h"
BOOST_AUTO_TEST_CASE(MainTest)
{
}

#include <iostream>
BOOST_AUTO_TEST_SUITE(BitsViewTest)
BOOST_AUTO_TEST_CASE(BitsViewToString)
{
	Int16 ExponentSize = 11;
	Int16 MASK = (((1<<15) - 1) / (1 << (15 - ExponentSize))) << ( 15 - ExponentSize);
	BOOST_CHECK_EQUAL(MASK.ComplementalCode().ToString(sizeof(Int16)),"7ff0");
	//BOOST_CHECK_EQUAL(MASK.ComplementalCode().ToString(),"7f f0");

	ExponentSize = 8;
	MASK = (((1<<15) - 1) / (1 << (15 - ExponentSize))) << ( 15 - ExponentSize);
	BOOST_CHECK_EQUAL(MASK.ComplementalCode().ToString(sizeof(Int16)),"7f80");
	//BOOST_CHECK_EQUAL(MASK.ComplementalCode().ToString(),"7f 80");
	//

	Int64 M1 = 0x000fffffffffffff;
	std::cout<<std::hex<<M1.value<<std::endl;
	BOOST_CHECK_EQUAL(M1.ToString(),"000f ffff ffff ffff");

	Int16 FractionSize = 23;
	M1 = (1 << FractionSize) - 1;
	BOOST_CHECK_EQUAL(M1.ComplementalCode().ToString(sizeof(Int32)),"007f ffff");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UInt8Test)
BOOST_AUTO_TEST_CASE(UInt8Constructor)
{
	UInt8 i = 2;
	BOOST_CHECK_EQUAL(i , 2);
}

BOOST_AUTO_TEST_CASE(UInt8SelfOperator)
{
	UInt8 i = 8;

	//operator ++
	++i;
	BOOST_CHECK(i == 9);
	i++;
	BOOST_CHECK(i == 10);
	BOOST_CHECK((++i) == 11);
	BOOST_CHECK((i++) == 11);
	BOOST_CHECK(i == 12);

	//operator --
	--i;
	BOOST_CHECK(i == 11);
	i--;
	BOOST_CHECK(i == 10);
	BOOST_CHECK((--i) == 9);
	BOOST_CHECK((i--) == 9);
	BOOST_CHECK(i == 8);

	//operator += -= *= /= %=
	i += 4;
	BOOST_CHECK(i == 12);

	i -= 5;
	BOOST_CHECK(i == 7);
	i *= 8;
	BOOST_CHECK(i == 56);
	i /= 4;
	BOOST_CHECK(i == 14);
	i %= 3;
	BOOST_CHECK(i == 2);

	i += UInt8(2);
	BOOST_CHECK(i == 4);

	i += Int32(3);
	BOOST_CHECK(i == 7);

	i += 2.3;
	BOOST_CHECK(i == 9);

	i += Double(2.9);
	BOOST_CHECK(i == 11);
}

BOOST_AUTO_TEST_CASE(UInt8Operator)
{
	UInt8 i = 4,j = 5;
	BOOST_CHECK((i + j) == 9);
	BOOST_CHECK((j - i) == 1);
	BOOST_CHECK((i * j) == 20);
	BOOST_CHECK((i / j) == 0);
	BOOST_CHECK((j / i) == 1);
	BOOST_CHECK((j % i) == 1);
	BOOST_CHECK((i % j) == 4);
}

BOOST_AUTO_TEST_CASE(UInt8Size)
{
	BOOST_CHECK(sizeof(UInt8) == 1);

	UInt8 i = 3;
	BOOST_CHECK(i.Size() == 1);
}

BOOST_AUTO_TEST_CASE(UInt8PDT)
{
	char c = 'e';
	UInt8 i = 2;
	std::memcpy(&i,&c,sizeof(char));
	BOOST_CHECK_EQUAL(i,'e');
}

BOOST_AUTO_TEST_CASE(UInt8TrueCode)
{
	//positive
	UInt8 n1 = 23;
	BOOST_CHECK_EQUAL(n1.TrueCode().ToString(sizeof(UInt8)),"17");
	//inpositive
	Int8 n2 = -23;
	BOOST_CHECK_EQUAL(n2.TrueCode().ToString(sizeof(Int8)),"97");

	//0
	UInt32 n = 0;
	BOOST_CHECK_EQUAL(n.TrueCode().ToString(sizeof(UInt32)),"0000 0000");

	//-0
	//Int32 zero=-0;
	//BOOST_CHECK_EQUAL(zero.TrueCode().ToString(sizeof(Int32)),"1000 0000");
}

BOOST_AUTO_TEST_CASE(UInt8OnesComplementalCode)
{
	//positive
	UInt8 n1 = 23;
	BOOST_CHECK_EQUAL(n1.OnesComplementalCode().ToString(sizeof(UInt8)),"17");
	//inpositive
	Int8 n2 = -23;
	BOOST_CHECK_EQUAL(n2.OnesComplementalCode().ToString(sizeof(Int8)),"e8");

	//0
	UInt32 n = 0;
	BOOST_CHECK_EQUAL(n.OnesComplementalCode().ToString(sizeof(UInt32)),"0000 0000");

	//-0
	//Int8 zero = -0;
	//BOOST_CHECK_EQUAL(zero.OnesComplementalCode().ToString(sizeof(Int8)),"ff");
}

BOOST_AUTO_TEST_CASE(UInt8ComplementalCode)
{
	//positive
	UInt8 n1 = 23;
	BOOST_CHECK_EQUAL(n1.ComplementalCode().ToString(sizeof(UInt8)),"17");
	//inpositive
	Int8 n2 = -23;
	BOOST_CHECK_EQUAL(n2.ComplementalCode().ToString(sizeof(Int8)),"e9");

	//0
	UInt32 n = 0;
	BOOST_CHECK_EQUAL(n.ComplementalCode().ToString(sizeof(UInt32)),"0000 0000");

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FloatTest)
BOOST_AUTO_TEST_CASE(FloatSize)
{
	BOOST_CHECK_EQUAL(sizeof(Float),4);
}

BOOST_AUTO_TEST_CASE(FloatPDT)
{
	float f = 3.4f;
	Float ff = 0.0f;
	std::memcpy(&ff,&f,sizeof(f));
	BOOST_CHECK_EQUAL(ff,3.4f);
}

BOOST_AUTO_TEST_CASE(OperatorLessThan)
{
	// F < F
	Float ff1 = 2.4f,ff2 = 2.3f;
	BOOST_CHECK(ff2 < ff1);

	// f < F
	float f = 1.2f;
	BOOST_CHECK(f < ff1);

	//F < f
	float f1 = 3.5;
	BOOST_CHECK(ff1 < f1);

	//F < d
	double d1 = 3.6;
	BOOST_CHECK(ff1 < d1);

	//d < F
	double d2 = 1.1;
	BOOST_CHECK(d2 < ff1);
}

BOOST_AUTO_TEST_CASE(OperatorLessEqual)
{
	//F <= F
	Float ff1 = -1.2f,ff2 = 1.3f,ff3 = -1.2f;
	BOOST_CHECK(ff1 <= ff2);
	BOOST_CHECK(ff1 <= ff3);

	//F <= f
	float f1 = 1.3f,f2 = -1.2f;
	BOOST_CHECK(ff1 <= f1);
	BOOST_CHECK(ff1 <= f2);

	//F <= d
	double d1 = 1.3,d2 = -1.2;
	BOOST_CHECK(ff1 <= d1);
	BOOST_CHECK(ff1 <= d2);

	//f <= F
	BOOST_CHECK(f1 <= ff2);
	BOOST_CHECK(f2 <= ff2);

	//d <= F
	BOOST_CHECK(d1 <= ff2);
	BOOST_CHECK(d2 <= ff2);
}

BOOST_AUTO_TEST_CASE(OperatorGreatThan)
{
	//F > F
	Float ff1 = 1.4f,ff2=1.3f;
	BOOST_CHECK(ff1 > ff2);

	//F > f
	float f = 1.3f;
	BOOST_CHECK(ff1 > f);

	//F > d
	double d = 1.3;
	BOOST_CHECK(ff1 > d);

	//f > F
	float f1 = 1.5f;
	BOOST_CHECK(f1 > ff1);

	//d > F
	double d1 = 1.5;
	BOOST_CHECK(d1 > ff1);
}

BOOST_AUTO_TEST_CASE(OperatorGreatEqual)
{
	//F >= F
	Float ff1 = 1.2f,ff2 = 1.1f,ff3 = 1.2f;
	BOOST_CHECK(ff1 >= ff2);
	BOOST_CHECK(ff1 >= ff3);

	//F >= f
	float f1 = 1.1f,f2 = 1.2f;
	BOOST_CHECK(ff1 >= f1);
	BOOST_CHECK(ff1 >= f2);

	//F >= d
	double d1 = 1.1,d2 = 1.2;
	BOOST_CHECK(ff1 >= d1);
	BOOST_CHECK(ff1 >= d2);

	//f >= F
	float f3 = 1.3f;
	BOOST_CHECK(f3 >= ff1);
	BOOST_CHECK(f2 >= ff1);

	//d >= F
	double d3 = 1.3;
	BOOST_CHECK(d3 >= ff1);
	BOOST_CHECK(d2 >= ff1);
}
BOOST_AUTO_TEST_CASE(FloatExponent)
{
	Float d = 2.5f; 
	Int16 nExponent = d.Exponent();
	BOOST_CHECK_EQUAL(nExponent,1);

	Float d1 = -1.2f;
	nExponent = d1.Exponent();
	BOOST_CHECK_EQUAL(0,nExponent);
}

BOOST_AUTO_TEST_CASE(FloatFraction)
{
	Float d = 2.5f;
	Int32 nFraction = d.Fraction();
	BOOST_CHECK_EQUAL(nFraction.ToString(),"0020 0000");

	Float d1 = -1.2f;
	nFraction = d1.Fraction();
	BOOST_CHECK_EQUAL(nFraction.ToString(),"0019 999a");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DoubleTest)
BOOST_AUTO_TEST_CASE(DoubleSize)
{
	BOOST_CHECK_EQUAL(sizeof(Double),8);
}

BOOST_AUTO_TEST_CASE(DoublePDT)
{
	double f = 3.4;
	Double ff = 0.0;
	std::memcpy(&ff,&f,sizeof(f));
	BOOST_CHECK_EQUAL(ff,3.4);
}

BOOST_AUTO_TEST_CASE(DoubleLessThan)
{
	//D < D
	Double dd1 = -1.2,dd2 = -1.1;
	BOOST_CHECK(dd1 < dd2);

	//D < d
	double d1 = -1.1;
	BOOST_CHECK(dd1 < d1);

	//D < f
	float f1 = -1.1f;
	BOOST_CHECK(dd1 < f1);

	//d < D
	Double dd3 = 1.0;
	BOOST_CHECK(d1 < dd3);

	//f < D
	BOOST_CHECK(f1 < dd3);
}

BOOST_AUTO_TEST_CASE(DoubleLessEqual)
{
	//D <= D
	Double dd1 = 1.2,dd2 = 1.5,dd3 = 1.2;
	BOOST_CHECK(dd1 <= dd2);
	BOOST_CHECK(dd1 <= dd3);

	//D <= d
	double d1 = 1.5,d2 = 1.2;
	BOOST_CHECK(dd1 <= d1);
	BOOST_CHECK(dd1 <= d2);

	//D <= f
	float f1 = 1.5f,f2 = 1.2f;
	BOOST_CHECK(dd1 <= f1);
	BOOST_CHECK(dd1 <= f2);

	//d <= D
	BOOST_CHECK(d1 <= dd2);
	BOOST_CHECK(d2 <= dd2);

	//f <= D
	BOOST_CHECK(f1 <= dd2);
	BOOST_CHECK(f2 <= dd2);
}

BOOST_AUTO_TEST_CASE(DoubleGreatThan)
{
	//D > D
	Double dd1 = 1.3,dd2 = 0.9;
	BOOST_CHECK(dd1 > dd2);

	//D > d
	double d = 0.9;
	BOOST_CHECK(dd1 > d);

	//D > f
	float f = 0.9;
	BOOST_CHECK(dd1 > f);

	//d > D
	double d1 = 1.3;
	BOOST_CHECK(d1 > dd2);

	//f > D
	float f1 = 1.3;
	BOOST_CHECK(f1 > dd2);
}

BOOST_AUTO_TEST_CASE(DoubleGreatEqual)
{
	//D >= D
	Double dd1 = 1.1,dd2 = 0.8,dd3 = 1.1;
	BOOST_CHECK(dd1 >= dd2);
	BOOST_CHECK(dd1 >= dd3);

	//D >= d
	double d1 = 0.8, d2 = 1.1;
	BOOST_CHECK(dd1 >= d1);
	BOOST_CHECK(dd1 >= d2);

	//D >= f
	float f1 = 0.8,f2 = 1.1;
	BOOST_CHECK(dd1 >= f1);
	BOOST_CHECK(dd1 >= f2);

	//d >= D
	BOOST_CHECK(d2 >= dd2);
	BOOST_CHECK(d1 >= dd2);

	//f >= D
	BOOST_CHECK(f2 >= dd2);
	BOOST_CHECK(f1 >= dd2);
}

BOOST_AUTO_TEST_CASE(DoubleExponent)
{
	Double d = 2.5; 
	Int16 nExponent = d.Exponent();
	BOOST_CHECK_EQUAL(nExponent,1);

	Double d1 = -1.2;
	nExponent = d1.Exponent();
	BOOST_CHECK_EQUAL(0,nExponent);
}

BOOST_AUTO_TEST_CASE(DoubleFraction)
{
	Double d = 2.5;
	Int64 nFraction = d.Fraction();
	BOOST_CHECK_EQUAL(nFraction.ToString(),"0004 0000 0000 0000");

	Double d1 = -1.2;
	nFraction = d1.Fraction();
	BOOST_CHECK_EQUAL(nFraction.ToString(),"0003 3333 3333 3333");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FloatDoubleOp)
BOOST_AUTO_TEST_CASE(FloatDoubleLessThan)
{
	//F < D
	Float ff1 = -1.2f,ff2 = 1.2f;
	Double dd1 = -1.2,dd2 = 1.2;
	BOOST_CHECK(ff1 < dd2);

	//D < F
	BOOST_CHECK(dd1 < ff2);

}

BOOST_AUTO_TEST_CASE(FloatDoubleLessEqual)
{
	//F <= D
	Float ff1 = -1.2f,ff2 = 1.2f;
	Double dd1 = -1.2,dd2 = 1.2;
	BOOST_CHECK(ff1 <= dd2);
	BOOST_CHECK(ff1 <= dd1);

	//D <= F
	BOOST_CHECK(dd1 < ff2);
	BOOST_CHECK(dd1 <= ff1);
}

BOOST_AUTO_TEST_CASE(FloatDoubleGreatThan)
{
	//F > D
	Float ff1 = 1.2f,ff2 = 1.1f;
	Double dd1 = 1.2,dd2 = 1.1;
	BOOST_CHECK(ff1 > dd2);

	//D > F
	BOOST_CHECK(dd1 > ff2);
}

BOOST_AUTO_TEST_CASE(FloatDoubleGreatEqual)
{
	//F >= D
	Float ff1 = 1.2f,ff2 = 1.1f;
	Double dd1 = 1.2,dd2 = 1.1;
	BOOST_CHECK(ff1 >= dd1);
	BOOST_CHECK(ff1 >= dd2);

	//D >= F
	BOOST_CHECK(dd1 >= ff1);
	BOOST_CHECK(dd1 >= ff2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ArithmeticOp)
BOOST_AUTO_TEST_CASE(IntAddOther)
{
	Int32 n1 = 2;
	BOOST_CHECK_EQUAL(n1 + UInt8(2),4);
	BOOST_CHECK_EQUAL(UInt8(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + UInt16(2),4);
	BOOST_CHECK_EQUAL(UInt16(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + UInt64(2),4);
	BOOST_CHECK_EQUAL(UInt64(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + Float(2.1),4.1);
	BOOST_CHECK_EQUAL(Float(2.1) + n1,4.1);

	BOOST_CHECK_EQUAL(n1 + Double(2.3),4.3);
	BOOST_CHECK_EQUAL(Double(2.1) + n1,4.1);

	BOOST_CHECK_EQUAL(n1 + uint8_t(2),4);
	BOOST_CHECK_EQUAL(uint8_t(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + uint16_t(2),4);
	BOOST_CHECK_EQUAL(uint16_t(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + uint64_t(2),4);
	BOOST_CHECK_EQUAL(uint64_t(2) + n1,4);

	BOOST_CHECK_EQUAL(n1 + float(2.1),4.1);
	BOOST_CHECK_EQUAL(float(2.1) + n1,4.1);

	BOOST_CHECK_EQUAL(n1 + double(2.3),4.3);
	BOOST_CHECK_EQUAL(double(2.1) + n1,4.1);
}

BOOST_AUTO_TEST_CASE(IntSubOther)
{
	Int32 n1 = 2;
	BOOST_CHECK_EQUAL(n1 - UInt8(2),0);
	BOOST_CHECK_EQUAL(UInt8(1) - n1,-1);

	BOOST_CHECK_EQUAL(n1 - UInt16(2),0);
	BOOST_CHECK_EQUAL(UInt16(1) - n1,-1);

	BOOST_CHECK_EQUAL(n1 - UInt64(2),0);
	BOOST_CHECK_EQUAL(UInt64(7) - n1,5);

	BOOST_CHECK_EQUAL(n1 - Float(2.1),-0.1);
	BOOST_CHECK_EQUAL(Float(2.1) - n1,0.1);

	BOOST_CHECK_EQUAL(n1 - Double(2.3),-0.3);
	BOOST_CHECK_EQUAL(Double(2.1) - n1,0.1);

	BOOST_CHECK_EQUAL(n1 - uint8_t(2),0);
	BOOST_CHECK_EQUAL(uint8_t(5) - n1,3);

	BOOST_CHECK_EQUAL(n1 - uint16_t(1),1);
	BOOST_CHECK_EQUAL(uint16_t(2) - n1,0);

	BOOST_CHECK_EQUAL(n1 - uint64_t(1),1);
	BOOST_CHECK_EQUAL(uint64_t(2) - n1,0);

	BOOST_CHECK_EQUAL(n1 - float(2.1),-0.1);
	BOOST_CHECK_EQUAL(float(2.1) - n1,0.1);

	BOOST_CHECK_EQUAL(n1 - double(2.3),-0.3);
	BOOST_CHECK_EQUAL(double(2.1) - n1,0.1);
}

BOOST_AUTO_TEST_CASE(IntMultiOther)
{
	Int32 n1 = 2;
	BOOST_CHECK_EQUAL(n1 * UInt8(2),4);
	BOOST_CHECK_EQUAL(UInt8(1) * n1,2);

	BOOST_CHECK_EQUAL(n1 * UInt16(2),4);
	BOOST_CHECK_EQUAL(UInt16(1) * n1,2);

	BOOST_CHECK_EQUAL(n1 * UInt64(2),4);
	BOOST_CHECK_EQUAL(UInt64(7) * n1,14);

	BOOST_CHECK_EQUAL(n1 * Float(2.1),4.2);
	BOOST_CHECK_EQUAL(Float(2.1) * n1,4.2);

	BOOST_CHECK_EQUAL(n1 * Double(2.3),4.6);
	BOOST_CHECK_EQUAL(Double(2.1) * n1,4.2);

	BOOST_CHECK_EQUAL(n1 * uint8_t(2),4);
	BOOST_CHECK_EQUAL(uint8_t(5) * n1,10);

	BOOST_CHECK_EQUAL(n1 * uint16_t(1),2);
	BOOST_CHECK_EQUAL(uint16_t(2) * n1,4);

	BOOST_CHECK_EQUAL(n1 * uint64_t(1),2);
	BOOST_CHECK_EQUAL(uint64_t(2) * n1,4);

	BOOST_CHECK_EQUAL(n1 * float(2.1),4.2);
	BOOST_CHECK_EQUAL(float(2.1) * n1,4.2);

	BOOST_CHECK_EQUAL(n1 * double(2.3),4.6);
	BOOST_CHECK_EQUAL(double(2.1) * n1,4.2);
}

BOOST_AUTO_TEST_CASE(IntDivideOther)
{
	Int32 n1 = 2;
	BOOST_CHECK_EQUAL(n1 / UInt8(2),1);
	BOOST_CHECK_EQUAL(UInt8(1) / n1,0);

	BOOST_CHECK_EQUAL(n1 / UInt16(2),1);
	BOOST_CHECK_EQUAL(UInt16(1) / n1,0);

	BOOST_CHECK_EQUAL(n1 / UInt64(2),1);
	BOOST_CHECK_EQUAL(UInt64(7) / n1,3);

	BOOST_CHECK_EQUAL(n1 / Float(2.1),2 / 2.1);
	BOOST_CHECK_EQUAL(Float(2.1) / n1,1.05);

	BOOST_CHECK_EQUAL(n1 / Double(2.3),2 / 2.3);
	BOOST_CHECK_EQUAL(Double(2.1) / n1,1.05);

	BOOST_CHECK_EQUAL(n1 / uint8_t(2),1);
	BOOST_CHECK_EQUAL(uint8_t(5) / n1,2);

	BOOST_CHECK_EQUAL(n1 / uint16_t(1),2);
	BOOST_CHECK_EQUAL(uint16_t(2) / n1,1);

	BOOST_CHECK_EQUAL(n1 / uint64_t(1),2);
	BOOST_CHECK_EQUAL(uint64_t(2) / n1,1);

	BOOST_CHECK_EQUAL(n1 / float(2.1),2 / 2.1);
	BOOST_CHECK_EQUAL(float(2.1) / n1,1.05);

	BOOST_CHECK_EQUAL(n1 / double(2.3),2 / 2.3);
	BOOST_CHECK_EQUAL(double(2.1) / n1,1.05);
}

BOOST_AUTO_TEST_CASE(ModBitwise)
{
	Int32 n1 = 38;
	Int8 n2 = 49;

	Int16 n3 = n1 % n2;
	Int16 n4 = n2 % n1;
	BOOST_CHECK_EQUAL(38,n3);
	BOOST_CHECK_EQUAL(n4,11);

	//Test &
	n3 = n1 & n2;
	n4 = n2 & n1;
	BOOST_CHECK_EQUAL(n3,32);
	BOOST_CHECK_EQUAL(n4,32);

	//Test | 
	n3 = n1 | n2;
	n4 = n2 | n1;
	BOOST_CHECK_EQUAL(n3,55);
	BOOST_CHECK_EQUAL(n4,55);

	//Test ^
	n3 = n1 ^ n2;
	n4 = n2 ^ n1;
	BOOST_CHECK_EQUAL(n3,23);
	BOOST_CHECK_EQUAL(n4,23);
}

BOOST_AUTO_TEST_CASE(PrecisionTest)
{
	Float f = 1.0e-6;

	BOOST_CHECK_EQUAL(f,0.0);
}

BOOST_AUTO_TEST_SUITE_END()

#endif

