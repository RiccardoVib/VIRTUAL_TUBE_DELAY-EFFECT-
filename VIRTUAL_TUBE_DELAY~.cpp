//
//  VIRTUAL_TUBE_DELAY~.cpp
//  VIRTUAL_TUBE_DELAY~
//
//  Created by Riccardo Simionato on 10/03/18.
//  Copyright © 2018 Riccardo Simionato. All rights reserved.
//

#include "m_pd.h"
#include <math.h>
#include <tgmath.h>

const double PI = 3.14159265358979;

// delay filters parameters

const double f12 = -42.8571428571429;
const double f12LP = 100;
const double g12 = 0.00285714285714286;
const double f212 = 785.714285714286;

const double g23 = 0.00500000000000000;
const double f23LP = 133.333333333333;

//const double inc0 = 0.85;
const double fc1_0 = 1200;
const double fcLP_0 = 9500;
const double fc2_0 = 1500;

//const double inc1 = 0.87;
const double fc1_1 = 900;
const double fcLP_1 = 10200;
const double fc2_1 = 7000;


//reflection filters value

//stepref0
const double B0r_0 = 0.00148875526585464;
const double B1r_0 = -0.00120708383241042;
const double B2r_0 = -0.00148190029224148;
const double B3r_0 = 0.00121393880602358;

const double A1r_0 = -2.89790633258181;
const double A2r_0 = 2.79802595323123;
const double A3r_0 = -0.900105910702194;


//stepref1
const double B0r_1 = 0.00335592831460436;
const double B1r_1 = -0.00277817344018852;
const double B2r_1 = -0.00334268955647620;
const double B3r_1 = 0.00279141219831668;

const double A1r_1 = -2.88825538503306;
const double A2r_1 = 2.77989104675777;
const double A3r_1 = -0.891609184208459;


//stepref2
const double B0r_2 = 0.00517270575773444;
const double B1r_2 = -0.00436824166171923;
const double B2r_2 = -0.00515548132738072;
const double B3r_2 = 0.00438546609207296;

const double A1r_2 = -2.87865489770775;
const double A2r_2 = 2.76156314738057;
const double A3r_2 = -0.882873800812105;

//stepref3
const double B0r_3 = 0.00694154483627482;
const double B1r_3 = -0.00597476665661756;
const double B2r_3 = -0.00692237672582804;
const double B3r_3 = 0.00599393476706433;

const double A1r_3 = -2.86910528623180;
const double A2r_3 = 2.74306469622661;
const double A3r_3 = -0.873921073773921;

//stepref4
const double B0r_4 = 0.00866475675339795;
const double B1r_4 = -0.00759543715065878;
const double B2r_4 = -0.00864533731394742;
const double B3r_4 = 0.00761485659010931;

const double A1r_4 = -2.85960675039235;
const double A2r_4 = 2.72441611016413;
const double A3r_4 = -0.864770520892871;

//stepref5
const double B0r_5 = 0.0103445175450547;
const double B1r_5 = -0.00922813353428962;
const double B2r_5 = -0.0103261959767865;
const double B3r_5 = 0.00924645510255783;

const double A1r_5 = -2.85015929946656;
const double A2r_5 = 2.70563596673260;
const double A3r_5 = -0.855440024129502;


//stepref6
const double B0r_6 = 0.0119828779968571;
const double B1r_6 = -0.0108709108283402;
const double B2r_6 = -0.0119666668108299;
const double B3r_6 = 0.0108871220143674;

const double A1r_6 = -2.84076277470616;
const double A2r_6 = 2.68674117057348;
const double A3r_6 = -0.845945973495265;


//stepref7
const double B0r_7 = 0.00836341467664481;
const double B1r_7 = -0.00771081517160211;
const double B2r_7 = -0.00835515175240575;
const double B3r_7 = 0.00771907809584116;

const double A1r_7 = -2.88259911416098;
const double A2r_7 = 2.76830119673105;
const double A3r_7 = -0.885685556721597;


//stepref8
const double B0r_8 = 0.00900195734508397;
const double B1r_8 = -0.00838163049001607;
const double B2r_8 = -0.00899386146161446;
const double B3r_8 = 0.00838972637348558;

const double A1r_8 = -2.88561377593316;
const double A2r_8 = 2.77407915692424;
const double A3r_8 = -0.888449189224143;


//stepref9
const double B0r_9 = 0.00969383015351482;
const double B1r_9 = -0.00910235464057830;
const double B2r_9 = -0.00968593989333203;
const double B3r_9 = 0.00911024490076109;

const double A1r_9 = -2.88827763754024;
const double A2r_9 = 2.77918335198401;
const double A3r_9 = -0.890889933923404;


//stepref10
const double B0r_10 = 0.0104428831033720;
const double B1r_10 = -0.00987777161476080;
const double B2r_10 = -0.0104352379207295;
const double B3r_10 = 0.00988541679740335;

const double A1r_10 = -2.89066491723660;
const double A2r_10 = 2.78375610909223;
const double A3r_10 = -0.893075901490345;


//stepref11
const double B0r_11 = 0.0112533756990923;
const double B1r_11 = -0.0107128762780108;
const double B2r_11 = -0.0112460156575885;
const double B3r_11 = 0.0107202363195145;

const double A1r_11 = -2.89283178576968;
const double A2r_11 = 2.78790514723905;
const double A3r_11 = -0.895058641386365;


//stepref12
const double B0r_12 = 0.0121299824661228;
const double B1r_12 = -0.0116129408030305;
const double B2r_12 = -0.0121229478695646;
const double B3r_12 = 0.0116199753995886;

const double A1r_12 = -2.89482161761424;
const double A2r_12 = 2.79171365153887;
const double A3r_12 = -0.896877964731514;


//stepref13
const double B0r_13 = 0.0130778078453958;
const double B1r_13 = -0.0125835707077660;
const double B2r_13 = -0.0130711387557259;
const double B3r_13 = 0.0125902397974359;

const double A1r_13 = -2.89666851198821;
const double A2r_13 = 2.79524702918906;
const double A3r_13 = -0.898565179021510;


class VIRTUAL_TUBE_DELAYObj{
    
public:
    VIRTUAL_TUBE_DELAYObj() //constructor 
    {
        
        //reflection filters

        br0[0] = B0r_0; ar0[0] = A1r_0;
        br0[1] = B1r_0; ar0[1] = A2r_0;
        br0[2] = B2r_0; ar0[2] = A3r_0;
        br0[3] = B3r_0;
        
        br1[0] = B0r_1; ar1[0] = A1r_1;
        br1[1] = B1r_1; ar1[1] = A2r_1;
        br1[2] = B2r_1; ar1[2] = A3r_1;
        br1[3] = B3r_1;
        
        br2[0] = B0r_2;
        br2[1] = B1r_2; ar2[0] = A1r_2;
        br2[2] = B2r_2; ar2[1] = A2r_2;
        br2[3] = B3r_2; ar2[2] = A3r_2;
        
        br3[0] = B0r_3;
        br3[1] = B1r_3; ar3[0] = A1r_3;
        br3[2] = B2r_3; ar3[1] = A2r_3;
        br3[3] = B3r_3; ar3[2] = A3r_3;
        
        br4[0] = B0r_4;
        br4[1] = B1r_4; ar4[0] = A1r_4;
        br4[2] = B2r_4; ar4[1] = A2r_4;
        br4[3] = B3r_4; ar4[2] = A3r_4;
        
        br5[0] = B0r_5;
        br5[1] = B1r_5; ar5[0] = A1r_5;
        br5[2] = B2r_5; ar5[1] = A2r_5;
        br5[3] = B3r_5; ar5[2] = A3r_5;
        
        br6[0] = B0r_6;
        br6[1] = B1r_6; ar6[0] = A1r_6;
        br6[2] = B2r_6; ar6[1] = A2r_6;
        br6[3] = B3r_6; ar6[2] = A3r_6;
        
        br7[0] = B0r_7;
        br7[1] = B1r_7; ar7[0] = A1r_7;
        br7[2] = B2r_7; ar7[1] = A2r_7;
        br7[3] = B3r_7; ar7[2] = A3r_7;
        
        
        br8[0] = B0r_8;
        br8[1] = B1r_8; ar8[0] = A1r_8;
        br8[2] = B2r_8; ar8[1] = A2r_8;
        br8[3] = B3r_8; ar8[2] = A3r_8;

        
        br9[0] = B0r_9;
        br9[1] = B1r_9; ar9[0] = A1r_9;
        br9[2] = B2r_9; ar9[1] = A2r_9;
        br9[3] = B3r_9; ar9[2] = A3r_9;
        
        
        br10[0] = B0r_10;
        br10[1] = B1r_10; ar10[0] = A1r_10;
        br10[2] = B2r_10; ar10[1] = A2r_10;
        br10[3] = B3r_10; ar10[2] = A3r_10;

        
        br11[0] = B0r_11;
        br11[1] = B1r_11; ar11[0] = A1r_11;
        br11[2] = B2r_11; ar11[1] = A2r_11;
        br11[3] = B3r_11; ar11[2] = A3r_11;
        
        br12[0] = B0r_12;
        br12[1] = B1r_12; ar12[0] = A1r_12;
        br12[2] = B2r_12; ar12[1] = A2r_12;
        br12[3] = B3r_12; ar12[2] = A3r_12;
        
        br13[0] = B0r_13;
        br13[1] = B1r_13; ar13[0] = A1r_13;
        br13[2] = B2r_13; ar13[1] = A2r_13;
        br13[3] = B3r_13; ar13[2] = A3r_13;

        
             // delay filters
        
        fc1_R = 0;
        fc2_R = 0;
        inc_R = 0;
        
        fc1_L = 0;
        fc2_L = 0;
        inc_L = 0;
        
        fcLP_R = 0;
        fcLP_0_R = 0;
        fcLP_1_R = 0;
        
        fcLP_L = 0;
        fcLP_0_L = 0;
        fcLP_1_L = 0;
        
        
        Q1_R = 0;
        Q2_R = 0;
        G1_R = 0;
        G2_R = 0;
        V1_R = 0;
        V2_R = 0;
        
        Q1_L = 0;
        Q2_L = 0;
        G1_L = 0;
        G2_L = 0;
        V1_L = 0;
        V2_L = 0;
        
        //1st filter
        
        K1_R = 0;
        K1_L = 0;
        
        a1_R = 0;
        a1_L = 0;
        
        a2_R = 0;
        a2_L = 0;
        
        b0_R = 0;
        b0_L = 0;
        
        b1_R = 0;
        b1_L = 0;
        
        b2_R = 0;
        b2_L = 0;
        
        
        //2nd filter
        
        K2_R = 0;
        K2_L = 0;
        
        a11_R = 0;
        a11_L = 0;
        
        a22_R = 0;
        a22_L = 0;
        
        b00_R = 0;
        b00_L = 0;
        
        b11_R = 0;
        b11_L = 0;
        
        b22_R = 0;
        b22_L = 0;
        
        // final filter
        
        a1f_R = 0;
        a1f_L = 0;
        
        a2f_R = 0;
        a2f_L = 0;
        
        a3f_R = 0;
        a3f_L = 0;
        
        a4f_R = 0;
        a4f_L = 0;
        
        a5f_R = 0;
        a5f_L = 0;
        
        a6f_R = 0;
        a6f_L = 0;
        
        b0f_R = 0;
        b0f_L = 0;
        
        b1f_R = 0;
        b1f_L = 0;
        
        b2f_R = 0;
        b2f_L = 0;
        
        b3f_R = 0;
        b3f_L = 0;
        
        b4f_R = 0;
        b4f_L = 0;
        
        b5f_R = 0;
        b5f_L = 0;
        
        b6f_R = 0;
        b6f_L = 0;
        
        //LP filter
        
        KLP_R = 0;
        KLP_L = 0;
        
        a2LP_R = 0;
        a2LP_L = 0;
        
        a1LP_R = 0;
        a1LP_L = 0;
        
        b0LP_R = 0;
        b0LP_L = 0;
        
        b1LP_R = 0;
        b1LP_L = 0;
        
        b2LP_R = 0;
        b2LP_L = 0;
        
        outR = new float[6];
        outL = new float[6];
        inR = new float[6];
        inL = new float[6];
        out2R = new float[6];
        out2L = new float[6];
        out3R = new float[3];
        out3L = new float[3];
        
        
        len = 4490;//4490; //[46.7755102040816] m
        
        bufferR = new float[len];
        bufferL = new float[len];
        
    };
    
    ~VIRTUAL_TUBE_DELAYObj() //distruttore
    {
        
        
        delete [] bufferL;
        delete [] bufferR;
        delete [] inL;
        delete [] inR;
        delete [] outR;
        delete [] outL;
        delete [] out2R;
        delete [] out2L;
        delete [] out3R;
        delete [] out3L;
    }
    
    void process(const float* input, float* lengthL, float* lengthR, float* gainL, float* gainR, float* size, float* ref, float* lengthRefL, float* lengthRefR, float* gainRefL, float* gainRefR, float* dry_wet, float* outputR, float* outputL, int n)
    {
        
        //delay time = length/c
        int lL = floor(lengthL[n-1]*100);
        int lR = floor(lengthR[n-1]*100);
        
        double lengL = lL/100;
        double lengR = lR/100;
        
        if (lengL < 1)
            lengL = 1;
        
        if (lengR < 1)
            lengR = 1;

        
        int delayMillisecondsL = lengL/0.3438;  // time delay
        int delayMillisecondsR = lengR/0.3438;  // time delay
        
        // number of samples = delay time * f
        int delaySamplesL = (int)((float)delayMillisecondsL * 44.1f); // assumes 44100 Hz sample rate
        int delaySamplesR = (int)((float)delayMillisecondsR * 44.1f); // assumes 44100 Hz sample rate
        
        
        float gL = gainL[n-1];
        float gR = gainR[n-1];
        float gRef_R = gainRefR[n-1];
        float gRef_L = gainRefL[n-1];
        
        float wet = dry_wet[n-1]/100.00f;
        float dry = 1 - dry_wet[n-1]/100.00f;
        
        int rad = floor(size[n-1]*10 - 12);
        
        if (rad == -12){
            rad = 0;
        }
        
        
        if (rad == 0 || rad == -12) {
            
            ar[0] = ar0[0];
            ar[1] = ar0[1];
            ar[2] = ar0[2];
            
            br[0] = br0[0];
            br[1] = br0[1];
            br[2] = br0[2];
            br[3] = br0[3];
            
        }else if (rad == 1) {
            
            ar[0] = ar1[0];
            ar[1] = ar1[1];
            ar[2] = ar1[2];
            
            br[0] = br1[0];
            br[1] = br1[1];
            br[2] = br1[2];
            br[3] = br1[3];
            
        }else if (rad == 2) {
            
            ar[0] = ar2[0];
            ar[1] = ar2[1];
            ar[2] = ar2[2];
            
            br[0] = br2[0];
            br[1] = br2[1];
            br[2] = br2[2];
            br[3] = br2[3];
            
        }else if (rad == 3) {
            
            ar[0] = ar3[0];
            ar[1] = ar3[1];
            ar[2] = ar3[2];
            
            br[0] = br3[0];
            br[1] = br3[1];
            br[2] = br3[2];
            br[3] = br3[3];
            
        }else if (rad == 4) {
            
            ar[0] = ar4[0];
            ar[1] = ar4[1];
            ar[2] = ar4[2];
            
            br[0] = br4[0];
            br[1] = br4[1];
            br[2] = br4[2];
            br[3] = br4[3];
            
        }else if (rad == 5) {
            
            ar[0] = ar5[0];
            ar[1] = ar5[1];
            ar[2] = ar5[2];
            
            br[0] = br5[0];
            br[1] = br5[1];
            br[2] = br5[2];
            br[3] = br5[3];
            
        }else if (rad == 6) {
            
            ar[0] = ar6[0];
            ar[1] = ar6[1];
            ar[2] = ar6[2];
            
            br[0] = br6[0];
            br[1] = br6[1];
            br[2] = br6[2];
            br[3] = br6[3];
            
        }else if (rad == 7) {
            
            ar[0] = ar7[0];
            ar[1] = ar7[1];
            ar[2] = ar7[2];
            
            br[0] = br7[0];
            br[1] = br7[1];
            br[2] = br7[2];
            br[3] = br7[3];
            
        }else if (rad == 8) {
            
            ar[0] = ar8[0];
            ar[1] = ar8[1];
            ar[2] = ar8[2];
            
            br[0] = br8[0];
            br[1] = br8[1];
            br[2] = br8[2];
            br[3] = br8[3];
            
        }else if (rad == 9) {
            
            ar[0] = ar9[0];
            ar[1] = ar9[1];
            ar[2] = ar9[2];
            
            br[0] = br9[0];
            br[1] = br9[1];
            br[2] = br9[2];
            br[3] = br9[3];
            
        }else if (rad == 10) {
            
            ar[0] = ar10[0];
            ar[1] = ar10[1];
            ar[2] = ar10[2];
            
            br[0] = br10[0];
            br[1] = br10[1];
            br[2] = br10[2];
            br[3] = br10[3];
            
        }else if (rad == 11) {
            
            ar[0] = ar11[0];
            ar[1] = ar11[1];
            ar[2] = ar11[2];
            
            br[0] = br11[0];
            br[1] = br11[1];
            br[2] = br11[2];
            br[3] = br11[3];
            
        }else if (rad == 12) {
            
            ar[0] = ar12[0];
            ar[1] = ar12[1];
            ar[2] = ar12[2];
            
            br[0] = br12[0];
            br[1] = br12[1];
            br[2] = br12[2];
            br[3] = br12[3];
            
        }else if (rad == 13) {
            
            ar[0] = ar13[0];
            ar[1] = ar13[1];
            ar[2] = ar13[2];
            
            br[0] = br13[0];
            br[1] = br13[1];
            br[2] = br13[2];
            br[3] = br13[3];
        }
        
        //delay time = length/c
        int lRL = floor(lengthRefL[n-1]*100);
        int lRR = floor(lengthRefR[n-1]*100);
        
        
        double lengRefL = lRL/100;
        double lengRefR = lRR/100;
        
        if (lengRefL < 1)
            lengRefL = 1;
        
        if (lengRefR < 1)
            lengRefR = 1;
        
        double length_totL = 2*lengRefL;
        double length_totR = 2*lengRefR;
        
        int delayMillisecondsRefL = (2*lengRefL)/0.3438;  // time delay
        int delayMillisecondsRefR = (2*lengRefR)/0.3438;  // time delay
        
        // number of samples = delay time * f
        int delaySamplesRefL = (int)((float)delayMillisecondsRefL * 44.1f); // assumes 44100 Hz sample rate
        int delaySamplesRefR = (int)((float)delayMillisecondsRefR * 44.1f); // assumes 44100 Hz sample rate
        
        int delaySamplesL_tot = delaySamplesL + delaySamplesRefL;
        int delaySamplesR_tot = delaySamplesR + delaySamplesRefR;
        
        
        int k_R;
        int k_L;
        
        double inck_R;
        double inck_L;
        
        int k2_R;
        int k2_L;
        
        double inck2_R;
        double inck2_L;
        
        if (lengR < 2) {
            k_R = 0; inck_R = 8.5;
        }else if (lengR < 3){
            k_R = 850; inck_R = 8.5;
        }else if (lengR < 4){
            k_R = 1700; inck_R = 10;
        }else if (lengR < 5){
            k_R = 2700; inck_R = 8;
        }else if (lengR < 6){
            k_R = 3500; inck_R = 5;
        }else if (lengR < 7){
            k_R = 4000; inck_R = 5;
        }else if (lengR < 8){
            k_R = 4500; inck_R = 4;
        }else if (lengR < 9){
            k_R = 4900; inck_R = 3;
        }else if (lengR < 10){
            k_R = 5200; inck_R = 2;
        }else if (lengR < 11){
            k_R = 5400; inck_R = 2;
        }else if (lengR < 12){
            k_R = 5600; inck_R = 2;
        }else if (lengR < 13){
            k_R = 5800; inck_R = 2;
        }else if (lengR < 14){
            k_R = 6000; inck_R = 2;
        }else if (lengR < 15){
            k_R = 6200; inck_R = 2;
        }else if (lengR < 16){
            k_R = 6400; inck_R = 2;
        }else if (lengR < 17){
            k_R = 6700; inck_R = 3;
        }else if (lengR < 18){
            k_R = 7000; inck_R = 3;
        }else if (lengR < 19){
            k_R = 7300; inck_R = 3;
        }else if (lengR < 20){
            k_R = 7500; inck_R = 2;
        }else if (lengR < 21){
            k_R = 7700; inck_R = 2;
        }else if (lengR < 22){
            k_R = 7800; inck_R = 1;
        }else if (lengR < 23){
            k_R = 7950; inck_R = 1.5;
        }else if (lengR < 24){
            k_R = 8050; inck_R = 0.5;
        }else if (lengR < 25){
            k_R = 8150; inck_R = 1;
        }else if (lengR < 26){
            k_R = 8250; inck_R = 1;
        }else if (lengR < 27){
            k_R = 8350; inck_R = 1;
        }else if (lengR < 28){
            k_R = 8400; inck_R = 0.5;
        }else if (lengR < 29){
            k_R = 8500; inck_R = 1;
        }else if (lengR < 30){
            k_R = 8550; inck_R = 1.5;
        }else if (lengR < 31){
            k_R = 8600; inck_R = 0.5;
        }else if (lengR < 32){
            k_R = 8650; inck_R = 0.5;
        }else if (lengR < 33){
            k_R = 8690; inck_R = 0.4;
        }else if (lengR < 34){
            k_R = 8750; inck_R = 0.6;
        }else if (lengR < 35){
            k_R = 8770; inck_R = 1.3;
        }else{
            k_R = 8900; inck_R = 0;
        }
        
        if (lengL < 2) {
            k_L = 0; inck_L = 8.5;
        }else if (lengL < 3){
            k_L = 850; inck_L = 8.5;
        }else if (lengL < 4){
            k_L = 1700; inck_L = 10;
        }else if (lengL < 5){
            k_L = 2700; inck_L = 8;
        }else if (lengL < 6){
            k_L = 3500; inck_L = 5;
        }else if (lengL < 7){
            k_L = 4000; inck_L = 5;
        }else if (lengL < 8){
            k_L = 4500; inck_L = 4;
        }else if (lengL < 9){
            k_L = 4900; inck_L = 3;
        }else if (lengL < 10){
            k_L = 5200; inck_L = 2;
        }else if (lengL < 11){
            k_L = 5400; inck_L = 2;
        }else if (lengL < 12){
            k_L = 5600; inck_L = 2;
        }else if (lengL < 13){
            k_L = 5800; inck_L = 2;
        }else if (lengL < 14){
            k_L = 6000; inck_L = 2;
        }else if (lengL < 15){
            k_L = 6200; inck_L = 2;
        }else if (lengL < 16){
            k_L = 6400; inck_L = 2;
        }else if (lengL < 17){
            k_L = 6700; inck_L = 3;
        }else if (lengL < 18){
            k_L = 7000; inck_L = 3;
        }else if (lengL < 19){
            k_L = 7300; inck_L = 3;
        }else if (lengL < 20){
            k_L = 7500; inck_L = 2;
        }else if (lengL < 21){
            k_L = 7700; inck_L = 2;
        }else if (lengL < 22){
            k_L = 7800; inck_L = 1;
        }else if (lengL < 23){
            k_L = 7950; inck_L = 1.5;
        }else if (lengL < 24){
            k_L = 8050; inck_L = 0.5;
        }else if (lengL < 25){
            k_L = 8150; inck_L = 1;
        }else if (lengL < 26){
            k_L = 8250; inck_L = 1;
        }else if (lengL < 27){
            k_L = 8350; inck_L = 1;
        }else if (lengL < 28){
            k_L = 8400; inck_L = 0.5;
        }else if (lengL < 29){
            k_L = 8500; inck_L = 1;
        }else if (lengL < 30){
            k_L = 8550; inck_L = 1.5;
        }else if (lengL < 31){
            k_L = 8600; inck_L = 0.5;
        }else if (lengL < 32){
            k_L = 8650; inck_L = 0.5;
        }else if (lengL < 33){
            k_L = 8690; inck_L = 0.4;
        }else if (lengL < 34){
            k_L = 8750; inck_L = 0.6;
        }else if (lengL < 35){
            k_L = 8770; inck_L = 1.3;
        }else{
            k_L = 8900; inck_L = 0;
        }

    
        //reflection filter
        if (length_totR < 2){
            k2_R = 0; inck2_R = 8.5;
        }else if (length_totR < 3){
            k2_R = 850; inck2_R = 8.5;
        }else if (length_totR < 4){
            k2_R = 1700; inck2_R = 10;
        }else if (length_totR < 5){
            k2_R = 2700; inck2_R = 8;
        }else if (length_totR < 6){
            k2_R = 3500; inck2_R = 5;
        }else if (length_totR < 7){
            k2_R = 4000; inck2_R = 5;
        }else if (length_totR < 8){
            k2_R = 4500; inck2_R = 4;
        }else if (length_totR < 9){
            k2_R = 4900; inck2_R = 3;
        }else if (length_totR < 10){
            k2_R = 5200; inck2_R = 2;
        }else if (length_totR < 11){
            k2_R = 5400; inck2_R = 2;
        }else if (length_totR < 12){
            k2_R = 5600; inck2_R = 2;
        }else if (length_totR < 13){
            k2_R = 5800; inck2_R = 2;
        }else if (length_totR < 14){
            k2_R = 6000; inck2_R = 2;
        }else if (length_totR < 15){
            k2_R = 6200; inck2_R = 2;
        }else if (length_totR < 16){
            k2_R = 6400; inck2_R = 2;
        }else if (length_totR < 17){
            k2_R = 6700; inck2_R = 3;
        }else if (length_totR < 18){
            k2_R = 7000; inck2_R = 3;
        }else if (length_totR < 19){
            k2_R = 7300; inck2_R = 3;
        }else if (length_totR < 20){
            k2_R = 7500; inck2_R = 2;
        }else if (length_totR < 21){
            k2_R = 7700; inck2_R = 2;
        }else if (length_totR < 22){
            k2_R = 7800; inck2_R = 1;
        }else if (length_totR < 23){
            k2_R = 7950; inck2_R = 1.5;
        }else if (length_totR < 24){
            k2_R = 8050; inck2_R = 0.5;
        }else if (length_totR < 25){
            k2_R = 8150; inck2_R = 1;
        }else if (length_totR < 26){
            k2_R = 8250; inck2_R = 1;
        }else if (length_totR < 27){
            k2_R = 8350; inck2_R = 1;
        }else if (length_totR < 28){
            k2_R = 8400; inck2_R = 0.5;
        }else if (length_totR < 29){
            k2_R = 8500; inck2_R = 1;
        }else if (length_totR < 30){
            k2_R = 8550; inck2_R = 1.5;
        }else if (length_totR < 31){
            k2_R = 8600; inck2_R = 0.5;
        }else if (length_totR < 32){
            k2_R = 8650; inck2_R = 0.5;
        }else if (length_totR < 33){
            k2_R = 8690; inck2_R = 0.4;
        }else if (length_totR < 34){
            k2_R = 8750; inck2_R = 0.6;
        }else if (length_totR < 35){
            k2_R = 8770; inck2_R = 1.3;
        }else{
            k2_R = 8900; inck2_R = 0;
        }
        
        if (length_totL < 2){
            k2_L = 0; inck2_L = 8.5;
        }else if (length_totL < 3){
            k2_L = 850; inck2_L = 8.5;
        }else if (length_totL < 4){
            k2_L = 1700; inck2_L = 10;
        }else if (length_totL < 5){
            k2_L = 2700; inck2_L = 8;
        }else if (length_totL < 6){
            k2_L = 3500; inck2_L = 5;
        }else if (length_totL < 7){
            k2_L = 4000; inck2_L = 5;
        }else if (length_totL < 8){
            k2_L = 4500; inck2_L = 4;
        }else if (length_totL < 9){
            k2_L = 4900; inck2_L = 3;
        }else if (length_totL < 10){
            k2_L = 5200; inck2_L = 2;
        }else if (length_totL < 11){
            k2_L = 5400; inck2_L = 2;
        }else if (length_totL < 12){
            k2_L = 5600; inck2_L = 2;
        }else if (length_totL < 13){
            k2_L = 5800; inck2_L = 2;
        }else if (length_totL < 14){
            k2_L = 6000; inck2_L = 2;
        }else if (length_totL < 15){
            k2_L = 6200; inck2_L = 2;
        }else if (length_totL < 16){
            k2_L = 6400; inck2_L = 2;
        }else if (length_totL < 17){
            k2_L = 6700; inck2_L = 3;
        }else if (length_totL < 18){
            k2_L = 7000; inck2_L = 3;
        }else if (length_totL < 19){
            k2_L = 7300; inck2_L = 3;
        }else if (length_totL < 20){
            k2_L = 7500; inck2_L = 2;
        }else if (length_totL < 21){
            k2_L = 7700; inck2_L = 2;
        }else if (length_totL < 22){
            k2_L = 7800; inck2_L = 1;
        }else if (length_totL < 23){
            k2_L = 7950; inck2_L = 1.5;
        }else if (length_totL < 24){
            k2_L = 8050; inck2_L = 0.5;
        }else if (length_totL < 25){
            k2_L = 8150; inck2_L = 1;
        }else if (length_totL < 26){
            k2_L = 8250; inck2_L = 1;
        }else if (length_totL < 27){
            k2_L = 8350; inck2_L = 1;
        }else if (length_totL < 28){
            k2_L = 8400; inck2_L = 0.5;
        }else if (length_totL < 29){
            k2_L = 8500; inck2_L = 1;
        }else if (length_totL < 30){
            k2_L = 8550; inck2_L = 1.5;
        }else if (length_totL < 31){
            k2_L = 8600; inck2_L = 0.5;
        }else if (length_totL < 32){
            k2_L = 8650; inck2_L = 0.5;
        }else if (length_totL < 33){
            k2_L = 8690; inck2_L = 0.4;
        }else if (length_totL < 34){
            k2_L = 8750; inck2_L = 0.6;
        }else if (length_totL < 35){
            k2_L = 8770; inck2_L = 1.3;
        }else{
            k2_L = 8900; inck2_L = 0;
        }
        
        if (rad <= 6){
            
            inc_R = (pow(0.85 + rad*g12,(lengR)));
            inc_L = (pow(0.85 + rad*g12,(lengL)));
            Q1_R = 0.65;
            fcLP_R = fcLP_0 + rad*f12LP - (k_R + inck_R*(lengR - floor(lengR)));
            
            Q1_L = 0.65;
            fcLP_L = fcLP_0 + rad*f12LP - (k_L + inck_L*(lengL - floor(lengL)));
            
            //ref
            incRef_R = (pow(0.85 + rad*g12,(length_totR)));
            incRef_L = (pow(0.85 + rad*g12,(length_totL)));
            Q1Ref_R = 0.65;
            fcLPRef_R = fcLP_0 + rad*f12LP - (k2_R + inck2_R*(length_totR - floor(length_totR)));
            
            Q1Ref_L = 0.65;
            fcLPRef_L = fcLP_0 + rad*f12LP - (k2_L + inck2_L*(length_totL - floor(length_totL)));
            
            
            //right
            if (lengR <= 15) {
                
                G1_R = -1 - 0.85*(lengR-1);
                V1_R = pow(10,(G1_R/20));
                
                fc1_R = fc1_0 + rad*f12 +(lengR-1)*30;
                
                G2_R = -0.9-(lengR-1)*1;
                V2_R = pow(10,(G2_R/20));
                
                fc2_R = fc2_0 + rad*f212 + (lengR-1)*50;
                
                Q2_R = 0.5;
                
            }else{
                
                G1_R = -12.9000-0.6*(lengR-15);
                V1_R = pow(10,(G1_R/20));
                
                fc1_R = 1620 + rad*f12 + (lengR-15)*20;
                
                G2_R = -14.9000-(lengR-15)*0.1;
                V2_R = pow(10,(G2_R/20));
                
                fc2_R = 2200 + rad*f212;
                
                Q2_R = 0.5 + (lengR-15)*0.02;
                
            }
            
            //ref right
            
            if (length_totR <= 15) {
                
                G1Ref_R = -1 - 0.85*(length_totR-1);
                V1Ref_R = pow(10,(G1Ref_R/20));
                
                fc1Ref_R = fc1_0 + rad*f12 +(length_totR-1)*30;
                
                G2Ref_R = -0.9 - (length_totR-1)*1;
                V2Ref_R = pow(10,(G2Ref_R/20));
                
                fc2Ref_R = fc2_0 + rad*f212 + (length_totR-1)*50;
                
                Q2Ref_R = 0.5;
                
            }else{
                
                G1Ref_R = -12.9000 - 0.6*(length_totR-15);
                V1Ref_R = pow(10,(G1Ref_R/20));
                
                fc1Ref_R = 1620 + rad*f12 + (length_totR-15)*20;
                
                G2Ref_R = -14.9000-(length_totR-15)*0.1;
                V2Ref_R = pow(10,(G2Ref_R/20));
                
                fc2Ref_R = 2200 + rad*f212;
                
                Q2Ref_R = 0.5+(length_totR-15)*0.02;
                
            }
            
            // left
            
            if (lengL <= 15) {
                
                G1_L = -1 - 0.85*(lengL-1);
                V1_L = pow(10,(G1_L/20));
                
                fc1_L = fc1_0 + rad*f12 + (lengL-1)*30;
                
                G2_L = -0.9 - (lengL-1)*1;
                V2_L = pow(10,(G2_L/20));
                
                fc2_L = fc2_0 + rad*f212 + (lengL-1)*50;
                
                Q2_L = 0.5;
                
            }else{
                
                G1_L = -12.9000 - 0.6*(lengL-15);
                V1_L = pow(10,(G1_L/20));
                
                fc1_L = 1620 + rad*f12 + (lengL-15)*20;
                
                G2_L = -14.9000-(lengL-15)*0.1;
                V2_L = pow(10,(G2_L/20));
                
                fc2_L = 2200 + rad*f212;
                
                Q2_L = 0.5 + (lengL-15)*0.02;
                
            }
            
            // ref left
            
            if (length_totL <= 15) {
                
                G1Ref_L = -1 - 0.85*(length_totL-1);
                V1Ref_L = pow(10,(G1Ref_L/20));
                
                fc1Ref_L = fc1_0 + rad*f12 +(length_totL-1)*30;
                
                G2Ref_L = -0.9 - (length_totL-1)*1;
                V2Ref_L = pow(10,(G2Ref_L/20));
                
                fc2Ref_L = fc2_0 + rad*f212 + (length_totL-1)*50;
                
                Q2Ref_L = 0.5;
                
            }else{
                
                G1Ref_L = -12.9000-0.6*(length_totL-15);
                V1Ref_L = pow(10,(G1Ref_L/20));
                
                fc1Ref_L = 1620 + rad*f12 + (length_totL-15)*20;
                
                G2Ref_L = -14.9000 - (length_totL-15)*0.1;
                V2Ref_L = pow(10,(G2Ref_L/20));
                
                fc2Ref_L = 2200 + rad*f212;
                
                Q2Ref_L = 0.5+(length_totL-15)*0.02;
            
            }
            
            
            
        }else if(rad >= 7){
            
            inc_R = (pow(0.87 + (rad-7)*g23,(lengR)));
            inc_L = (pow(0.87 + (rad-7)*g23,(lengL)));
            Q1_R = 0.65;
            fcLP_R = fcLP_1 + (rad-7)*f23LP - (k_R + inck_R*(lengR - floor(lengR)));
            
            Q1_L = 0.65;
            fcLP_L = fcLP_1 + (rad-7)*f23LP - (k_L + inck_L*(lengL - floor(lengL)));
            
            //ref
            incRef_R = (pow(0.87 + (rad-7)*g23,(length_totR)));
            incRef_L = (pow(0.87 + (rad-7)*g23,(length_totL)));
            Q1Ref_R = 0.65;
            fcLPRef_R = fcLP_1 + (rad-7)*f23LP - (k2_R + inck2_R*(length_totR - floor(length_totR)));
            
            Q1Ref_L = 0.65;
            fcLPRef_L = fcLP_1 + (rad-7)*f23LP - (k2_L + inck2_L*(length_totL - floor(length_totL)));
            
            //right
            
            if (lengR <= 15) {
                
                G1_R = -1 - 0.85*(lengR-1);
                V1_R = pow(10,(G1_R/20));
                
                fc1_R = fc1_1 +(lengR-1)*30;
                
                G2_R = -0.9 - (lengR-1)*1;
                V2_R = pow(10,(G2_R/20));
                
                fc2_R = fc2_1 + (lengR-1)*50;
                
                Q2_R = 0.5;
                
            }else{
                
                G1_R = -12.9000 - 0.6*(lengR-15);
                V1_R = pow(10,(G1_R/20));
                
                fc1_R = 1320 + (lengR-15)*20;
                
                G2_R = -14.9000 - (lengR-15)*0.1;
                V2_R = pow(10,(G2_R/20));
                
                fc2_R = 7700;
                
                Q2_R = 0.5 + (lengR-15)*0.02;
                
            }
            
            // ref right
            
            if (length_totR <= 15) {
                
                G1Ref_R = -1-0.85*(length_totR-1);
                V1Ref_R = pow(10,(G1Ref_R/20));
                
                fc1Ref_R = fc1_1 + (length_totR-1)*30;
                
                G2Ref_R = -0.9 - (length_totR-1)*1;
                V2Ref_R = pow(10,(G2Ref_R/20));
                
                fc2Ref_R = fc2_1 + (length_totR-1)*50;
                
                Q2Ref_R = 0.5;
                
            }else{
                
                G1Ref_R = -12.9000 - 0.6*(length_totR-15);
                V1Ref_R = pow(10,(G1Ref_R/20));
                
                fc1Ref_R = 1320 + (length_totR-15)*20;
                
                G2Ref_R = -14.9000 - (length_totR-15)*0.1;
                V2Ref_R = pow(10,(G2Ref_R/20));
                
                fc2Ref_R = 7700;
                
                Q2Ref_R = 0.5 + (length_totR-15)*0.02;
                
            }
            
            //left
            
            if (lengL <= 15) {
                
                G1_L = -1 - 0.85*(lengL-1);
                V1_L = pow(10,(G1_L/20));
                
                fc1_L = fc1_1 +(lengL-1)*30;
                
                G2_L = -0.9 - (lengL-1)*1;
                V2_L = pow(10,(G2_L/20));
                
                fc2_L = fc2_1 + (lengL-1)*50;
                
                Q2_L = 0.5;
                
            }else{
                
                G1_L = -12.9000 - 0.6*(lengL-15);
                V1_L = pow(10,(G1_L/20));
                
                fc1_L = 1320 + (lengL-15)*20;
                
                G2_L = -14.9000 - (lengL-15)*0.1;
                V2_L = pow(10,(G2_L/20));
                
                fc2_L = 7700;
                
                Q2_L = 0.5 + (lengL-15)*0.02;
                
            }
            // ref left
            
            if (length_totL <= 15) {
                
                G1Ref_L = -1 - 0.85*(length_totL-1);
                V1Ref_L = pow(10,(G1Ref_L/20));
                
                fc1Ref_L = fc1_1 +(length_totL-1)*30;
                
                G2Ref_L = -0.9 - (length_totL-1)*1;
                V2Ref_L = pow(10,(G2Ref_L/20));
                
                fc2Ref_L = fc2_1 + (length_totL-1)*50;
                
                Q2Ref_L = 0.5;
                
            }else{
                
                G1Ref_L = -12.9000-0.6*(length_totL-15);
                V1Ref_L = pow(10,(G1Ref_L/20));
                
                fc1Ref_L = 1320 + (length_totL-15)*20;
                
                G2Ref_L = -14.9000 - (length_totL-15)*0.1;
                V2Ref_L = pow(10,(G2Ref_L/20));
                
                fc2Ref_L = 7700;
                
                Q2Ref_L = 0.5+(length_totL-15)*0.02;
                
            }
            
            
        }
        
        
        
        
        //1st filter
        
        K1_R = tan(PI*fc1_R/44100);
        
        a1_R = (2*(V1_R*K1_R*K1_R - 1))/(1 + (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R);
        
        a2_R = (1 - (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R)/(1 + (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R);
        
        b0_R = V1_R*(1 + (K1_R)/Q1_R + K1_R*K1_R) / (1 + (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R);
        
        b1_R = (2*V1_R*(K1_R*K1_R - 1)) / (1 + (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R);
        
        b2_R = V1_R*(1 - (K1_R)/Q1_R + K1_R*K1_R) / (1 + (sqrt(V1_R)*K1_R)/Q1_R + V1_R*K1_R*K1_R);
        
        //2nd filter
        
        K2_R = tan(PI*fc2_R/44100);
        
        a11_R = (2*(V2_R*K2_R*K2_R - 1))/ (1 + (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R);
        
        a22_R = (1 - (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R) / (1 + (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R);
        
        b00_R =  V2_R*(1 + (K2_R)/Q2_R + K2_R*K2_R) / (1 + (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R);
        
        b11_R = (2*V2_R*(K2_R*K2_R - 1)) / (1 + (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R);
        
        b22_R = V2_R*(1 - (K2_R)/Q2_R + K2_R*K2_R)/ (1 + (sqrt(V2_R)*K2_R)/Q2_R + V2_R*K2_R*K2_R);
        
        //LP filter
        if (lengR < 2){
            
            KLP_R = tan(PI*fcLP_R/44100);
            
            a2LP_R = 0;
            
            a1LP_R = (KLP_R-1)/(KLP_R+1);
            
            b0LP_R = KLP_R/(KLP_R+1);
            
            b1LP_R = KLP_R/(KLP_R+1);
            
            b2LP_R = 0;
            
        }else{
            
            KLP_R = tan(PI*fcLP_R/44100);
            
            a2LP_R = pow(((KLP_R-1)/(KLP_R+1)),2);
            
            a1LP_R = 2*((KLP_R-1)/(KLP_R+1));
            
            b0LP_R = pow((KLP_R/(KLP_R+1)),2);
            
            b1LP_R = 2*(KLP_R/(KLP_R+1))*(KLP_R/(KLP_R+1));
            
            b2LP_R = pow((KLP_R/(KLP_R+1)),2);
        
        }
        
        //final filter
        
        a1f_R = a1LP_R  + a1_R + a11_R;
        
        a2f_R = a2LP_R + a1_R * a1LP_R + a2_R + a11_R * a1LP_R + a11_R * a1_R + a22_R;
        
        a3f_R = a1_R * a2LP_R + a2_R * a1LP_R + a11_R * a2LP_R + a11_R * a1_R * a1LP_R + a11_R * a2_R + a22_R * a1LP_R + a22_R * a1_R;
        
        a4f_R = a2_R * a2LP_R + a11_R * a1_R * a2LP_R + a11_R * a2_R * a1LP_R + a22_R * a2LP_R + a22_R * a1_R * a1LP_R + a22_R * a2_R;
        
        a5f_R = a11_R * a2_R * a2LP_R + a22_R * a1_R * a2LP_R + a22_R * a2_R * a1LP_R;

        a6f_R = a22_R * a2LP_R * a2_R;

        b0f_R = inc_R*(b00_R * b0_R * b0LP_R);
        
        b1f_R = inc_R*(b00_R * b0_R * b1LP_R + b00_R * b1_R * b0LP_R + b11_R * b0_R * b0LP_R);
        
        b2f_R = inc_R*(b00_R * b0_R * b2LP_R + b00_R * b1_R * b1LP_R + b00_R * b2_R * b0LP_R + b11_R * b0_R * b1LP_R + b11_R * b1_R * b0LP_R + b0_R * b0LP_R * b22_R);

        b3f_R = inc_R*(b00_R * b1_R * b2LP_R + b00_R * b2_R * b1LP_R + b11_R * b0_R * b2LP_R + b11_R * b1_R * b1LP_R + b11_R * b2_R * b0LP_R + b22_R * b1_R * b0LP_R + b22_R * b0_R * b1LP_R);

        b4f_R = inc_R*(b2_R * b2LP_R * b00_R + b11_R * b1_R * b2LP_R + b11_R * b2_R * b1LP_R + b2_R * b0LP_R * b22_R + b22_R * b1_R * b1LP_R + b22_R * b0_R * b2LP_R);
        b5f_R = inc_R*(b11_R * b2_R * b2LP_R + b22_R * b2_R * b1LP_R + b22_R * b1_R * b2LP_R);
        
        b6f_R = inc_R*(b22_R * b2_R * b2LP_R);
        
        //left
        
        //1st filter
        
        K1_L = tan(PI*fc1_L/44100);
        
        a1_L = (2*(V1_L*K1_L*K1_L - 1))/(1 + (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L);
        
        a2_L = (1 - (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L)/(1 + (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L);
        
        b0_L = V1_L*(1 + (K1_L)/Q1_L + K1_L*K1_L) / (1 + (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L);
        
        b1_L = (2*V1_L*(K1_L*K1_L - 1)) / (1 + (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L);
        
        b2_L = V1_L*(1 - (K1_L)/Q1_L + K1_L*K1_L) / (1 + (sqrt(V1_L)*K1_L)/Q1_L + V1_L*K1_L*K1_L);
        
        //2nd filter
        
        K2_L = tan(PI*fc2_L/44100);
        
        a11_L = (2*(V2_L*K2_L*K2_L - 1))/ (1 + (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L);
        
        a22_L = (1 - (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L) / (1 + (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L);
        
        b00_L =  V2_L*(1 + (K2_L)/Q2_L + K2_L*K2_L) / (1 + (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L);
        
        b11_L = (2*V2_L*(K2_L*K2_L - 1)) / (1 + (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L);
        
        b22_L = V2_L*(1 - (K2_L)/Q2_L + K2_L*K2_L)/ (1 + (sqrt(V2_L)*K2_L)/Q2_L + V2_L*K2_L*K2_L);
        
        //LP filter
        if (lengL < 2){
            
            KLP_L = tan(PI*fcLP_L/44100);
            
            a2LP_L = 0;
            
            a1LP_L = (KLP_L-1)/(KLP_L+1);
            
            b0LP_L = KLP_L/(KLP_L+1);
            
            b1LP_L = KLP_L/(KLP_L+1);
            
            b2LP_L = 0;
            
        }else{
            
            KLP_L = tan(PI*fcLP_L/44100);
            
            a2LP_L = pow(((KLP_L-1)/(KLP_L+1)),2);
            
            a1LP_L = 2*((KLP_L-1)/(KLP_L+1));
            
            b0LP_L = pow((KLP_L/(KLP_L+1)),2);
            
            b1LP_L = 2*(KLP_L/(KLP_L+1))*(KLP_L/(KLP_L+1));
            
            b2LP_L = pow((KLP_L/(KLP_L+1)),2);
            
        }
        
        
        //final filter
        
        a1f_L = a1LP_L  + a1_L + a11_L;
        
        a2f_L = a2LP_L + a1_L * a1LP_L + a2_L + a11_L * a1LP_L + a11_L * a1_L + a22_L;
        
        a3f_L = a1_L * a2LP_L + a2_L * a1LP_L + a11_L * a2LP_L + a11_L * a1_L * a1LP_L + a11_L * a2_L + a22_L * a1LP_L + a22_L * a1_L;
        
        a4f_L = a2_L * a2LP_L + a11_L * a1_L * a2LP_L + a11_L * a2_L * a1LP_L + a22_L * a2LP_L + a22_L * a1_L * a1LP_L + a22_L * a2_L;
        
        a5f_L = a11_L * a2_L * a2LP_L + a22_L * a1_L * a2LP_L + a22_L * a2_L * a1LP_L;
        
        a6f_L = a22_L * a2LP_L * a2_L;
        
        b0f_L = inc_L*(b00_L * b0_L * b0LP_L);
        
        b1f_L = inc_L*(b00_L * b0_L * b1LP_L + b00_L * b1_L * b0LP_L + b11_L * b0_L * b0LP_L);
        
        b2f_L = inc_L*(b00_L * b0_L * b2LP_L + b00_L * b1_L * b1LP_L + b00_L * b2_L * b0LP_L + b11_L * b0_L * b1LP_L + b11_L * b1_L * b0LP_L + b0_L * b0LP_L * b22_L);
        
        b3f_L = inc_L*(b00_L * b1_L * b2LP_L + b00_L * b2_L * b1LP_L + b11_L * b0_L * b2LP_L + b11_L * b1_L * b1LP_L + b11_L * b2_L * b0LP_L + b22_L * b1_L * b0LP_L + b22_L * b0_L * b1LP_L);
    
        b4f_L = inc_L*(b2_L * b2LP_L * b00_L + b11_L * b1_L * b2LP_L + b11_L * b2_L * b1LP_L + b2_L * b0LP_L * b22_L + b22_L * b1_L * b1LP_L + b22_L * b0_L * b2LP_L);
        b5f_L = inc_L*(b11_L * b2_L * b2LP_L + b22_L * b2_L * b1LP_L + b22_L * b1_L * b2LP_L);
        
        b6f_L = inc_L*(b22_L * b2_L * b2LP_L);
        
        //ref
        
        //1st filter
        
        K1Ref_R = tan(PI*fc1Ref_R/44100);
        
        a1Ref_R = (2*(V1Ref_R*K1Ref_R*K1Ref_R - 1))/(1 + (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R);
        
        a2Ref_R = (1 - (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R)/(1 + (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R);
        
        b0Ref_R = V1Ref_R*(1 + (K1Ref_R)/Q1Ref_R + K1Ref_R*K1Ref_R) / (1 + (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R);
        
        b1Ref_R = (2*V1Ref_R*(K1Ref_R*K1Ref_R - 1)) / (1 + (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R);
        
        b2Ref_R = V1Ref_R*(1 - (K1Ref_R)/Q1Ref_R + K1Ref_R*K1Ref_R) / (1 + (sqrt(V1Ref_R)*K1Ref_R)/Q1Ref_R + V1Ref_R*K1Ref_R*K1Ref_R);
        
        //2nd filter
        
        K2Ref_R = tan(PI*fc2Ref_R/44100);
        
        a11Ref_R = (2*(V2Ref_R*K2Ref_R*K2Ref_R - 1))/ (1 + (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R);
        
        a22Ref_R = (1 - (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R) / (1 + (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R);
        
        b00Ref_R =  V2Ref_R*(1 + (K2Ref_R)/Q2Ref_R + K2Ref_R*K2Ref_R) / (1 + (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R);
        
        b11Ref_R = (2*V2Ref_R*(K2Ref_R*K2Ref_R - 1)) / (1 + (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R);
        
        b22Ref_R = V2Ref_R*(1 - (K2Ref_R)/Q2Ref_R + K2Ref_R*K2Ref_R)/ (1 + (sqrt(V2Ref_R)*K2Ref_R)/Q2Ref_R + V2Ref_R*K2Ref_R*K2Ref_R);
        
        //LP filter
        if (length_totR < 2){
            
            KLPRef_R = tan(PI*fcLPRef_R/44100);
            
            a2LPRef_R = 0;
            
            a1LPRef_R = (KLPRef_R-1)/(KLPRef_R+1);
            
            b0LPRef_R = KLPRef_R/(KLPRef_R+1);
            
            b1LPRef_R = KLPRef_R/(KLPRef_R+1);
            
            b2LPRef_R = 0;
            
        }else{
            
            KLPRef_R = tan(PI*fcLPRef_R/44100);
            
            a2LPRef_R = pow(((KLPRef_R-1)/(KLPRef_R+1)),2);
            
            a1LPRef_R = 2*((KLPRef_R-1)/(KLPRef_R+1));
            
            b0LPRef_R = pow((KLPRef_R/(KLPRef_R+1)),2);
            
            b1LPRef_R = 2*(KLPRef_R/(KLPRef_R+1))*(KLPRef_R/(KLPRef_R+1));
            
            b2LPRef_R = pow((KLPRef_R/(KLPRef_R+1)),2);
            
        }
        
        
        //final filter
        
        a1fRef_R = a1LPRef_R  + a1Ref_R + a11Ref_R;
        
        a2fRef_R = a2LPRef_R + a1Ref_R * a1LPRef_R + a2Ref_R + a11Ref_R * a1LPRef_R + a11Ref_R * a1Ref_R + a22Ref_R;
        
        a3fRef_R = a1Ref_R * a2LPRef_R + a2Ref_R * a1LPRef_R + a11Ref_R * a2LPRef_R + a11Ref_R * a1Ref_R * a1LPRef_R + a11Ref_R * a2Ref_R + a22Ref_R * a1LPRef_R + a22Ref_R * a1Ref_R;
        
        a4fRef_R = a2Ref_R * a2LPRef_R + a11Ref_R * a1Ref_R * a2LPRef_R + a11Ref_R * a2Ref_R * a1LPRef_R + a22Ref_R * a2LPRef_R + a22Ref_R * a1Ref_R * a1LPRef_R + a22Ref_R * a2Ref_R;
        
        a5fRef_R = a11Ref_R * a2Ref_R * a2LPRef_R + a22Ref_R * a1Ref_R * a2LPRef_R + a22Ref_R * a2Ref_R * a1LPRef_R;
        
        a6fRef_R = a22Ref_R * a2LPRef_R * a2Ref_R;
        
        b0fRef_R = incRef_R*(b00Ref_R * b0Ref_R * b0LPRef_R);
        
        b1fRef_R = incRef_R*(b00Ref_R * b0Ref_R * b1LPRef_R + b00Ref_R * b1Ref_R * b0LPRef_R + b11Ref_R * b0Ref_R * b0LPRef_R);
        
        b2fRef_R = incRef_R*(b00Ref_R * b0Ref_R * b2LPRef_R + b00Ref_R * b1Ref_R * b1LPRef_R + b00Ref_R * b2Ref_R * b0LPRef_R + b11Ref_R * b0Ref_R * b1LPRef_R + b11Ref_R * b1Ref_R * b0LPRef_R + b0Ref_R * b0LPRef_R * b22Ref_R);
        
        b3fRef_R = incRef_R*(b00Ref_R * b1Ref_R * b2LPRef_R + b00Ref_R * b2Ref_R * b1LPRef_R + b11Ref_R * b0Ref_R * b2LPRef_R + b11Ref_R * b1Ref_R * b1LPRef_R + b11Ref_R * b2Ref_R * b0LPRef_R + b22Ref_R * b1Ref_R * b0LPRef_R + b22Ref_R * b0Ref_R * b1LPRef_R);
        
        b4fRef_R = incRef_R*(b2Ref_R * b2LPRef_R * b00Ref_R + b11Ref_R * b1Ref_R * b2LPRef_R + b11Ref_R * b2Ref_R * b1LPRef_R + b2Ref_R * b0LPRef_R * b22Ref_R + b22Ref_R * b1Ref_R * b1LPRef_R + b22Ref_R * b0Ref_R * b2LPRef_R);
        b5fRef_R = incRef_R*(b11Ref_R * b2Ref_R * b2LPRef_R + b22Ref_R * b2Ref_R * b1LPRef_R + b22Ref_R * b1Ref_R * b2LPRef_R);
        
        b6fRef_R = incRef_R*(b22Ref_R * b2Ref_R * b2LPRef_R);
        
        
        //left
        
        //1st filter
        
        K1Ref_L = tan(PI*fc1Ref_L/44100);
        
        a1Ref_L = (2*(V1Ref_L*K1Ref_L*K1Ref_L - 1))/(1 + (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L);
        
        a2Ref_L = (1 - (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L)/(1 + (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L);
        
        b0Ref_L = V1Ref_L*(1 + (K1Ref_L)/Q1Ref_L + K1Ref_L*K1Ref_L) / (1 + (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L);
        
        b1Ref_L = (2*V1Ref_L*(K1Ref_L*K1Ref_L - 1)) / (1 + (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L);
        
        b2Ref_L = V1Ref_L*(1 - (K1Ref_L)/Q1Ref_L + K1Ref_L*K1Ref_L) / (1 + (sqrt(V1Ref_L)*K1Ref_L)/Q1Ref_L + V1Ref_L*K1Ref_L*K1Ref_L);
        
        //2nd filter
        
        K2Ref_L = tan(PI*fc2Ref_L/44100);
        
        a11Ref_L = (2*(V2Ref_L*K2Ref_L*K2Ref_L - 1))/ (1 + (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L);
        
        a22Ref_L = (1 - (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L) / (1 + (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L);
        
        b00Ref_L =  V2Ref_L*(1 + (K2Ref_L)/Q2Ref_L + K2Ref_L*K2Ref_L) / (1 + (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L);
        
        b11Ref_L = (2*V2Ref_L*(K2Ref_L*K2Ref_L - 1)) / (1 + (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L);
        
        b22Ref_L = V2Ref_L*(1 - (K2Ref_L)/Q2Ref_L + K2Ref_L*K2Ref_L)/ (1 + (sqrt(V2Ref_L)*K2Ref_L)/Q2Ref_L + V2Ref_L*K2Ref_L*K2Ref_L);
        
        //LP filter
        if (length_totL < 2){
            
            KLPRef_L = tan(PI*fcLPRef_L/44100);
            
            a2LPRef_L = 0;
            
            a1LPRef_L = (KLPRef_L-1)/(KLPRef_L+1);
            
            b0LPRef_L = KLPRef_L/(KLPRef_L+1);
            
            b1LPRef_L = KLPRef_L/(KLPRef_L+1);
            
            b2LPRef_L = 0;
            
        }else{
            
            KLPRef_L = tan(PI*fcLPRef_L/44100);
            
            a2LPRef_L = pow(((KLPRef_L-1)/(KLPRef_L+1)),2);
            
            a1LPRef_L = 2*((KLPRef_L-1)/(KLPRef_L+1));
            
            b0LPRef_L = pow((KLPRef_L/(KLPRef_L+1)),2);
            
            b1LPRef_L = 2*(KLPRef_L/(KLPRef_L+1))*(KLPRef_L/(KLPRef_L+1));
            
            b2LPRef_L = pow((KLPRef_L/(KLPRef_L+1)),2);
            
        }

        
        //final filter
        
        a1fRef_L = a1LPRef_L  + a1Ref_L + a11Ref_L;
        
        a2fRef_L = a2LPRef_L + a1Ref_L * a1LPRef_L + a2Ref_L + a11Ref_L * a1LPRef_L + a11Ref_L * a1Ref_L + a22Ref_L;
        
        a3fRef_L = a1Ref_L * a2LPRef_L + a2Ref_L * a1LPRef_L + a11Ref_L * a2LPRef_L + a11Ref_L * a1Ref_L * a1LPRef_L + a11Ref_L * a2Ref_L + a22Ref_L * a1LPRef_L + a22Ref_L * a1Ref_L;
        
        a4fRef_L = a2Ref_L * a2LPRef_L + a11Ref_L * a1Ref_L * a2LPRef_L + a11Ref_L * a2Ref_L * a1LPRef_L + a22Ref_L * a2LPRef_L + a22Ref_L * a1Ref_L * a1LPRef_L + a22Ref_L * a2Ref_L;
        
        a5fRef_L = a11Ref_L * a2Ref_L * a2LPRef_L + a22Ref_L * a1Ref_L * a2LPRef_L + a22Ref_L * a2Ref_L * a1LPRef_L;
        
        a6fRef_L = a22Ref_L * a2LPRef_L * a2Ref_L;
        
        b0fRef_L = incRef_L*(b00Ref_L * b0Ref_L * b0LPRef_L);
        
        b1fRef_L = incRef_L*(b00Ref_L * b0Ref_L * b1LPRef_L + b00Ref_L * b1Ref_L * b0LPRef_L + b11Ref_L * b0Ref_L * b0LPRef_L);
        
        b2fRef_L = incRef_L*(b00Ref_L * b0Ref_L * b2LPRef_L + b00Ref_L * b1Ref_L * b1LPRef_L + b00Ref_L * b2Ref_L * b0LPRef_L + b11Ref_L * b0Ref_L * b1LPRef_L + b11Ref_L * b1Ref_L * b0LPRef_L + b0Ref_L * b0LPRef_L * b22Ref_L);
        
        b3fRef_L = incRef_L*(b00Ref_L * b1Ref_L * b2LPRef_L + b00Ref_L * b2Ref_L * b1LPRef_L + b11Ref_L * b0Ref_L * b2LPRef_L + b11Ref_L * b1Ref_L * b1LPRef_L + b11Ref_L * b2Ref_L * b0LPRef_L + b22Ref_L * b1Ref_L * b0LPRef_L + b22Ref_L * b0Ref_L * b1LPRef_L);
        
        b4fRef_L = incRef_L*(b2Ref_L * b2LPRef_L * b00Ref_L + b11Ref_L * b1Ref_L * b2LPRef_L + b11Ref_L * b2Ref_L * b1LPRef_L + b2Ref_L * b0LPRef_L * b22Ref_L + b22Ref_L * b1Ref_L * b1LPRef_L + b22Ref_L * b0Ref_L * b2LPRef_L);
        b5fRef_L = incRef_L*(b11Ref_L * b2Ref_L * b2LPRef_L + b22Ref_L * b2Ref_L * b1LPRef_L + b22Ref_L * b1Ref_L * b2LPRef_L);
        
        b6fRef_L = incRef_L*(b22Ref_L * b2Ref_L * b2LPRef_L);
        
        
        // DSP cycle
        for (int i = 0; i < n; ++i)
        {
            
            inR[0] = (t_sample)input[i];
            inL[0] = (t_sample)input[i];
            
            if (ref[n-1] == 0) {
                
                
                outR[0] = b0f_R*inR[0] + b1f_R*inR[1] + b2f_R*inR[2] + b3f_R*inR[3] + b4f_R*inR[4] + b5f_R*inR[5] + b6f_R*inR[6] - a1f_R*outR[1] - a2f_R*outR[2] - a3f_R*outR[3] - a4f_R*outR[4] - a5f_R*outR[5] - a6f_R*outR[6];
                
                outL[0] = b0f_L*inL[0] + b1f_L*inL[1] + b2f_L*inL[2] + b3f_L*inL[3] + b4f_L*inL[4] + b5f_L*inL[5] + b6f_L*inL[6] - a1f_L*outL[1] - a2f_L*outL[2] - a3f_L*outL[3] - a4f_L*outL[4] - a5f_L*outL[5] - a6f_L*outL[6];
                
                
                
                
                bufferL[delaySamplesL] = outL[0];
                bufferR[delaySamplesR] = outR[0];
                
                
                outputR[i] = dry*(t_sample)input[i] + wet*gR*bufferR[0];
                outputL[i] = dry*(t_sample)input[i] + wet*gL*bufferL[0];
                
                
                for (int k = 5; k >= 0; k--) {
                    
                    outL[k+1] = outL[k];
                    outR[k+1] = outR[k];
                    inL[k+1] = inL[k];
                    inR[k+1] = inR[k];
                    
                }
                
                inL[0] = 0;
                inR[0] = 0;
                outL[0] = 0;
                outR[0] = 0;
                
                for (int k = 0; k < len; k++) {
                    
                    bufferR[k] = bufferR[k+1];
                    bufferL[k] = bufferL[k+1];
                }
                
                bufferL[len] = 0;
                bufferR[len] = 0;
                
            }else if (ref[n-1] == 1) {
                
                
                outR[0] = b0f_R*inR[0] + b1f_R*inR[1] + b2f_R*inR[2] + b3f_R*inR[3] + b4f_R*inR[4] + b5f_R*inR[5] + b6f_R*inR[6] - a1f_R*outR[1] - a2f_R*outR[2] - a3f_R*outR[3] - a4f_R*outR[4] - a5f_R*outR[5] - a6f_R*outR[6];
                
                outL[0] = b0f_L*inL[0] + b1f_L*inL[1] + b2f_L*inL[2] + b3f_L*inL[3] + b4f_L*inL[4] + b5f_L*inL[5] + b6f_L*inL[6] - a1f_L*outL[1] - a2f_L*outL[2] - a3f_L*outL[3] - a4f_L*outL[4] - a5f_L*outL[5] - a6f_L*outL[6];
                
                
                //
                out2R[0] = b0fRef_R*outR[0] + b1fRef_R*outR[1] + b2fRef_R*outR[2] + b3fRef_R*outR[3] + b4fRef_R*outR[4] + b5fRef_R*outR[5] + b6fRef_R*outR[6] - a1fRef_R*out2R[1] - a2fRef_R*out2R[2] - a3fRef_R*out2R[3] - a4fRef_R*out2R[4] - a5fRef_R*out2R[5] - a6fRef_R*out2R[6];
                
                out2L[0] = b0fRef_L*outL[0] + b1fRef_L*outL[1] + b2fRef_L*outL[2] + b3fRef_L*outL[3] + b4fRef_L*outL[4] + b5fRef_L*outL[5] + b6fRef_L*outL[6] - a1fRef_L*out2L[1] - a2fRef_L*out2L[2] - a3fRef_L*out2L[3] - a4fRef_L*out2L[4] - a5fRef_L*out2L[5] - a6fRef_L*out2L[6];
            
                
                out3R[0] = br[0]*out2R[0] + br[1]*out2R[1] + br[2]*out2R[2] + br[3]*out2R[3] - ar[0]*out3R[1] - ar[1]*out3R[2] - ar[2]*out3R[3];
                
                out3L[0] = br[0]*out2L[0] + br[1]*out2L[1] + br[2]*out2L[2] + br[3]*out2L[3] - ar[0]*out3L[1] - ar[1]*out3L[2] - ar[2]*out3L[3];

                
                bufferL[delaySamplesL] = bufferL[delaySamplesL] + gL*outL[0];
                bufferR[delaySamplesR] = bufferR[delaySamplesR] + gR*outR[0];
                
                bufferL[delaySamplesL_tot] = bufferL[delaySamplesL_tot] + gRef_L*out3L[0];
                bufferR[delaySamplesR_tot] = bufferR[delaySamplesR_tot] + gRef_R*out3R[0];
                
                
                outputR[i] = dry*(t_sample)input[i] + wet*(bufferR[0]);
                outputL[i] = dry*(t_sample)input[i] + wet*(bufferL[0]);
                
                
                for (int k = 5; k >= 0; k--) {
                    
                    outL[k+1] = outL[k];
                    outR[k+1] = outR[k];
                    inL[k+1] = inL[k];
                    inR[k+1] = inR[k];
                    out2L[k+1] = out2L[k];
                    out2R[k+1] = out2R[k];
                    
                }
                
                for (int k = 2; k >= 0; k--) {
                    
                    out3L[k+1] = out3L[k];
                    out3R[k+1] = out3R[k];
                    
                }
                
                
                for (int k = 0; k < len; k++) {
                    
                    bufferR[k] = bufferR[k+1];
                    bufferL[k] = bufferL[k+1];
                }
                
                bufferL[len] = 0;
                bufferR[len] = 0;
                
                
            }// end if ref
            
        }//end dsp cycle
        
        return;
    } //end process cycle
    
    //global variables
private:
    
    int len;
    
    float *outR;
    float *outL;
    float *out2R;
    float *out2L;
    float *out3R;
    float *out3L;
    
    float *inR;
    float *inL;
    
    float *bufferR;
    float *bufferL;
    
    float fc1_R, fc1Ref_R;
    float fc2_R, fc2Ref_R;
    float inc_R, incRef_R;
    
    float fc1_L, fc1Ref_L;
    float fc2_L, fc2Ref_L;
    float inc_L, incRef_L;
    
    float fcLP_R, fcLPRef_R;
    float fcLP_0_R, fcLPRef_0_R;
    float fcLP_1_R, fcLPRef_1_R;
    
    float fcLP_L, fcLPRef_L;
    float fcLP_0_L, fcLPRef_0_L;
    float fcLP_1_L, fcLPRef_1_L;
    
    float Q1_R, Q1Ref_R;
    float Q2_R, Q2Ref_R;
    float G1_R, G1Ref_R;
    float G2_R, G2Ref_R;
    float V1_R, V1Ref_R;
    float V2_R, V2Ref_R;
    
    float Q1_L, Q1Ref_L;
    float Q2_L, Q2Ref_L;
    float G1_L, G1Ref_L;
    float G2_L, G2Ref_L;
    float V1_L, V1Ref_L;
    float V2_L, V2Ref_L;
    
    float K1_R, K1Ref_R;
    float K1_L, K1Ref_L;
    
    float a1_R, a1Ref_R;
    float a1_L, a1Ref_L;
    
    float a2_R, a2Ref_R;
    float a2_L, a2Ref_L;
    
    float b0_R, b0Ref_R;
    float b0_L, b0Ref_L;
    
    float b1_R, b1Ref_R;
    float b1_L, b1Ref_L;
    
    float b2_R, b2Ref_R;
    float b2_L, b2Ref_L;
    
    float K2_R, K2Ref_R;
    float K2_L, K2Ref_L;
    
    float a11_R, a11Ref_R;
    float a11_L, a11Ref_L;
    
    float a22_R, a22Ref_R;
    float a22_L, a22Ref_L;
    
    float b00_R, b00Ref_R;
    float b00_L, b00Ref_L;
    
    float b11_R, b11Ref_R;
    float b11_L, b11Ref_L;
    
    float b22_R, b22Ref_R;
    float b22_L, b22Ref_L;
    
    float a1f_R, a1fRef_R;
    float a1f_L, a1fRef_L;
    
    float a2f_R, a2fRef_R;
    float a2f_L, a2fRef_L;
    
    float a3f_R, a3fRef_R;
    float a3f_L, a3fRef_L;
    
    float a4f_R, a4fRef_R;
    float a4f_L, a4fRef_L;
    
    float a5f_R, a5fRef_R;
    float a5f_L, a5fRef_L;
    
    float a6f_R, a6fRef_R;
    float a6f_L, a6fRef_L;
    
    float b0f_R, b0fRef_R;
    float b0f_L, b0fRef_L;
    
    float b1f_R, b1fRef_R;
    float b1f_L, b1fRef_L;
    
    float b2f_R, b2fRef_R;
    float b2f_L, b2fRef_L;
    
    float b3f_R, b3fRef_R;
    float b3f_L, b3fRef_L;
    
    float b4f_R, b4fRef_R;
    float b4f_L, b4fRef_L;
    
    float b5f_R, b5fRef_R;
    float b5f_L, b5fRef_L;
    
    float b6f_R, b6fRef_R;
    float b6f_L, b6fRef_L;
    
    float KLP_R, KLPRef_R;
    float KLP_L, KLPRef_L;
    
    float a2LP_R, a2LPRef_R;
    float a2LP_L, a2LPRef_L;
    
    float a1LP_R, a1LPRef_R;
    float a1LP_L, a1LPRef_L;
    
    float b0LP_R, b0LPRef_R;
    float b0LP_L, b0LPRef_L;
    
    float b1LP_R, b1LPRef_R;
    float b1LP_L, b1LPRef_L;
    
    float b2LP_R, b2LPRef_R;
    float b2LP_L, b2LPRef_L;
    
    double ar0[3];
    double br0[4];
    double ar1[3];
    double br1[4];
    double ar2[3];
    double br2[4];
    double ar3[3];
    double br3[4];
    double ar4[3];
    double br4[4];
    double ar5[3];
    double br5[4];
    double ar6[3];
    double br6[4];
    double ar7[3];
    double br7[4];
    double ar8[3];
    double br8[4];
    double ar9[3];
    double br9[4];
    double ar10[3];
    double br10[4];
    double ar11[3];
    double br11[4];
    double ar12[3];
    double br12[4];
    double ar13[3];
    double br13[4];
    double ar[3];
    double br[4];
    
/*    float incEnd;
    float fcEnd;
    float fLPEnd;
    float K1End;
    float G1End;
    float V1End;
    float Q1End;
    float KLPEnd;
    
    float a1End;
    float a2End;
    float b0End;
    float b1End;
    float b2End;
    
    float a1LPEnd;
    float b0LPEnd;
    float b1LPEnd;
    
    float a3f_End;
    float a2f_End;
    float a1f_End;
    float b3f_End;
    float b2f_End;
    float b1f_End;
    float b0f_End;*/
    
};

/* the data structure for each copy of "gardenfilter_tilde".  In this case we
 only need pd's obligatory header (of type t_object). */
typedef struct VIRTUAL_TUBE_DELAY_tilde
{
    t_object 		x_ob;
    VIRTUAL_TUBE_DELAYObj	*dd;
    float			default_input;
} t_VIRTUAL_TUBE_DELAY_tilde;

/* this is a pointer to the class for "gardenfilter_tilde", which is created in the
 "setup" routine below and used to create new ones in the "new" routine. */
t_class *VIRTUAL_TUBE_DELAY_tilde_class;

/* ------------------------------------------------ */
/* ------------------------------------------------ */

/* this is called when a new "gardenfilter_tilde" object is created. */
void *VIRTUAL_TUBE_DELAY_tilde_new(void)
{
    post("VIRTUAL_TUBE_DELAY_new");
    
    t_VIRTUAL_TUBE_DELAY_tilde *x = (t_VIRTUAL_TUBE_DELAY_tilde *)pd_new(VIRTUAL_TUBE_DELAY_tilde_class);
    x->default_input = 0;
    x->dd = NULL;
    
    try
    {
        // call to the constructor
        x->dd = new VIRTUAL_TUBE_DELAYObj();
        
    }
    catch (int n)
    {
        x->dd = 0;
        post("VIRTUAL_TUBE_DELAY_new catched error ");
        return (void*) 0;
    }
    
    // delaytime inlet left
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, &s_signal, &s_signal);
    // delaytime inlet right
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, &s_signal, &s_signal);
    // gain inlet left
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, &s_signal, &s_signal);
    // gain inlet right
    inlet_new(&x->x_ob, &x->x_ob.ob_pd, &s_signal, &s_signal);
    // param inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // size inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // ref inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // lengthRefL inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // lengthRefR inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // gainRefL inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    // gainRefR inlet
    inlet_new(&x->x_ob , &x->x_ob.ob_pd, &s_signal, &s_signal);
    
    // stereo outlet
    outlet_new(&x->x_ob, &s_signal);
    outlet_new(&x->x_ob, &s_signal);
    
    return (void *)x;
}

static void VIRTUAL_TUBE_DELAY_tilde_delete(t_VIRTUAL_TUBE_DELAY_tilde *x)
{
    post("VIRTUAL_TUBE_DELAY_delete");
    
    if (x->dd) {
        delete x->dd; x->dd = NULL;
    }
    
    
}

t_int *VIRTUAL_TUBE_DELAY_tilde_perform(t_int *w)
{
    t_VIRTUAL_TUBE_DELAY_tilde *x = (t_VIRTUAL_TUBE_DELAY_tilde *)(w[1]);   //obj ref
    
    // 4 signal input: signal, time, gain, dry/wet and changeF
    t_sample  *input = (t_sample *)(w[2]);  //input samples mono
    t_sample  *lengthL = (t_sample *)(w[3]);  //time left
    t_sample  *lengthR = (t_sample *)(w[4]);  //time right
    t_sample  *gainL = (t_sample *)(w[5]);  //gain left
    t_sample  *gainR = (t_sample *)(w[6]);  //gain right
    t_sample  *size = (t_sample *)(w[7]);   //size
    t_sample  *ref = (t_sample *)(w[8]);   //ref
    t_sample  *lengthRefL = (t_sample *)(w[9]); //lenght ref left
    t_sample  *lengthRefR = (t_sample *)(w[10]); //lenght ref right
    t_sample  *gainRefL = (t_sample *)(w[11]);   //gain ref left
    t_sample  *gainRefR = (t_sample *)(w[12]);   //gain ref right
    t_sample  *dry_wet = (t_sample *)(w[13]);  //dry/wet
    
    
    // 2 signal output: filtered stereo signal
    t_sample *outputL = (t_sample *)(w[14]); //output samples left
    t_sample *outputR = (t_sample *)(w[15]); //output samples right
    
    int n = (int)(w[16]);
    
    x->dd->process(input, lengthL, lengthR, gainL, gainR, size, ref, lengthRefL, lengthRefR, gainRefL, gainRefR, dry_wet, outputR, outputL, n);
    
    return (w+17);
}

void VIRTUAL_TUBE_DELAY_tilde_dsp(t_VIRTUAL_TUBE_DELAY_tilde *x, t_signal **sp)
{
    dsp_add(VIRTUAL_TUBE_DELAY_tilde_perform,
            16,
            x,
            sp[0]->s_vec, //inlet1
            sp[1]->s_vec, //inlet2
            sp[2]->s_vec, //inlet3
            sp[3]->s_vec, //inlet4
            sp[4]->s_vec, //inlet5
            sp[5]->s_vec, //inlet6
            sp[6]->s_vec, //inlet7
            sp[7]->s_vec, //inlet8
            sp[8]->s_vec, //inlet9
            sp[9]->s_vec, //inlet10
            sp[10]->s_vec, //inlet11
            sp[11]->s_vec, //inlet12
            sp[12]->s_vec, //outlet1
            sp[13]->s_vec, //outlet2
            sp[0]->s_n); //vector size
}

/* this is called once at setup time, when this code is loaded into Pd. */
extern "C"	{
#ifdef WIN32
    __declspec(dllexport) void VIRTUAL_TUBE_DELAY_tilde_setup(void)
#else
    void VIRTUAL_TUBE_DELAY_tilde_setup(void)
#endif
    {
        post("VIRTUAL_TUBE_DELAY_tilde_setup");
        // creation of the gardenfilter~ instance
        VIRTUAL_TUBE_DELAY_tilde_class = class_new(gensym("VIRTUAL_TUBE_DELAY~"),
                                             (t_newmethod)VIRTUAL_TUBE_DELAY_tilde_new,
                                             (t_method)VIRTUAL_TUBE_DELAY_tilde_delete, sizeof(t_VIRTUAL_TUBE_DELAY_tilde),
                                             0,
                                             (t_atomtype) 0);
        
        // sound processing
        class_addmethod(VIRTUAL_TUBE_DELAY_tilde_class,
                        (t_method)VIRTUAL_TUBE_DELAY_tilde_dsp, gensym("dsp"), (t_atomtype) 0);
        
        // signal input
        CLASS_MAINSIGNALIN(VIRTUAL_TUBE_DELAY_tilde_class, t_VIRTUAL_TUBE_DELAY_tilde, default_input);
    }
}