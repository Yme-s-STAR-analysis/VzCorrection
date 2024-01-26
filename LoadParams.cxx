void LoadParams() {
    const int n = 1;
    const int trgs[n] = {
        650000
    };
    int major = 0; // 640041

    double p[7];
    TFile* tf;
    TF1* func;

    // RefMult3
    // get major
    cout << "For RefMult3" << endl;
    tf = new TFile(Form("high_end_point_vz_Ref3_%d_raw.root", trgs[major]));
    func = (TF1*)tf->Get("hfunc");
    func->GetParameters(p);

    tf->Close();

    for (int i=0; i<n; i++) {
        tf = new TFile(Form("high_end_point_vz_Ref3_%d_raw.root", trgs[i]));
        func = (TF1*)tf->Get("hfunc");
        p[0] = func->GetParameter(0);
        cout << "Trigger ID: " << trgs[i] << endl;
        cout << "{";
        for (int j=0; j<7; j++) {
            cout << p[j] << "\t";
            if (j != 6) {
                cout << ",";
            } else {
                cout << "}\n";
            }
        }
        tf->Close();
    }

    // RefMult3X
    // get major
    tf = new TFile(Form("high_end_point_vz_Ref3X_%d_raw.root", trgs[major]));
    func = (TF1*)tf->Get("hfunc");
    func->GetParameters(p);

    tf->Close();
    cout << "For RefMult3X" << endl;
    for (int i=0; i<n; i++) {
        tf = new TFile(Form("high_end_point_vz_Ref3X_%d_raw.root", trgs[i]));
        func = (TF1*)tf->Get("hfunc");
        p[0] = func->GetParameter(0);
        cout << "Trigger ID: " << trgs[i] << endl;
        cout << "{";
        for (int j=0; j<7; j++) {
            cout << p[j] << "\t";
            if (j != 6) {
                cout << ",";
            } else {
                cout << "}\n";
            }
        }
        tf->Close();
    }

}
