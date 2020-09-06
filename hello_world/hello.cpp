#include "hello.decl.h"

CProxy_Main mainProxy;
constexpr int nElem = 8;

class Main : public CBase_Main {
	public:
		Main (CkArgMsg* m) {
			CkPrintf("Running Hello on %d Processors with %d elements.\n", CkNumPes(), nElem);
			CProxy_Hello arr = CProxy_Hello :: ckNew(nElem);
			mianProxy = thisProxy;
			arr[0].sayHi(0);
		};
		
		void done() {
			CkPrintf("All done.\n");
			CkExit();
		};
};

class Hello : public CBase_hello {
	public:
		Hello() {}
		void SayHi() {
			CkPrintf("PE %d says : Hellow World from element %d.\n", ckMyPe(), thisIndex);
			if(thisIndex < nElem - 1) {
				thisProxy[thisIndex + 1].SayHi();
			}
			else {
				mainProxy.done();
			}
		}
};
