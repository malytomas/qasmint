#include <cage-core/debug.h>
#include <cage-core/macros.h>
#include <cage-core/string.h>
#include <qasm/qasm.h>

using namespace qasm;

#define CAGE_TESTCASE(NAME) CAGE_LOG(SeverityEnum::Info, "testcase", stringizer() + fill(string(), CageTestCase::counter * 4, ' ') + NAME); CageTestCase CAGE_JOIN(cageTestCase_, __LINE__);
#define CAGE_TEST(COND,...) { if (!(COND)) CAGE_THROW_CRITICAL(Exception, CAGE_STRINGIZE(COND)); }
#define CAGE_TEST_THROWN(COND,...) { bool ok = false; { CAGE_LOG(SeverityEnum::Info, "exception", "awaiting exception"); ::cage::detail::OverrideBreakpoint OverrideBreakpoint; try { COND; } catch (...) { ok = true; } } if (!ok) { CAGE_LOG(SeverityEnum::Info, "exception", "caught no exception"); CAGE_THROW_CRITICAL(Exception, CAGE_STRINGIZE(COND)); } else { CAGE_LOG(SeverityEnum::Info, "exception", "the exception was expected"); } }
#ifdef CAGE_ASSERT_ENABLED
#define CAGE_TEST_ASSERTED(COND,...) { ::cage::detail::OverrideAssert overrideAssert; CAGE_TEST_THROWN(COND); }
#else
#define CAGE_TEST_ASSERTED(COND,...) {}
#endif

struct CageTestCase : private Immovable
{
	static uint32 counter;
	CageTestCase()
	{
		counter++;
	}
	~CageTestCase()
	{
		counter--;
	}
};
