#ifndef __CENT_TOOL_CONFXXX__
#define __CENT_TOOL_CONFXXX__

namespace cent_conf {
    
    // The name and mode are used to check in the LOG file if the wrong parameter file is used.
    static const char* Name = "19p6-U"; 
    static const char* Mode = 
        "TEST";
        // "PU";
        // "LUMI";
        // "VZ";
        // "COMP";

    static const int nTrg = 6;
    static int trgList[nTrg] = {
        640001,
        640011,
        640021,
        640031,
        640041,
        640051
    };

    // Pile-up parameters

    // Official vz-dependent nTofMatch cut parameters the vz bins are:
    //  - 0 for -70 to -29
    //  - 1 for -29 to +29
    //  - 2 for +29 to +70
    // Will apply 4th order polynoial, instead of 3rd order
    static double match_upper_pars[3][5] = {
        {-2.42631231475246, 1.09725095487999, -0.000713252178085719, 2.77913369768123e-06, -4.03436998560179e-09},
        {-1.75423462803525, 1.01081367577287, -0.000321620496150629, 7.63921901896849e-07, -6.22014720258837e-10},
        {-2.59392664055544, 1.1041684381829, -0.000829795689107222, 3.29774572690107e-06, -4.80775654862195e-09}
    };
    static double match_lower_pars[3][5] = {
        {-15.5923736275086, 0.604206551537668, 0.00131805594121643, -2.04753779335401e-06, 5.73181898751325e-10},
        {-13.1157864223955, 0.504707692972168, 0.00187997948645203, -4.7317012773039e-06, 4.8234194091071e-09},
        {-15.9411138444366, 0.61506063963685, 0.0011824174541949, -1.48902496972716e-06, -2.29371463231934e-10}
    };
    
    // Customized nTofBeta cut parameters, no Vz dependence
    static double beta_upper_pars[4] = {
        0, 0, 0, 0
    };
    static double beta_lower_pars[4] = {
        0, 0, 0, 0
    };

    // Luminosity arguments
    static double lumi_par[nTrg][2] = { // please follow the order of trigger id
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };

    // vz arguments
    static double vz_par[nTrg][7] = { // please follow the order of trigger id
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };
      
    // centrality split with RefMult3
    static int cent_edge[9] = { // here fill in the centrality bin edge 
        492, 413, 288, 196, 128, 79, 46, 24, 12
    };

} // namespace cent_conf


#endif
