#pragma once
#include "../DataStructures/List.h"
namespace gfm 
{
	class ListUnitTest {
		static bool AllTests() {
			return TrivialTest();
		}

		static bool TrivialTest() {
			gfm::List<char> l1;
			gfm::List<unsigned char> l2;
			gfm::List<short> l3;
			gfm::List<unsigned short> l4;
			gfm::List<int> l5;
			gfm::List<unsigned int> l6;
			gfm::List<long> l7;
			gfm::List<unsigned long> l8;
			gfm::List<long long> l9;
			gfm::List<unsigned long long> l10;
			gfm::List<float> l10;
			gfm::List<double> l11;
			gfm::List<long double> l12;
			struct PODTEST {
				int g[5];
			};
			gfm::List<PODTEST> l13;
			class PODTEST2 {
			public:
				int g[10];
				char m[255];
				double z;
			};
			gfm::List<PODTEST2> l14;
			return l1.ISTRIVIAL && l2.ISTRIVIAL && l3.ISTRIVIAL &&
				l4.ISTRIVIAL && l5.ISTRIVIAL && l6.ISTRIVIAL &&
				l9.ISTRIVIAL && l8.ISTRIVIAL && l7.ISTRIVIAL &&
				l10.ISTRIVIAL && l11.ISTRIVIAL && l12.ISTRIVIAL &&
				l13.ISTRIVIAL && l14.ISTRIVIAL;
		}
	};
}//gfm