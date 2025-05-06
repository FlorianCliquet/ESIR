#include <iostream>
#include "mixage/filtre/compression.hpp"
#include "mixage/filtre/echo.hpp"
#include "mixage/filtre/fade_in.hpp"
#include "mixage/filtre/fade_out.hpp"
#include "mixage/filtre/panning.hpp"
#include "mixage/producteur/lecteur_fichier.hpp"
#include "mixage/producteur/signal_constant.hpp"
#include "mixage/utils/constantes.hpp"
#include "mixage/utils/enregistreur_fichier_texte.hpp"
#include "mixage/producteur/harmonique.hpp"
#include "mixage/filtre/multiplicateur.hpp"
#include "mixage/filtre/operation_binaire.hpp"
#include "mixage/utils/enregistreur_fichier.hpp"
#include "mixage/filtre/volume.hpp"
#include "mixage/filtre/mixeur.hpp"

#include "qtest.hpp"

void QTest::Q2() {
    std::cout << "Q2: Test signal_constant class\n";
    signal_constant cst(4.0);
    enregistreur_fichier_texte enregistreur("../out/q2.txt", 1);
    enregistreur.connecterEntree(cst.getSortie(0), 0);
    for (char i = 0; i < 50; ++i) {
        cst.calculer();
        enregistreur.calculer();
    }
    std::cout << "Q2 done\n";
}

void QTest::Q5() {
    std::cout << "Q5: Test harmonique class\n";
    harmonique la(440, 0);
    enregistreur_fichier_texte enregistreur("../out/q5.raw", 1);
    enregistreur.connecterEntree(la.getSortie(0), 0);
    for (unsigned int i = 0; i < 2 * MixageSonore::frequency; ++i) {
        la.calculer();
        enregistreur.calculer();
    }
    std::cout << "Q5 done\n";
}

void QTest::Q9() {
    std::cout << "Q9: Test multiplicateur class\n";
    harmonique la440Hz(440, 0);
    harmonique la880Hz(880, 0);
    enregistreur_fichier enregistreur("../out/q9.raw", 1);
    multiplicateur filtreMultiplicateur;
    filtreMultiplicateur.connecterEntree(la440Hz.getSortie(0), 0);
    filtreMultiplicateur.connecterEntree(la880Hz.getSortie(0), 1);
    enregistreur.connecterEntree(filtreMultiplicateur.getSortie(0), 0);
    for (unsigned int i = 0; i < 2 * MixageSonore::frequency; ++i) {
        la440Hz.calculer();
        la880Hz.calculer();
        filtreMultiplicateur.calculer();
        enregistreur.calculer();
    }
    std::cout << "Q9 done\n";
}

void QTest::Q11() {
    std::cout << "Q11: Test operation_binaire class\n";
    harmonique la440Hz(440, 0);
    harmonique la880Hz(880, 0);
    enregistreur_fichier enregistreur("../out/q11.raw", 1);
    operation_binaire<std::multiplies<>> filtreOp;
    filtreOp.connecterEntree(la440Hz.getSortie(0), 0);
    filtreOp.connecterEntree(la880Hz.getSortie(0), 1);
    enregistreur.connecterEntree(filtreOp.getSortie(0), 0);
    for (unsigned int i = 0; i < 2 * MixageSonore::frequency; ++i) {
        la440Hz.calculer();
        la880Hz.calculer();
        filtreOp.calculer();
        enregistreur.calculer();
    }
    std::cout << "Q11 done\n";
}

void QTest::Q12() {
    std::cout << "Q12: Test volume class\n";
    harmonique la(440, 0);
    enregistreur_fichier enregistreur("../out/q12.raw", 1);
    volume filtre(2.0);
    filtre.connecterEntree(la.getSortie(0), 0);
    enregistreur.connecterEntree(filtre.getSortie(0), 0);
    for (unsigned int i = 0; i < 2 * MixageSonore::frequency; ++i) {
        la.calculer();
        filtre.calculer();
        enregistreur.calculer();
    }
    std::cout << "Q12 done\n";
}

void QTest::Q15() {
    std::cout << "Q15: Test mixeur class\n";
    {
        mixeur filtremixeur({0.5, 1});
        harmonique la440Hz(440, 0);
        harmonique la880Hz(880, 0);
        filtremixeur.connecterEntree(la440Hz.getSortie(0), 0);
        filtremixeur.connecterEntree(la880Hz.getSortie(0), 1);
        enregistreur_fichier enregistreur("../out/q15_1.raw", 1);
        enregistreur.connecterEntree(filtremixeur.getSortie(0), 0);
        for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
            la440Hz.calculer();
            la880Hz.calculer();
            filtremixeur.calculer();
            enregistreur.calculer();
        }
    }
    {
        mixeur filtremixeur({1, 0.5});
        harmonique la440Hz(440, 0);
        harmonique la880Hz(880, 0);
        filtremixeur.connecterEntree(la440Hz.getSortie(0), 0);
        filtremixeur.connecterEntree(la880Hz.getSortie(0), 1);
        enregistreur_fichier enregistreur("../out/q15_2.raw", 1);
        enregistreur.connecterEntree(filtremixeur.getSortie(0), 0);
        for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
            la440Hz.calculer();
            la880Hz.calculer();
            filtremixeur.calculer();
            enregistreur.calculer();
        }
    }
    std::cout << "Q15 done\n";
}

void QTest::Q16() {
    std::cout << "Q16: Test lecteur_fichier_mono class\n";
    lecteur_fichier lecteur("../raw/mono.raw", 1);
    enregistreur_fichier enregistreur("../out/q16_lecteur_fichier_mono.raw", 1);
    enregistreur.connecterEntree(lecteur.getSortie(0), 0);

    while(lecteur.can_read()){
        lecteur.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q16_lecteur_fichier_mono.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q16 done\n";
}

// Test for Q17: Mixage piste audio (Mono + Stereo)
void QTest::Q17() {
    std::cout << "Q17: Test mixage_piste_audio\n";
    lecteur_fichier lecteur_mono("../raw/mono.raw", 1);
    lecteur_fichier lecteur_stereo("../raw/stereo.raw", 2);
    mixeur mixeur_filter({0.5, 0.5, 0.5});

    mixeur_filter.connecterEntree(lecteur_mono.getSortie(0), 0);
    mixeur_filter.connecterEntree(lecteur_stereo.getSortie(0), 1);
    mixeur_filter.connecterEntree(lecteur_stereo.getSortie(1), 2);

    enregistreur_fichier enregistreur("../out/q17_mixage_piste_audio.raw", 1);
    enregistreur.connecterEntree(mixeur_filter.getSortie(0), 0);

    while (lecteur_mono.can_read() && lecteur_stereo.can_read()) {
        lecteur_mono.calculer();
        lecteur_stereo.calculer();
        mixeur_filter.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q17_mixage_piste_audio.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q17 done\n";
}

// Test for Q18_1: Fade In
void QTest::Q18_1() {
    std::cout << "Q18_1: Test fade_in class\n";
    lecteur_fichier lecteur("../raw/mono.raw", 1);
    enregistreur_fichier enregistreur("../out/q181_fade_in.raw", 1);

    fade_in fade_filter(2, 2);
    fade_filter.connecterEntree(lecteur.getSortie(0), 0);
    enregistreur.connecterEntree(fade_filter.getSortie(0), 0);

    while (lecteur.can_read()) {
        lecteur.calculer();
        fade_filter.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q181_fade_in.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q18_1 done\n";
}

// Test for Q18_2: Fade Out
void QTest::Q18_2() {
    std::cout << "Q18_2: Test fade_out class\n";
    lecteur_fichier lecteur("../raw/mono.raw", 1);
    enregistreur_fichier enregistreur("../out/q182_fade_out.raw", 1);

    fade_out fade_filter(2, 2);
    fade_filter.connecterEntree(lecteur.getSortie(0), 0);
    enregistreur.connecterEntree(fade_filter.getSortie(0), 0);

    while (lecteur.can_read()) {
        lecteur.calculer();
        fade_filter.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q182_fade_out.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q18_2 done\n";
}

// // Test for Q18Compression: Compression filter
void QTest::Q18Compression() {
    std::cout << "Q18Compression: Test compression filter\n";
    lecteur_fichier lecteur("../raw/mono.raw", 1);
    enregistreur_fichier enregistreur("../out/q18_compression.raw", 1);

    compression compression_filter(0.98);
    compression_filter.connecterEntree(lecteur.getSortie(0), 0);
    enregistreur.connecterEntree(compression_filter.getSortie(0), 0);

    while (lecteur.can_read()) {
        lecteur.calculer();
        compression_filter.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q18_compression.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q18Compression done\n";
}

// // Test for Q18Echo: Echo effect
void QTest::Q18Echo() {
    std::cout << "Q18Echo: Test echo filter\n";
    lecteur_fichier lecteur("../raw/stereo.raw", 2);
    enregistreur_fichier enregistreur("../out/q18_echo.raw", 1);

    echo echo_filter(1000, 0.5);
    echo_filter.connecterEntree(lecteur.getSortie(0), 0);
    enregistreur.connecterEntree(echo_filter.getSortie(0), 0);

    while (lecteur.can_read()) {
        lecteur.calculer();
        echo_filter.calculer();
        enregistreur.calculer();
    }

    std::ifstream out_file("../out/q18_echo.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q18Echo done\n";
}

// Test for Q18Panning: Panning effect
void QTest::Q18Panning() {
    std::cout << "Q18Panning: Test panning effect\n";
    lecteur_fichier lecteur("../raw/stereo.raw", 2);
    enregistreur_fichier enregistreur("../out/q18_panning.raw", 2);

    panning panning_filter;
    harmonique harmonique_filter(1, 0);

    panning_filter.connecterEntree(lecteur.getSortie(0), 0);
    panning_filter.connecterEntree(lecteur.getSortie(1), 1);
    panning_filter.connecterEntree(harmonique_filter.getSortie(0), 2);

    enregistreur.connecterEntree(panning_filter.getSortie(0), 0);
    enregistreur.connecterEntree(panning_filter.getSortie(1), 1);

    while (lecteur.can_read()) {
      lecteur.calculer();
      harmonique_filter.calculer();
      panning_filter.calculer();
      enregistreur.calculer();
    }
    

    std::ifstream out_file("../out/q18_panning.raw");
    assert(out_file.good() && out_file.peek() != std::ifstream::traits_type::eof());
    out_file.close();
    std::cout << "Q18Panning done\n";
}