#include <cstdlib>
#include <string>
#include "test_macros.h"

int main() {

    //TODO absolute paths I guess...
    std::string boost_options(" --log_level=all");
#if TEST_BASE
    system((std::string("tests/base/test_z_qtshapes_base") + boost_options).c_str());
#endif
#if TEST_QPOINT
    system((std::string("tests/qpoint/test_z_qtshapes_qpoint") + boost_options).c_str());
#endif
#if TEST_QPOINTF
    system((std::string("tests/qpointf/test_z_qtshapes_qpointf") + boost_options).c_str());
#endif
#if TEST_QLINE
    system((std::string("tests/qline/test_z_qtshapes_qline_1") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_2") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_3") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_4") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_5") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_6") + boost_options).c_str());
    system((std::string("tests/qline/test_z_qtshapes_qline_7") + boost_options).c_str());
#endif
#if TEST_QLINEF
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_1") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_2") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_3") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_4") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_5") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_6") + boost_options).c_str());
    system((std::string("tests/qlinef/test_z_qtshapes_qlinef_7") + boost_options).c_str());
#endif
#if TEST_QTRI
    system((std::string("tests/qtri/test_z_qtshapes_qtri_1") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_2") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_3") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_4") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_5") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_6") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_7") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_8") + boost_options).c_str());
    system((std::string("tests/qtri/test_z_qtshapes_qtri_9") + boost_options).c_str());
#endif
#if TEST_QTRIF
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_1") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_2") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_3") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_4") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_5") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_6") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_7") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_8") + boost_options).c_str());
    system((std::string("tests/qtrif/test_z_qtshapes_qtrif_9") + boost_options).c_str());
#endif
#if TEST_QRECT
    system((std::string("tests/qrect/test_z_qtshapes_qrect_1") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_2") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_3") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_4") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_5") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_6") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_7") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_8") + boost_options).c_str());
    system((std::string("tests/qrect/test_z_qtshapes_qrect_9") + boost_options).c_str());
#endif
#if TEST_QRECTF
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_1") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_2") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_3") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_4") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_5") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_6") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_7") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_8") + boost_options).c_str());
    system((std::string("tests/qrectf/test_z_qtshapes_qrectf_9") + boost_options).c_str());
#endif
#if TEST_QELLIPSE
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_1") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_2") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_3") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_4") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_5") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_6") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_7") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_8") + boost_options).c_str());
    system((std::string("tests/qellipse/test_z_qtshapes_qellipse_9") + boost_options).c_str());
#endif
#if TEST_QELLIPSEF
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_1") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_2") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_3") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_4") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_5") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_6") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_7") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_8") + boost_options).c_str());
    system((std::string("tests/qellipsef/test_z_qtshapes_qellipsef_9") + boost_options).c_str());
#endif
#if TEST_LINALG
    system((std::string("tests/linalg/test_z_linalg") + boost_options).c_str());
    system((std::string("tests/linalg/test_z_matrix") + boost_options).c_str());
    system((std::string("tests/linalg/test_z_offsetmatrix") + boost_options).c_str());
    system((std::string("tests/linalg/test_z_matrixtraits") + boost_options).c_str());
#endif

    return 0;
}
