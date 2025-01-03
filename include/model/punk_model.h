/** OBJ_to_ARRAY_convert (ttrossea)
**
** - punk -
***/

#ifndef PUNK_MODEL
    #define PUNK_MODEL
    #include "model.h"

    /** #define PUNK_MAX_VERTICES 3083
    #define PUNK_MAX_NORMALS 314
    #define PUNK_MAX_FACES 334
 **/

    static const double        punk_v[PUNK_MAX_VERTICES] =
    {
        308, 3, 0,
        0.836120, -0.593216, -0.240727, 
        0.836120, -0.593216, 0.352931, 
        -0.779900, -0.590816, 0.767436, 
        -0.779899, -0.590816, -0.135621, 
        1.175097, 2.319142, -0.379754, 
        1.245175, 2.218042, 0.052473, 
        -1.164677, 1.920441, 0.838028, 
        -1.131382, 2.095747, -0.458333, 
        -0.220100, -0.590816, -0.135621, 
        -0.220100, -0.590816, 0.767436, 
        0.000000, 2.071364, -0.912974, 
        -0.000001, 1.726610, 1.233829, 
        0.163880, -0.593216, -0.240727, 
        -1.000000, 1.408277, -0.411563, 
        0.163880, -0.593216, 0.352931, 
        -1.000000, 1.409244, 0.282722, 
        1.000000, 1.097603, -0.333699, 
        1.000000, 1.097603, 0.333699, 
        0.000000, 0.018820, -0.746635, 
        0.000000, -0.421540, 1.000000, 
        0.405226, 2.378730, -0.591746, 
        0.405226, 2.268519, 0.405227, 
        -0.405227, 2.268519, 0.405226, 
        -0.405226, 2.378730, -0.591746, 
        -0.609947, -0.035553, -0.533912, 
        -0.878702, 2.100697, 1.074881, 
        -0.669700, 2.223177, -0.770489, 
        0.752650, -0.072028, -0.384278, 
        0.752650, -0.270229, 0.851339, 
        0.698603, 2.310504, -0.813648, 
        0.999999, 1.980182, 1.000001, 
        0.357598, 3.204061, -0.357598, 
        -0.357598, 3.204061, -0.357598, 
        0.357598, 3.204061, 0.357598, 
        -0.357598, 3.204061, 0.357598, 
        0.856852, -0.934860, -0.375707, 
        0.856852, -0.934860, 0.104992, 
        0.184611, -0.934860, -0.375707, 
        0.184611, -0.934860, 0.104992, 
        -0.160824, -0.916881, 0.159810, 
        -0.720623, -0.916881, 0.159810, 
        -0.160824, -0.916881, 0.655569, 
        -0.720624, -0.916881, 0.655569, 
        1.495768, -0.487661, 0.172509, 
        -1.167769, 2.554239, 0.105323, 
        0.574721, 2.501099, 0.000000, 
        -0.569635, 2.453149, 0.000000, 
        0.000000, 3.802993, -0.882948, 
        -0.000000, 3.602374, 0.845818, 
        0.356218, 3.240980, 0.000000, 
        -0.356218, 3.240980, 0.000000, 
        0.444184, 2.922603, -0.444184, 
        0.444184, 2.922603, 0.444184, 
        -0.444184, 2.922603, -0.444184, 
        -0.444184, 2.922603, 0.444184, 
        -0.000000, 2.928068, 0.521145, 
        -0.521145, 2.928068, 0.000000, 
        0.000000, 2.928068, -1.198034, 
        -0.000000, 4.237062, 0.000000, 
        0.521144, 2.928068, 0.000000, 
        -0.195143, 2.456471, -0.589878, 
        -0.246653, 2.322167, 0.527624, 
        0.626163, 2.322167, 0.195143, 
        -0.594714, 2.374942, -0.262295, 
        -0.181491, 3.230832, -0.348891, 
        -0.181491, 3.230832, 0.348891, 
        0.348891, 3.230832, 0.181491, 
        -0.348891, 3.230832, -0.181491, 
        0.430118, 3.076267, -0.430117, 
        0.467434, 2.593400, 0.467434, 
        -0.430118, 3.076267, -0.430118, 
        -0.430118, 3.076267, 0.430118, 
        0.195143, 2.476815, -0.589878, 
        0.224049, 2.322167, 0.527624, 
        0.626163, 2.322167, -0.195143, 
        -0.594714, 2.322167, 0.195143, 
        0.181491, 3.230832, -0.348891, 
        0.181491, 3.230832, 0.348891, 
        0.348891, 3.230832, -0.181491, 
        -0.348891, 3.230832, 0.181491, 
        0.467434, 2.593400, -0.467433, 
        0.430118, 3.076267, 0.430118, 
        -0.467434, 2.593400, -0.467434, 
        -0.467434, 2.593400, 0.467434, 
        -0.000000, 3.087816, 0.494740, 
        -0.234600, 2.925336, 0.499341, 
        0.234599, 2.925336, 0.499341, 
        -0.494740, 3.087816, 0.000000, 
        -0.528957, 2.614645, 0.000000, 
        -0.499341, 2.925336, -0.234599, 
        -0.499341, 2.925336, 0.234600, 
        0.000000, 3.087816, -0.494739, 
        0.000000, 2.614645, -0.528957, 
        0.234600, 2.925336, -0.499340, 
        -0.234599, 2.925336, -0.499341, 
        -0.000000, 3.319544, 0.232083, 
        -0.000000, 3.319544, -0.232083, 
        0.232083, 3.319544, 0.000000, 
        -0.232083, 3.319544, 0.000000, 
        0.494740, 3.087816, 0.000000, 
        0.528957, 2.614645, 0.000000, 
        0.499341, 2.925336, 0.234600, 
        0.499341, 2.925336, -0.234599, 
        0.514872, 2.604023, -0.248046, 
        0.514872, 2.604023, 0.248046, 
        0.478063, 3.082041, 0.227914, 
        -0.227914, 3.296448, -0.227914, 
        0.227914, 3.296448, -0.227913, 
        0.227914, 3.296448, 0.227914, 
        -0.248046, 2.604023, -0.514872, 
        0.248046, 2.604023, -0.514872, 
        0.227914, 3.082041, -0.478063, 
        -0.514872, 2.604023, 0.248046, 
        -0.514872, 2.604023, -0.248046, 
        -0.478063, 3.082041, -0.227914, 
        0.248046, 2.604023, 0.514872, 
        -0.248046, 2.604023, 0.514872, 
        -0.227914, 3.082041, 0.478063, 
        0.227913, 3.082041, 0.478063, 
        -0.478063, 3.082041, 0.227914, 
        -0.227914, 3.082041, -0.478063, 
        -0.227914, 3.296448, 0.227914, 
        0.478063, 3.082041, -0.227913, 
        1.532238, 1.075396, 0.134585, 
        1.150299, 0.948354, 0.603947, 
        1.624767, 1.663106, 0.134586, 
        1.150299, 1.663106, 0.603946, 
        0.224049, 2.320287, 0.468382, 
        -0.000000, 2.275447, 0.473008, 
        -0.108328, 2.640496, 0.462260, 
        -0.108485, 2.758267, 0.461940, 
        0.216398, 2.749950, 0.447340, 
        -0.246653, 2.320287, 0.468382, 
        -0.219272, 2.756395, 0.447340, 
        0.220872, 2.628147, 0.455829, 
        -0.223514, 2.634592, 0.455829, 
        0.000000, 2.520742, -0.589878, 
        0.947437, -0.530316, 0.798897, 
        2.074089, 2.249534, -0.160429, 
        0.628149, 2.251617, 1.464391, 
        1.624767, 1.663106, 0.134586, 
        1.150299, 1.663106, 0.603946, 
        1.424499, 2.114135, 0.030257, 
        1.510584, 1.919333, -0.313947, 
        1.312383, 1.022979, -0.313947, 
        1.075150, 1.022979, 0.254433, 
        0.699459, 1.005715, -0.614046, 
        0.874638, 0.762946, 0.874639, 
        -0.780597, 0.736846, 0.939620, 
        -0.658418, 0.998584, -0.558757, 
        0.000000, 0.758389, -0.761394, 
        -0.000000, 0.762946, 1.000000, 
        1.000000, 1.450106, -0.521413, 
        1.000000, 1.450106, 0.333699, 
        1.919835, 0.433094, -0.196462, 
        1.624767, 1.300857, 0.134585, 
        1.150299, 1.300857, 0.603947, 
        0.702956, 0.437183, 1.195921, 
        1.150299, 1.300857, 0.603947, 
        1.075149, 1.375481, 0.254433, 
        1.436665, 1.375481, -0.497784, 
        1.559131, -0.487684, 0.234134, 
        1.010800, -0.530340, 0.860522, 
        2.154631, 2.249497, -0.049578, 
        0.708479, 2.245786, 1.575242, 
        2.018062, 0.433057, -0.100929, 
        0.800926, 0.430080, 1.291453, 
        0.000000, 2.361008, -0.796191, 
        1.316227, 2.250576, 0.629742, 
        1.399540, -0.509012, 0.660508, 
        1.649832, 2.247642, 0.933215, 
        -1.100244, 1.179328, 0.291421, 
        -1.174131, 1.171940, -0.269127, 
        -1.425983, 1.457875, 0.444056, 
        -1.508422, 1.736272, -0.453614, 
        -1.554471, 1.171940, -0.291354, 
        1.229231, -0.519676, 0.831904, 
        -1.100244, 1.179328, 0.291421, 
        -1.274857, 1.161638, 0.686626, 
        -1.293837, 0.818767, 0.288083, 
        -1.192534, 0.810370, 0.298675, 
        -1.437940, 1.181523, 0.660368, 
        -1.307670, 1.039533, 0.861394, 
        -1.364049, 0.999092, 0.805030, 
        -1.205913, 0.579217, 0.764064, 
        -1.269808, 0.559087, 0.732324, 
        1.191980, 2.309095, 1.342312, 
        1.246665, 0.950375, 1.196204, 
        1.570055, -0.498348, 0.447321, 
        2.062112, 2.287447, 0.363412, 
        1.887120, 0.858852, 0.449739, 
        -1.191779, 1.231986, 0.676237, 
        -1.564931, 1.307247, 0.268281, 
        -1.241351, 0.991019, 0.860323, 
        -1.409324, 0.789887, 0.979801, 
        -1.323251, 1.308399, 0.795204, 
        -1.486333, 1.328284, 0.768946, 
        -1.356063, 1.186294, 0.969973, 
        -1.412442, 1.145853, 0.913608, 
        -1.120443, 0.855097, 0.236178, 
        -1.471156, 0.847709, 0.213132, 
        -1.138281, 0.531517, 0.867107, 
        -1.330044, 0.524129, 0.780191, 
        -1.186233, 0.643926, 0.243081, 
        -1.226606, 0.642250, 0.239352, 
        -1.192343, 0.434469, 0.630033, 
        -1.221050, 0.423789, 0.625281, 
        -1.164415, 0.676420, 0.226067, 
        -1.265718, 0.684817, 0.215475, 
        -1.177794, 0.445267, 0.691456, 
        -1.241689, 0.425138, 0.659716, 
        -1.188079, 0.580642, 0.359992, 
        -1.224984, 0.578474, 0.352016, 
        -1.190868, 0.485044, 0.536601, 
        -1.222496, 0.480663, 0.524807, 
        -1.190868, 0.485044, 0.536601, 
        -1.188079, 0.580642, 0.359992, 
        -1.224984, 0.578474, 0.352016, 
        -1.222496, 0.480663, 0.524807, 
        -0.942766, -0.487294, -0.001420, 
        -0.939978, -0.391696, -0.178029, 
        -0.976882, -0.393863, -0.186004, 
        -0.974395, -0.491675, -0.013214, 
        -0.882556, -0.737209, -0.256352, 
        -0.940061, -0.394549, -0.172759, 
        -1.164722, 2.432390, 0.622608, 
        -1.170668, 2.476786, -0.386678, 
        -1.527930, 1.849977, 0.615340, 
        -1.890756, 2.004652, -0.422182, 
        -1.643498, 2.351236, 0.502194, 
        -1.445662, 2.477505, -0.268814, 
        -1.851632, 2.072104, 0.304917, 
        -1.758720, 2.348178, -0.160491, 
        -0.000000, 1.365615, 1.287052, 
        1.108593, 1.371564, 0.937320, 
        -1.004912, 1.431821, 1.171337, 
        0.000000, -0.270229, 1.098689, 
        0.000000, -0.421540, 1.000000, 
        0.000000, -0.270229, 1.098689, 
        0.000000, -0.421540, 1.000000, 
        -0.752650, -0.367011, 0.752650, 
        -0.752650, -0.270229, 0.851339, 
        -0.000000, 0.762946, 1.000000, 
        -0.000000, 0.762946, 1.000000, 
        -0.874639, 0.762946, 0.874638, 
        -0.874639, 0.762946, 0.874638, 
        -0.874639, 0.762946, 0.874638, 
        -0.000000, 0.762946, 1.000000, 
        -0.874639, 0.762946, 0.874638, 
        -0.000000, 0.762946, 1.000000, 
        -0.874639, 0.762946, 0.874638, 
        0.854925, 0.571537, 0.854926, 
        -0.755426, 0.553824, 0.948393, 
        -0.000000, 0.581445, 1.000000, 
        -0.000000, 0.581445, 1.000000, 
        0.752650, -0.139259, 0.622827, 
        -0.168731, 0.514620, 1.107697, 
        -0.168731, 0.856029, 1.107697, 
        -0.168731, 0.514620, 0.956576, 
        -0.168731, 0.856029, 0.956576, 
        0.172679, 0.514620, 1.107697, 
        0.172679, 0.856029, 1.107697, 
        0.172679, 0.514620, 0.956576, 
        0.172679, 0.856029, 0.956576, 
        -0.830959, 0.554539, 0.898142, 
        -0.820364, 0.669769, 0.950678, 
        -0.012150, 0.758283, 1.078016, 
        -0.012150, 0.576783, 1.078016, 
        0.864983, 0.567597, 0.919396, 
        0.884696, 0.759006, 0.939109, 
        0.010058, 0.759006, 1.064470, 
        0.010058, 0.577506, 1.064470, 
        0.901679, 0.741073, 0.686949, 
        1.689579, 1.114924, 0.944671, 
        0.099384, 2.634052, 0.462260, 
        0.099549, 2.751822, 0.461940, 
        -0.234600, 2.923455, 0.440099, 
        -0.248046, 2.602142, 0.455630, 
        -0.000000, 2.612765, 0.469715, 
        -0.000000, 2.926187, 0.461902, 
        0.234599, 2.923455, 0.440099, 
        0.248046, 2.602142, 0.455630, 
        0.103736, 2.635918, 0.510889, 
        0.103901, 2.753688, 0.510570, 
        0.220750, 2.751816, 0.495970, 
        0.225223, 2.630013, 0.504458, 
        -0.111607, 2.641830, 0.497004, 
        -0.111764, 2.759601, 0.496685, 
        -0.222551, 2.757728, 0.482084, 
        -0.226793, 2.635925, 0.490573, 
        0.000000, 0.018820, -0.746635, 
        1.689579, 1.114924, 0.944671, 
        1.399540, -0.509012, 0.660508, 
        1.229231, -0.519676, 0.831904, 
        1.246665, 0.950375, 1.196204, 
        -0.001787, -0.387513, -0.861571, 
        -0.741362, -0.385627, -0.745488, 
        0.811868, -0.402226, -0.523001, 
        0.752650, -0.439149, 0.915148, 
        0.000000, -0.439149, 1.162498, 
        -0.752650, -0.439149, 0.915148, 
        -0.670300, 2.391013, 0.006608, 
        -0.858950, 2.479151, 0.034144, 
        0.704691, 2.364655, -0.005260, 
        0.837589, 2.307182, 0.022700, 
        1.478454, 2.282525, -0.215555, 
        -1.398313, 2.175210, -0.397902, 
        -1.422566, 2.404350, -0.596205
    };

    static const double        punk_n[PUNK_MAX_VERTICES] =
    {
        314, 3, 0,
        0.9839, 0.1789, 0.0000, 
        0.7725, 0.6208, -0.1335, 
        0.6348, 0.4303, 0.6417, 
        -0.1161, 0.1449, 0.9826, 
        -0.3004, -0.0190, -0.9536, 
        0.2127, -0.0195, -0.9769, 
        0.1908, 0.1432, 0.9711, 
        0.0000, -0.5874, 0.8093, 
        -0.1106, -0.6294, -0.7692, 
        -0.9898, -0.1158, 0.0832, 
        0.0000, 0.0000, 1.0000, 
        0.9865, 0.1630, 0.0177, 
        0.1919, -0.4561, -0.8690, 
        0.9392, -0.1876, 0.2876, 
        0.6724, 0.6253, 0.3961, 
        -0.4446, 0.7691, 0.4591, 
        0.7551, -0.0447, -0.6541, 
        -0.1968, 0.9800, -0.0311, 
        -0.4376, 0.8705, -0.2254, 
        -0.4375, -0.0421, -0.8982, 
        -0.7099, 0.2731, 0.6492, 
        0.6997, -0.1761, -0.6924, 
        0.9873, -0.1584, -0.0085, 
        0.1850, 0.9408, 0.2840, 
        -0.3181, 0.8931, 0.3181, 
        -0.1335, 0.6208, -0.7725, 
        -0.7725, 0.6208, 0.1335, 
        0.1335, 0.6208, 0.7725, 
        0.0000, -1.0000, -0.0000, 
        0.9982, 0.0606, 0.0000, 
        -0.9982, -0.0606, -0.0000, 
        0.0000, 0.3675, -0.9300, 
        0.0000, -0.3245, 0.9459, 
        -0.9839, -0.1789, -0.0000, 
        0.0000, -0.6714, -0.7411, 
        -0.6992, -0.1823, 0.6913, 
        0.9991, -0.0417, 0.0013, 
        0.2341, 0.0710, 0.9696, 
        -0.7412, 0.6677, -0.0694, 
        -0.9964, 0.0382, -0.0752, 
        -0.9696, 0.0710, 0.2341, 
        0.6958, -0.1717, -0.6974, 
        0.7159, -0.4935, -0.4940, 
        -0.2341, 0.0710, -0.9696, 
        0.5345, 0.8191, -0.2084, 
        0.6689, 0.3242, -0.6689, 
        -0.5170, 0.8519, -0.0837, 
        0.7412, 0.6677, 0.0694, 
        0.9964, 0.0382, 0.0752, 
        0.9696, 0.0710, -0.2341, 
        0.9964, 0.0382, -0.0752, 
        0.9301, 0.3594, -0.0753, 
        0.9109, 0.1456, -0.3860, 
        0.9696, 0.0710, 0.2341, 
        0.8497, -0.0311, 0.5263, 
        0.9301, 0.3594, 0.0753, 
        0.7725, 0.6208, 0.1335, 
        0.9617, 0.1258, 0.2434, 
        0.9850, 0.1502, 0.0847, 
        -0.6689, 0.3242, -0.6689, 
        -0.5859, 0.7269, 0.3583, 
        -0.3181, 0.8931, -0.3181, 
        0.5170, 0.8519, -0.0837, 
        0.3181, 0.8931, -0.3181, 
        0.5859, 0.7269, 0.3583, 
        0.3181, 0.8931, 0.3181, 
        0.5170, 0.8519, 0.0837, 
        0.6689, 0.3242, 0.6689, 
        -0.7159, -0.4935, -0.4940, 
        -0.1072, 0.4698, -0.8762, 
        -0.1821, 0.4290, -0.8848, 
        0.2341, 0.0710, -0.9696, 
        0.2043, 0.4408, -0.8740, 
        0.0895, 0.5060, -0.8579, 
        0.1335, 0.6208, -0.7725, 
        0.2434, 0.1258, -0.9617, 
        0.5321, 0.7777, -0.3348, 
        -0.9964, 0.0382, 0.0752, 
        -0.9651, 0.2555, 0.0577, 
        -0.8778, -0.0645, 0.4746, 
        -0.9696, 0.0710, -0.2341, 
        -0.9058, 0.1587, -0.3930, 
        -0.9548, 0.2957, -0.0309, 
        -0.7725, 0.6208, -0.1335, 
        -0.9617, 0.1258, -0.2434, 
        -0.9850, 0.1502, -0.0847, 
        0.1793, 0.9833, -0.0312, 
        -0.0087, -0.9995, 0.0317, 
        0.3697, -0.1276, 0.9203, 
        -0.2341, 0.0710, 0.9696, 
        -0.3907, -0.1154, 0.9132, 
        -0.9964, 0.0847, -0.0027, 
        -0.1335, 0.6208, 0.7725, 
        -0.2434, 0.1258, 0.9617, 
        -0.0847, 0.1502, 0.9850, 
        0.6992, -0.1823, 0.6913, 
        0.0847, 0.1502, 0.9850, 
        0.2434, 0.1258, 0.9617, 
        -0.7412, 0.6677, 0.0694, 
        -0.9850, 0.1502, 0.0847, 
        -0.9617, 0.1258, 0.2434, 
        -0.6958, -0.1717, -0.6974, 
        -0.5321, 0.7777, -0.3348, 
        -0.2434, 0.1258, -0.9617, 
        -0.5345, 0.8191, -0.2084, 
        -0.6689, 0.3242, 0.6689, 
        -0.5170, 0.8519, 0.0837, 
        0.0552, 0.9153, 0.3990, 
        0.2097, 0.9346, 0.2872, 
        0.1862, 0.9821, -0.0294, 
        0.7412, 0.6677, -0.0694, 
        0.9850, 0.1502, -0.0847, 
        0.9617, 0.1258, -0.2434, 
        0.9610, -0.0225, -0.2756, 
        -0.9777, -0.0000, 0.2102, 
        0.0972, -0.9932, -0.0636, 
        0.0488, -0.9979, 0.0429, 
        0.0111, 0.9992, -0.0393, 
        0.0378, 0.0244, 0.9990, 
        -0.0360, 0.0258, 0.9990, 
        -0.9991, -0.0417, 0.0013, 
        0.0087, -0.9995, 0.0317, 
        0.0000, 0.7599, -0.6500, 
        1.0000, 0.0049, -0.0002, 
        -0.6298, 0.0574, -0.7746, 
        -0.7631, 0.0106, -0.6462, 
        -0.8345, 0.0391, -0.5496, 
        -0.7187, 0.2208, -0.6593, 
        -0.3679, -0.9272, -0.0706, 
        0.7257, 0.0000, 0.6880, 
        0.2225, 0.1815, -0.9579, 
        -0.0404, -0.4603, -0.8869, 
        0.4414, 0.1240, 0.8887, 
        -0.8086, 0.0270, -0.5877, 
        -0.6217, 0.0282, -0.7827, 
        -0.9547, 0.2953, -0.0377, 
        0.8455, -0.4214, -0.3278, 
        0.9904, -0.1200, -0.0688, 
        0.6734, -0.0152, -0.7392, 
        0.8542, -0.5178, -0.0468, 
        0.3896, -0.1058, 0.9149, 
        -0.9860, -0.1191, 0.1168, 
        0.2159, -0.1298, -0.9678, 
        -0.2868, -0.1370, -0.9481, 
        -0.1945, 0.0006, 0.9809, 
        -0.7541, -0.1326, 0.6432, 
        0.5955, -0.5197, -0.6125, 
        0.0328, -0.9988, -0.0362, 
        -0.0460, 0.9965, -0.0697, 
        -0.6411, -0.4254, 0.6388, 
        0.0039, 0.3739, -0.9274, 
        -0.1118, 0.3716, -0.9216, 
        0.1502, 0.8983, -0.4129, 
        -0.2255, 0.8216, -0.5236, 
        -0.0476, 0.9986, -0.0231, 
        0.8086, 0.0343, 0.5874, 
        0.9907, -0.0396, -0.1301, 
        0.2356, -0.5635, 0.7918, 
        -0.0894, 0.1472, -0.9851, 
        -0.0470, -0.1983, -0.9790, 
        -0.9381, -0.3434, 0.0461, 
        0.0419, -0.8409, -0.5395, 
        0.9016, 0.4020, 0.1595, 
        -0.7431, -0.0886, 0.6633, 
        -0.9989, -0.0473, -0.0072, 
        -0.8347, 0.4997, 0.2316, 
        0.4763, 0.1197, 0.8711, 
        -0.9763, -0.2068, 0.0631, 
        0.9793, 0.1194, 0.1637, 
        -0.2530, -0.5016, 0.8273, 
        0.3748, -0.2614, 0.8895, 
        0.9178, -0.2702, 0.2910, 
        0.9599, -0.0893, 0.2656, 
        -0.3009, -0.6285, 0.7173, 
        -0.9456, -0.3212, 0.0520, 
        -0.2072, 0.8704, 0.4466, 
        -0.3253, 0.5101, 0.7962, 
        -0.7952, 0.3473, 0.4970, 
        -0.0494, 0.7078, 0.7047, 
        -0.3167, 0.6659, 0.6755, 
        0.1978, 0.6243, -0.7557, 
        0.9570, 0.1204, 0.2638, 
        -0.2758, -0.6288, 0.7270, 
        0.0347, -0.8695, -0.4926, 
        0.3067, -0.8284, -0.4688, 
        0.0796, -0.8578, -0.5077, 
        0.1106, -0.8881, -0.4462, 
        0.1161, -0.8691, -0.4809, 
        -0.9826, -0.1785, -0.0512, 
        0.1308, 0.4935, -0.8598, 
        0.9832, 0.1505, 0.1030, 
        0.0671, -0.4653, -0.8826, 
        0.2634, -0.9548, 0.1377, 
        -0.5895, -0.7089, -0.3873, 
        0.8480, -0.4785, -0.2280, 
        -0.9759, -0.1955, -0.0966, 
        0.3314, -0.8253, -0.4573, 
        -0.9632, -0.2397, -0.1218, 
        0.9759, 0.1851, 0.1156, 
        -0.2357, -0.5159, 0.8236, 
        0.1533, 0.5081, -0.8475, 
        -0.1510, -0.7235, 0.6736, 
        0.9854, 0.1427, 0.0928, 
        0.3311, 0.2606, -0.9069, 
        0.6419, -0.4618, -0.6121, 
        -0.5752, 0.0935, -0.8126, 
        -0.9668, -0.2555, 0.0095, 
        -0.4007, -0.4523, 0.7968, 
        -0.3637, 0.9297, 0.0589, 
        -0.9379, 0.3465, 0.0183, 
        -0.6907, 0.0040, 0.7231, 
        -0.0638, 0.9859, -0.1548, 
        0.2971, 0.9279, -0.2253, 
        0.0673, 0.5199, 0.8516, 
        -0.2654, 0.1537, 0.9518, 
        -0.5686, -0.8190, 0.0767, 
        -0.5392, 0.3266, 0.7763, 
        0.0560, -0.2801, -0.9583, 
        -0.3260, -0.0380, -0.9446, 
        0.4106, -0.1707, -0.8957, 
        -0.0647, 0.8901, 0.4511, 
        -0.7026, 0.2297, 0.6735, 
        -0.1024, 0.1609, 0.9816, 
        -0.9494, -0.1405, -0.2809, 
        0.3008, -0.0444, 0.9527, 
        0.2952, -0.2095, 0.9322, 
        0.9729, 0.0238, 0.2299, 
        -0.0063, 0.9735, 0.2287, 
        -0.9247, -0.3741, -0.0704, 
        -0.4216, -0.4954, 0.7595, 
        0.8487, -0.5218, -0.0867, 
        0.2372, 0.0402, 0.9706, 
        -0.9732, 0.2278, -0.0308, 
        -0.1613, -0.4918, 0.8556, 
        -0.9904, -0.1379, 0.0002, 
        -0.1283, -0.4265, 0.8954, 
        0.1283, -0.4265, 0.8954, 
        -0.9551, -0.2437, -0.1687, 
        -0.1311, -0.4232, 0.8965, 
        -0.9700, -0.2430, 0.0008, 
        0.0086, 0.9982, 0.0597, 
        0.0359, -0.9989, -0.0287, 
        0.9902, -0.1394, -0.0093, 
        0.9742, 0.0000, 0.2258, 
        0.9784, -0.2069, -0.0000, 
        0.9810, -0.1170, 0.1550, 
        0.9725, -0.2296, 0.0390, 
        0.9140, 0.4056, -0.0010, 
        -1.0000, 0.0000, 0.0000, 
        -0.1721, -0.1658, 0.9710, 
        1.0000, 0.0000, 0.0000, 
        0.0000, 1.0000, 0.0000, 
        0.9881, 0.0000, 0.1539, 
        -0.1263, 0.8073, 0.5765, 
        0.1539, -0.0603, 0.9863, 
        0.9837, -0.0850, -0.1587, 
        -0.0214, -0.9981, -0.0577, 
        -0.9880, -0.0000, 0.1541, 
        0.4450, -0.3962, -0.8031, 
        0.8759, 0.1312, -0.4644, 
        -0.5518, -0.0994, 0.8280, 
        -0.8234, -0.1098, 0.5568, 
        -0.5092, -0.8602, 0.0269, 
        -0.9912, 0.1098, -0.0746, 
        -0.8967, 0.4108, 0.1650, 
        0.8328, -0.2185, 0.5086, 
        0.6683, 0.0310, 0.7433, 
        0.5125, -0.0714, 0.8557, 
        0.9090, -0.0867, 0.4077, 
        -0.0463, 0.0188, 0.9987, 
        -0.1054, 0.0509, 0.9931, 
        -0.0032, 0.0543, 0.9985, 
        -0.0581, 0.0393, 0.9975, 
        0.0517, 0.0188, 0.9985, 
        0.1035, 0.0450, 0.9936, 
        -0.0108, 0.0537, 0.9985, 
        0.0582, 0.0640, 0.9963, 
        0.0891, 0.0382, 0.9953, 
        0.9955, 0.0303, -0.0902, 
        -0.9960, 0.0016, 0.0891, 
        -0.0463, -0.9980, 0.0424, 
        -0.0939, 0.0382, 0.9948, 
        -0.0117, 0.9992, -0.0394, 
        -0.9951, 0.0280, -0.0950, 
        0.9956, 0.0016, 0.0939, 
        -0.2302, 0.4196, -0.8780, 
        0.4044, 0.3258, -0.8546, 
        0.5957, -0.2210, 0.7722, 
        0.0819, -0.8778, 0.4720, 
        -0.2939, -0.3378, -0.8942, 
        0.2939, -0.3378, -0.8942, 
        -0.5243, 0.8285, -0.1969, 
        0.2778, 0.9354, 0.2187, 
        -0.0618, 0.9741, -0.2173, 
        0.4694, 0.8269, 0.3096, 
        0.1999, 0.9677, -0.1535, 
        0.6518, 0.6367, -0.4120, 
        0.1970, 0.9305, 0.3087, 
        0.0522, 0.9959, 0.0734, 
        -0.4304, -0.5982, -0.6760, 
        -0.9062, 0.3665, 0.2107, 
        0.9199, -0.3321, -0.2087, 
        -0.3455, 0.9362, 0.0647, 
        0.4834, 0.2685, -0.8332, 
        0.4643, 0.6799, 0.5676, 
        0.2508, -0.6182, -0.7450, 
        -0.6718, 0.5947, -0.4416, 
        -0.0932, 0.9703, -0.2234, 
        -0.2176, 0.9498, 0.2250, 
        -0.8393, 0.5244, 0.1435, 
        -0.6293, -0.7700, 0.1053, 
        0.4668, -0.1334, -0.8743, 
        -0.5363, -0.1486, -0.8309, 
        -0.5231, -0.1570, -0.8377
    };

    static const int        punk_f[PUNK_MAX_VERTICES] =
    {
        4, 9, 10, 42, 40, 
        4, 123, 69, 32, 79, 
        3, 127, 126, 143, 
        3, 26, 234, 12, 
        3, 151, 19, 150, 
        3, 151, 147, 19, 
        3, 12, 234, 31, 
        4, 2, 15, 39, 37, 
        4, 9, 4, 25, 19, 
        3, 251, 16, 241, 
        3, 239, 238, 20, 
        5, 2, 1, 28, 256, 29, 
        4, 1, 13, 19, 28, 
        3, 240, 15, 239, 
        3, 238, 240, 20, 
        3, 63, 304, 46, 
        3, 47, 302, 76, 
        4, 155, 139, 164, 166, 
        3, 74, 128, 129, 
        3, 233, 231, 308, 
        3, 25, 14, 150, 
        3, 149, 247, 245, 
        3, 226, 7, 26, 
        4, 153, 17, 28, 147, 
        5, 154, 6, 31, 235, 148, 
        3, 6, 305, 31, 
        4, 122, 80, 35, 66, 
        4, 121, 71, 33, 65, 
        4, 120, 72, 35, 80, 
        4, 119, 82, 34, 78, 
        4, 36, 37, 39, 38, 
        4, 1, 2, 37, 36, 
        4, 15, 13, 38, 39, 
        4, 13, 1, 36, 38, 
        4, 40, 42, 43, 41, 
        4, 10, 3, 43, 42, 
        4, 3, 4, 41, 43, 
        4, 4, 9, 40, 41, 
        4, 118, 85, 49, 66, 
        4, 86, 117, 278, 277, 
        4, 116, 70, 53, 87, 
        4, 115, 88, 51, 68, 
        4, 114, 89, 57, 90, 
        4, 113, 84, 55, 91, 
        4, 112, 92, 48, 77, 
        4, 111, 93, 58, 94, 
        4, 110, 83, 54, 95, 
        4, 109, 96, 49, 78, 
        4, 108, 97, 59, 98, 
        4, 107, 68, 51, 99, 
        4, 106, 100, 50, 67, 
        4, 105, 101, 60, 102, 
        4, 104, 81, 52, 103, 
        4, 101, 104, 103, 60, 
        4, 46, 75, 104, 101, 
        4, 75, 21, 81, 104, 
        4, 70, 105, 102, 53, 
        4, 22, 63, 105, 70, 
        4, 63, 46, 101, 105, 
        4, 82, 106, 67, 34, 
        4, 53, 102, 106, 82, 
        4, 102, 60, 100, 106, 
        4, 97, 107, 99, 59, 
        4, 48, 65, 107, 97, 
        4, 65, 33, 68, 107, 
        4, 79, 108, 98, 50, 
        4, 32, 77, 108, 79, 
        4, 77, 48, 97, 108, 
        4, 67, 109, 78, 34, 
        4, 50, 98, 109, 67, 
        4, 98, 59, 96, 109, 
        4, 93, 110, 95, 58, 
        4, 93, 137, 61, 110, 
        4, 61, 24, 83, 110, 
        4, 81, 111, 94, 52, 
        4, 21, 73, 111, 81, 
        4, 93, 111, 73, 137, 
        4, 69, 112, 77, 32, 
        4, 52, 94, 112, 69, 
        4, 94, 58, 92, 112, 
        4, 89, 113, 91, 57, 
        4, 47, 76, 113, 89, 
        4, 76, 23, 84, 113, 
        4, 83, 114, 90, 54, 
        4, 24, 64, 114, 83, 
        4, 64, 47, 89, 114, 
        4, 71, 115, 68, 33, 
        4, 54, 90, 115, 71, 
        4, 90, 57, 88, 115, 
        3, 133, 62, 129, 
        4, 87, 56, 280, 281, 
        4, 74, 22, 70, 116, 
        4, 84, 117, 86, 55, 
        4, 23, 62, 117, 84, 
        4, 74, 116, 282, 128, 
        4, 72, 118, 66, 35, 
        4, 55, 86, 118, 72, 
        4, 86, 56, 85, 118, 
        4, 85, 119, 78, 49, 
        4, 56, 87, 119, 85, 
        4, 87, 53, 82, 119, 
        4, 88, 120, 80, 51, 
        4, 57, 91, 120, 88, 
        4, 91, 55, 72, 120, 
        4, 92, 121, 65, 48, 
        4, 58, 95, 121, 92, 
        4, 95, 54, 71, 121, 
        4, 96, 122, 66, 49, 
        4, 59, 99, 122, 96, 
        4, 99, 51, 80, 122, 
        6, 22, 74, 62, 23, 26, 31, 
        5, 23, 76, 302, 303, 26, 
        5, 21, 75, 304, 305, 30, 
        4, 100, 123, 79, 50, 
        4, 60, 103, 123, 100, 
        4, 103, 52, 69, 123, 
        4, 161, 144, 126, 156, 
        4, 160, 146, 125, 157, 
        4, 146, 145, 124, 125, 
        4, 136, 130, 287, 290, 
        4, 132, 276, 284, 285, 
        4, 129, 128, 282, 279, 
        4, 133, 129, 279, 278, 
        4, 116, 87, 281, 282, 
        4, 56, 86, 277, 280, 
        3, 129, 62, 74, 
        4, 117, 62, 133, 278, 
        4, 156, 126, 139, 155, 
        4, 125, 124, 44, 138, 
        4, 158, 140, 142, 159, 
        4, 126, 127, 142, 141, 
        5, 140, 169, 139, 141, 142, 
        4, 18, 17, 145, 146, 
        4, 154, 18, 146, 160, 
        4, 153, 5, 144, 161, 
        4, 17, 153, 161, 145, 
        4, 6, 154, 160, 143, 
        4, 138, 158, 159, 125, 
        4, 124, 156, 155, 44, 
        4, 143, 160, 157, 127, 
        4, 145, 161, 156, 124, 
        3, 29, 256, 252, 
        3, 5, 153, 30, 
        4, 14, 16, 172, 173, 
        4, 167, 188, 187, 165, 
        3, 251, 241, 242, 
        4, 30, 147, 151, 11, 
        4, 11, 151, 150, 27, 
        4, 253, 242, 239, 255, 
        4, 140, 158, 167, 165, 
        4, 44, 155, 166, 162, 
        7, 138, 44, 162, 189, 170, 177, 163, 
        5, 169, 140, 165, 187, 171, 
        4, 158, 138, 163, 167, 
        3, 11, 168, 30, 
        3, 27, 168, 11, 
        5, 21, 30, 168, 137, 73, 
        5, 24, 61, 137, 168, 27, 
        5, 139, 169, 171, 190, 164, 
        3, 171, 274, 190, 
        3, 200, 173, 178, 
        4, 16, 7, 174, 172, 
        5, 8, 175, 229, 307, 227, 
        4, 8, 14, 173, 175, 
        4, 182, 184, 199, 197, 
        4, 176, 173, 200, 201, 
        4, 192, 200, 178, 174, 
        3, 193, 192, 174, 
        4, 175, 176, 201, 193, 
        3, 175, 193, 174, 
        3, 195, 202, 194, 
        3, 193, 201, 195, 
        4, 200, 192, 194, 202, 
        4, 185, 186, 211, 210, 
        4, 177, 188, 167, 163, 
        4, 162, 166, 191, 189, 
        4, 166, 164, 190, 191, 
        3, 202, 195, 203, 
        3, 203, 195, 201, 
        4, 182, 179, 192, 193, 
        4, 183, 184, 195, 194, 
        4, 184, 182, 193, 195, 
        4, 179, 183, 194, 192, 
        4, 196, 197, 199, 198, 
        4, 179, 182, 197, 196, 
        4, 183, 179, 196, 198, 
        4, 184, 183, 198, 199, 
        4, 181, 180, 201, 200, 
        4, 186, 185, 202, 203, 
        4, 180, 186, 203, 201, 
        4, 185, 181, 200, 202, 
        4, 205, 204, 212, 213, 
        4, 186, 180, 209, 211, 
        4, 180, 181, 208, 209, 
        4, 181, 185, 210, 208, 
        4, 204, 205, 209, 208, 
        4, 207, 206, 210, 211, 
        6, 205, 213, 215, 207, 211, 209, 
        6, 206, 214, 212, 204, 208, 210, 
        4, 215, 213, 218, 219, 
        4, 219, 218, 222, 223, 
        4, 215, 214, 206, 207, 
        4, 213, 212, 217, 218, 
        4, 212, 214, 216, 217, 
        4, 214, 215, 219, 216, 
        3, 222, 224, 223, 
        5, 217, 216, 220, 225, 221, 
        4, 216, 219, 223, 220, 
        4, 218, 217, 221, 222, 
        3, 223, 224, 220, 
        3, 220, 224, 225, 
        4, 225, 224, 222, 221, 
        3, 227, 307, 308, 
        3, 8, 227, 27, 
        3, 175, 174, 228, 
        3, 174, 7, 228, 
        3, 231, 233, 230, 
        3, 233, 229, 232, 
        3, 232, 228, 230, 
        3, 227, 231, 45, 
        3, 27, 227, 303, 
        3, 12, 31, 26, 
        3, 228, 226, 230, 
        3, 228, 229, 175, 
        3, 228, 7, 226, 
        3, 175, 173, 176, 
        3, 25, 150, 19, 
        3, 19, 147, 28, 
        4, 149, 152, 244, 246, 
        3, 152, 243, 244, 
        3, 26, 7, 236, 
        3, 234, 26, 236, 
        3, 246, 247, 149, 
        3, 31, 6, 235, 
        3, 31, 234, 235, 
        3, 234, 148, 235, 
        3, 143, 144, 306, 
        3, 5, 6, 306, 
        5, 13, 15, 240, 238, 19, 
        3, 10, 240, 239, 
        4, 10, 9, 291, 240, 
        4, 29, 252, 254, 237, 
        5, 4, 3, 242, 241, 25, 
        4, 3, 10, 239, 242, 
        3, 14, 241, 16, 
        3, 246, 244, 234, 
        4, 243, 148, 234, 244, 
        3, 25, 241, 14, 
        4, 234, 236, 247, 246, 
        4, 7, 16, 251, 236, 
        4, 244, 246, 249, 248, 
        4, 248, 249, 251, 250, 
        4, 148, 243, 271, 270, 
        4, 253, 255, 268, 265, 
        4, 255, 254, 243, 152, 
        3, 256, 28, 252, 
        3, 154, 148, 18, 
        3, 17, 18, 28, 
        3, 148, 273, 18, 
        4, 28, 18, 273, 252, 
        3, 144, 143, 126, 
        4, 257, 258, 260, 259, 
        4, 265, 268, 267, 266, 
        4, 263, 264, 262, 261, 
        4, 261, 262, 258, 257, 
        4, 259, 263, 261, 257, 
        4, 264, 260, 258, 262, 
        4, 255, 152, 267, 268, 
        4, 152, 149, 266, 267, 
        4, 272, 269, 270, 271, 
        4, 252, 148, 270, 269, 
        4, 254, 252, 269, 272, 
        4, 243, 254, 272, 271, 
        3, 266, 251, 149, 
        3, 251, 266, 265, 
        3, 265, 242, 253, 
        3, 251, 242, 265, 
        3, 148, 273, 270, 
        3, 273, 148, 252, 
        3, 273, 269, 270, 
        3, 269, 273, 252, 
        4, 191, 274, 170, 189, 
        4, 177, 170, 293, 294, 
        3, 187, 274, 171, 
        3, 188, 274, 187, 
        3, 191, 190, 274, 
        4, 131, 130, 279, 280, 
        4, 134, 131, 280, 277, 
        4, 136, 134, 277, 278, 
        4, 130, 136, 278, 279, 
        4, 275, 276, 280, 279, 
        4, 276, 132, 281, 280, 
        4, 132, 135, 282, 281, 
        4, 135, 275, 279, 282, 
        4, 283, 286, 285, 284, 
        4, 135, 132, 285, 286, 
        4, 276, 275, 283, 284, 
        4, 275, 135, 286, 283, 
        4, 290, 287, 288, 289, 
        4, 131, 134, 289, 288, 
        4, 134, 136, 290, 289, 
        4, 130, 131, 288, 287, 
        4, 274, 188, 295, 292, 
        4, 188, 177, 294, 295, 
        4, 170, 274, 292, 293, 
        4, 297, 25, 291, 296, 
        4, 298, 296, 291, 28, 
        4, 293, 292, 295, 294, 
        4, 15, 2, 29, 239, 
        4, 239, 29, 299, 300, 
        4, 242, 239, 300, 301, 
        3, 64, 302, 47, 
        3, 45, 226, 303, 
        5, 303, 302, 64, 24, 27, 
        3, 226, 26, 303, 
        3, 45, 303, 227, 
        3, 46, 304, 75, 
        5, 305, 304, 63, 22, 31, 
        4, 305, 6, 5, 30, 
        3, 143, 127, 6, 
        3, 154, 235, 6, 
        3, 154, 235, 148, 
        3, 231, 230, 45, 
        3, 306, 144, 5, 
        3, 306, 6, 143, 
        3, 308, 307, 229, 
        3, 229, 233, 308, 
        3, 231, 227, 308, 
        3, 45, 230, 226, 
        3, 232, 230, 233, 
        3, 229, 228, 232, 
        3, 147, 30, 153, 
        3, 150, 14, 27, 
        3, 8, 27, 14
    };

#endif // PUNK_MODEL
