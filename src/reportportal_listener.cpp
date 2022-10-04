// Let Catch provide the required interfaces
#define CATCH_CONFIG_EXTERNAL_INTERFACES

#include <catch2/catch.hpp>
#include <iostream>

// -----------------------------------------------------------------------
// 1. Printing of listener data:
//

namespace reportportal {

std::string ws(int const level) {
    return std::string( 2 * level, ' ' );
}

template< typename T >
std::ostream& operator<<( std::ostream& os, std::vector<T> const& v ) {
    os << "{ ";
    for ( const auto& x : v )
        os << x << ", ";
    return os << "}";
}

// struct SourceLineInfo {
//     char const* file;
//     std::size_t line;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::SourceLineInfo const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- file: " << info.file << "\n"
       << ws(level+1) << "- line: " << info.line << "\n";
}

//struct MessageInfo {
//    std::string macroName;
//    std::string message;
//    SourceLineInfo lineInfo;
//    ResultWas::OfType type;
//    unsigned int sequence;
//};

void print( std::ostream& os, int const level, Catch::MessageInfo const& info ) {
    os << ws(level+1) << "- macroName: '" << info.macroName << "'\n"
       << ws(level+1) << "- message '"    << info.message   << "'\n";
    print( os,level+1  , "- lineInfo", info.lineInfo );
    os << ws(level+1) << "- sequence "    << info.sequence  << "\n";
}

void print( std::ostream& os, int const level, std::string const& title, std::vector<Catch::MessageInfo> const& v ) {
    os << ws(level  ) << title << ":\n";
    for ( const auto& x : v )
    {
        os << ws(level+1) << "{\n";
        print( os, level+2, x );
        os << ws(level+1) << "}\n";
    }
//    os << ws(level+1) << "\n";
}

// struct TestRunInfo {
//     std::string name;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::TestRunInfo const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- name: " << info.name << "\n";
}

// struct Counts {
//     std::size_t total() const;
//     bool allPassed() const;
//     bool allOk() const;
//
//     std::size_t passed = 0;
//     std::size_t failed = 0;
//     std::size_t failedButOk = 0;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::Counts const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- total(): "     << info.total()     << "\n"
       << ws(level+1) << "- allPassed(): " << info.allPassed() << "\n"
       << ws(level+1) << "- allOk(): "     << info.allOk()     << "\n"
       << ws(level+1) << "- passed: "      << info.passed      << "\n"
       << ws(level+1) << "- failed: "      << info.failed      << "\n"
       << ws(level+1) << "- failedButOk: " << info.failedButOk << "\n";
}

// struct Totals {
//     Counts assertions;
//     Counts testCases;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::Totals const& info ) {
    os << ws(level) << title << ":\n";
    print( os, level+1, "- assertions", info.assertions );
    print( os, level+1, "- testCases" , info.testCases  );
}

// struct TestRunStats {
//     TestRunInfo runInfo;
//     Totals totals;
//     bool aborting;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::TestRunStats const& info ) {
    os << ws(level) << title << ":\n";
    print( os, level+1 , "- runInfo", info.runInfo );
    print( os, level+1 , "- totals" , info.totals  );
    os << ws(level+1) << "- aborting: " << info.aborting << "\n";
}

// struct TestCaseInfo {
//     enum SpecialProperties{
//         None = 0,
//         IsHidden = 1 << 1,
//         ShouldFail = 1 << 2,
//         MayFail = 1 << 3,
//         Throws = 1 << 4,
//         NonPortable = 1 << 5,
//         Benchmark = 1 << 6
//     };
//
//     bool isHidden() const;
//     bool throws() const;
//     bool okToFail() const;
//     bool expectedToFail() const;
//
//     std::string tagsAsString() const;
//
//     std::string name;
//     std::string className;
//     std::string description;
//     std::vector<std::string> tags;
//     std::vector<std::string> lcaseTags;
//     SourceLineInfo lineInfo;
//     SpecialProperties properties;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::TestCaseInfo const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- isHidden(): "       << info.isHidden() << "\n"
       << ws(level+1) << "- throws(): "         << info.throws() << "\n"
       << ws(level+1) << "- okToFail(): "       << info.okToFail() << "\n"
       << ws(level+1) << "- expectedToFail(): " << info.expectedToFail() << "\n"
       << ws(level+1) << "- tagsAsString(): '"  << info.tagsAsString() << "'\n"
       << ws(level+1) << "- name: '"            << info.name << "'\n"
       << ws(level+1) << "- className: '"       << info.className << "'\n"
       << ws(level+1) << "- description: '"     << info.description << "'\n"
       << ws(level+1) << "- tags: "             << info.tags << "\n"
       << ws(level+1) << "- lcaseTags: "        << info.lcaseTags << "\n";
    print( os, level+1 , "- lineInfo", info.lineInfo );
    os << ws(level+1) << "- properties (flags): 0x" << std::hex << info.properties << std::dec << "\n";
}

// struct TestCaseStats {
//     TestCaseInfo testInfo;
//     Totals totals;
//     std::string stdOut;
//     std::string stdErr;
//     bool aborting;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::TestCaseStats const& info ) {
    os << ws(level  ) << title << ":\n";
    print( os, level+1 , "- testInfo", info.testInfo );
    print( os, level+1 , "- totals"  , info.totals   );
    os << ws(level+1) << "- stdOut: "   << info.stdOut << "\n"
       << ws(level+1) << "- stdErr: "   << info.stdErr << "\n"
       << ws(level+1) << "- aborting: " << info.aborting << "\n";
}

// struct SectionInfo {
//     std::string name;
//     std::string description;
//     SourceLineInfo lineInfo;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::SectionInfo const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- name: "         << info.name << "\n";
    print( os, level+1 , "- lineInfo", info.lineInfo );
}

// struct SectionStats {
//     SectionInfo sectionInfo;
//     Counts assertions;
//     double durationInSeconds;
//     bool missingAssertions;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::SectionStats const& info ) {
    os << ws(level  ) << title << ":\n";
    print( os, level+1 , "- sectionInfo", info.sectionInfo );
    print( os, level+1 , "- assertions" , info.assertions );
    os << ws(level+1) << "- durationInSeconds: " << info.durationInSeconds << "\n"
       << ws(level+1) << "- missingAssertions: " << info.missingAssertions << "\n";
}

// struct AssertionInfo
// {
//     StringRef macroName;
//     SourceLineInfo lineInfo;
//     StringRef capturedExpression;
//     ResultDisposition::Flags resultDisposition;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::AssertionInfo const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- macroName: '"  << info.macroName << "'\n";
    print( os, level+1 , "- lineInfo" , info.lineInfo );
    os << ws(level+1) << "- capturedExpression: '" << info.capturedExpression << "'\n"
       << ws(level+1) << "- resultDisposition (flags): 0x" << std::hex << info.resultDisposition  << std::dec << "\n";
}

//struct AssertionResultData
//{
//    std::string reconstructExpression() const;
//
//    std::string message;
//    mutable std::string reconstructedExpression;
//    LazyExpression lazyExpression;
//    ResultWas::OfType resultType;
//};

void print( std::ostream& os, int const level, std::string const& title, Catch::AssertionResultData const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- reconstructExpression(): '" <<   info.reconstructExpression() << "'\n"
       << ws(level+1) << "- message: '"                 <<   info.message << "'\n"
       << ws(level+1) << "- lazyExpression: '"          << "(info.lazyExpression)" << "'\n"
       << ws(level+1) << "- resultType: '"              <<   info.resultType << "'\n";
}

//class AssertionResult {
//    bool isOk() const;
//    bool succeeded() const;
//    ResultWas::OfType getResultType() const;
//    bool hasExpression() const;
//    bool hasMessage() const;
//    std::string getExpression() const;
//    std::string getExpressionInMacro() const;
//    bool hasExpandedExpression() const;
//    std::string getExpandedExpression() const;
//    std::string getMessage() const;
//    SourceLineInfo getSourceInfo() const;
//    std::string getTestMacroName() const;
//
//    AssertionInfo m_info;
//    AssertionResultData m_resultData;
//};

void print( std::ostream& os, int const level, std::string const& title, Catch::AssertionResult const& info ) {
    os << ws(level  ) << title << ":\n"
       << ws(level+1) << "- isOk(): "  << info.isOk() << "\n"
       << ws(level+1) << "- succeeded(): "  << info.succeeded() << "\n"
       << ws(level+1) << "- getResultType(): "  << info.getResultType() << "\n"
       << ws(level+1) << "- hasExpression(): "  << info.hasExpression() << "\n"
       << ws(level+1) << "- hasMessage(): "  << info.hasMessage() << "\n"
       << ws(level+1) << "- getExpression(): '"  << info.getExpression() << "'\n"
       << ws(level+1) << "- getExpressionInMacro(): '"  << info.getExpressionInMacro()  << "'\n"
       << ws(level+1) << "- hasExpandedExpression(): "  << info.hasExpandedExpression() << "\n"
       << ws(level+1) << "- getExpandedExpression(): "  << info.getExpandedExpression() << "'\n"
       << ws(level+1) << "- getMessage(): '"  << info.getMessage() << "'\n";
    print( os, level+1 , "- getSourceInfo(): ", info.getSourceInfo() );
    os << ws(level+1) << "- getTestMacroName(): '"  << info.getTestMacroName() << "'\n";

//    print( os, level+1 , "- *** m_info (AssertionInfo)", info.m_info );
//    print( os, level+1 , "- *** m_resultData (AssertionResultData)", info.m_resultData );
}

// struct AssertionStats {
//     AssertionResult assertionResult;
//     std::vector<MessageInfo> infoMessages;
//     Totals totals;
// };

void print( std::ostream& os, int const level, std::string const& title, Catch::AssertionStats const& info ) {
    os << ws(level  ) << title << ":\n";
    print( os, level+1 , "- assertionResult", info.assertionResult );
    print( os, level+1 , "- infoMessages", info.infoMessages );
    print( os, level+1 , "- totals", info.totals );
}

// -----------------------------------------------------------------------
// 2. My listener and registration:
//

char const * dashed_line =
    "--------------------------------------------------------------------------";

struct reportportal_listener : Catch::TestEventListenerBase {

    using TestEventListenerBase::TestEventListenerBase; // inherit constructor

    // Get rid of Wweak-tables
    ~reportportal_listener();

    // The whole test run starting
    void testRunStarting( Catch::TestRunInfo const& testRunInfo ) override {
        _launch = std::make_unique<report_portal::launch>(_service, "Catch2 Test Launch");
        _launch->set_description("This is a test launch for catch2 tests.");

        _launch->start(std::chrono::high_resolution_clock::now());

        std::unique_ptr<report_portal::test_item> suite = std::make_unique<report_portal::test_item>(*_launch, testRunInfo.name);
        suite->start(std::chrono::high_resolution_clock::now());
        _test_item_stack.push_back(std::move(suite));
    }

    // The whole test run ending
    void testRunEnded( Catch::TestRunStats const& testRunStats ) override {
        std::unique_ptr<report_portal::test_item>& suite = _test_item_stack.back();

        // [TODO] should aborting signal interrupted status or is that caught earlier?
        suite->end(std::chrono::high_resolution_clock::now());
        _test_item_stack.pop_back();

        _launch->end(std::chrono::high_resolution_clock::now());
        _launch.reset();

        std::cout
            << dashed_line
            << "\nEvent: testRunEnded:\n";
        print( std::cout, 1, "- testRunStats", testRunStats );
    }

    // A test is being skipped (because it is "hidden")
    void skipTest( Catch::TestCaseInfo const& testInfo ) override {
        // [TODO]
//        std::cout
//            << dashed_line
//            << "\nEvent: skipTest:\n";
//        print( std::cout, 1, "- testInfo", testInfo );
    }

    // Test cases starting
    void testCaseStarting(const Catch::TestCaseInfo& test_info ) override {
        std::unique_ptr<report_portal::test_item>& test_suite = _test_item_stack.back();

        std::unique_ptr<report_portal::test_item> test =
            std::make_unique<report_portal::test_item>(*test_suite, test_info.name, report_portal::test_item_type::test);

        test->set_description(
            "description = " + test_info.description + "\n"
            "tags = " + test_info.tagsAsString() + "\n"
            "file = " + test_info.lineInfo.file + "\n"
            "line = " + std::to_string(test_info.lineInfo.line) + "\n");

        test->start(std::chrono::high_resolution_clock::now());
        _test_item_stack.push_back(std::move(test));
    }

    // Test cases ending
    void testCaseEnded(const Catch::TestCaseStats& test_case_stats) override {
        std::unique_ptr<report_portal::test_item>& test = _test_item_stack.back();

        test->end(std::chrono::high_resolution_clock::now());
        _test_item_stack.pop_back();
    }

    // Sections starting
    void sectionStarting(const Catch::SectionInfo& section_info ) override {
        std::unique_ptr<report_portal::test_item>& test = _test_item_stack.back();

        std::unique_ptr<report_portal::test_item> section =
            std::make_unique<report_portal::test_item>(*test, section_info.name, report_portal::test_item_type::scenario);

        section->set_description(
            "file = " + section_info.lineInfo.file + "\n"
            "line = " + std::to_string(section_info.lineInfo.line) + "\n");

        section->start(std::chrono::high_resolution_clock::now());
        _test_item_stack.push_back(std::move(section));
    }

    // Sections ending
    void sectionEnded(const Catch::SectionStats& section_stats) override {
        std::unique_ptr<report_portal::test_item>& section = _test_item_stack.back();

        section->end(std::chrono::high_resolution_clock::now());
        _test_item_stack.pop_back();
    }

    // Assertions before/ after
    void assertionStarting(const Catch::AssertionInfo& assertion_info) override {
        std::unique_ptr<report_portal::test_item>& section = _test_item_stack.back();

        const std::string name = assertion_info.name + "( " + assertion_info.capturedExpression + " )";
        std::unique_ptr<report_portal::test_item> assertion =
            std::make_unique<report_portal::test_item>(*section, name, report_portal::test_item_type::step);

        assertion->set_description(
            "file = " + assertion_info.lineInfo.file + "\n"
            "line = " + std::to_string(assertion_info.lineInfo.line) + "\n");

        assertion->start(std::chrono::high_resolution_clock::now());
        _test_item_stack.push_back(std::move(section));
    }

    bool assertionEnded(const Catch::AssertionStats& assertion_stats) override {
        std::unique_ptr<report_portal::test_item>& assertion = _test_item_stack.back();

        report_portal::test_item_status status = report_portal::test_item_status::skipped;
        const ::testing::TestResult* test_result = test_info.result();
        if (test_result) {
            if (test_result->Passed()) {
                status = report_portal::test_item_status::passed;
            } else {
                status = report_portal::test_item_status::failed;
            }

            for (int i = 0; i < test_result->total_part_count(); ++i) {
                const ::testing::TestPartResult& test_part_result = test_result->GetTestPartResult(i);

                const std::string file_name = char_to_string(test_part_result.file_name());
                const std::string line_number = std::to_string(test_part_result.line_number());
                const std::string summary = char_to_string(test_part_result.summary());
                const std::string message = char_to_string(test_part_result.message());

                const std::string detailed_log =
                    "file = " + file_name + "\n"
                    "line = " + line_number + "\n" + summary;
                test->log(std::chrono::high_resolution_clock::now(), report_portal::log_level::error, detailed_log);
            }
        }

        test->end(std::chrono::high_resolution_clock::now(), status);
        _test_item_stack.pop_back();
    }
};

// Get rid of Wweak-tables
reportportal_listener::~reportportal_listener() {}

}

CATCH_REGISTER_LISTENER(reportportal::reportportal_listener)

