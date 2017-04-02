/*
 * Copyright (C) 2017 Lukas Berger <mail@lukasberger.at>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ATLAS:  big cpu cluster, default max clock: 2.1GHz, max clock: 2.496GHz according to kernel sources
 * APOLLO: little cpu cluster, default max clock: 1.5GHz, max clock: 2.0GHz according to kernel sources
 *
 * If you want to unlock all availabel cpu frequencies for ATLAS and APOLLO you have to
 * apply the patchfile "exynos7420-freq-unlock.patch" to the kernel to unlock all available
 * CPU clock frequencies. Be warned, you do this on your own risk. If you patched kernel,
 * update the CPUCLK_* defines in power.h to enable support for the new frequencies in Exynos5PowerHAL
 */
#ifndef EXYNOS5_POWER_HAL_PROFILES_INCLUDED
#define EXYNOS5_POWER_HAL_PROFILES_INCLUDED

struct power_profile_cpuclusters {
	char *core1;
	char *core2;
	char *core3;
	char *core4;
};

struct power_profile_cpucores {
	char *core1;
	char *core2;
	char *core3;
	char *core4;
};

struct power_profile_cpugov {
	char *above_hispeed_delay;
	char *boost;
	char *boostpulse;
	char *boostpulse_duration;
	char *go_hispeed_load;
	char *hispeed_freq;
	char *target_loads;
};

struct power_profile {

	struct {
		char *dvfs;
		char *dvfs_governor;
		char *dvfs_min_lock;
		char *dvfs_max_lock;
	} mali;

	struct power_profile_cpuclusters cpumaxfreq;
	struct power_profile_cpuclusters cpuminfreq;

	struct {
		struct power_profile_cpucores apollo; // ca53, little cluster
		struct power_profile_cpucores atlas; // ca57, big cluster
	} cpuonline;

	struct {
		struct power_profile_cpugov apollo; // ca53, little cluster
		struct power_profile_cpugov atlas; // ca57, big cluster
	} cpugov;


} power_profiles[3] = {
	/************************************
	 * PROFILE_POWER_SAVE
	 */
	{
		/* .mali = */ {
			/* .dvfs          = */ "0",
			/* .dvfs_governor = */ "1",
			/* .dvfs_min_lock = */ "266",
			/* .dvfs_max_lock = */ "266"
		},
		/* .cpuminfreq = */ {
			/* .apollo = */ "200000",
			/* .atlas = */ "200000"
		},
		/* .cpumaxfreq = */ {
			/* .apollo = */ "400000",
			/* .atlas = */ "800000"
		},
		/* .cpuonline = */ {
			/* .apollo = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "0",
				/* .core4 = */ "0"
			},
			/* .atlas = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "0",
				/* .core4 = */ "0"
			}
		},
		/* .cpugov = */ {
			/* .apollo = */ {
				/* .above_hispeed_delay = */ "19000 300000:49000 400000:19000",
				/* .boost               = */ "0",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "20000",
				/* .go_hispeed_load     = */ "85",
				/* .hispeed_freq        = */ "400000", // allow 200MHz+ to minimum of 400MHz
				/* .target_loads        = */ "75 300000:85 400000:90"
			},
			/* .atlas = */ {
				/* .above_hispeed_delay = */ "79000 500000:49000 800000:19000",
				/* .boost               = */ "0",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "20000",
				/* .go_hispeed_load     = */ "99",
				/* .hispeed_freq        = */ "800000", // allow 200MHz+ to minimum of 800Mhz
				/* .target_loads        = */ "87 500000:85 800000:90"
			}
		}
	},

	/************************************
	 * PROFILE_NORMAL
	 */
	{
		/* .mali = */ {
			/* .dvfs          = */ "1",
			/* .dvfs_governor = */ "1",
			/* .dvfs_min_lock = */ "266",
			/* .dvfs_max_lock = */ "772"
		},
		/* .cpuminfreq = */ {
			/* .apollo = */ "200000",
			/* .atlas = */ "200000"
		},
		/* .cpumaxfreq = */ {
			/* .apollo = */ "1200000",
			/* .atlas = */ "1600000"
		},
		/* .cpuonline = */ {
			/* .apollo = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "1",
				/* .core4 = */ "1"
			},
			/* .atlas = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "1",
				/* .core4 = */ "1"
			}
		},
		/* .cpugov = */ {
			/* .apollo = */ {
				/* .above_hispeed_delay = */ "19000 1200000:39000",
				/* .boost               = */ "0",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "40000",
				/* .go_hispeed_load     = */ "85",
				/* .hispeed_freq        = */ "1200000",
				/* .target_loads        = */ "75 1200000:85"
			},
			/* .atlas = */ {
				/* .above_hispeed_delay = */ "59000 1200000:79000 1600000:19000",
				/* .boost               = */ "0",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "80000",
				/* .go_hispeed_load     = */ "89",
				/* .hispeed_freq        = */ "1600000",
				/* .target_loads        = */ "80 1200000:90 1600000:90"
			}
		}
	},

	/************************************
	 * PROFILE_HIGH_PERFORMANCE
	 */
	{
		/* .mali = */ {
			/* .dvfs          = */ "1",
			/* .dvfs_governor = */ "3",
			/* .dvfs_min_lock = */ "420",
			/* .dvfs_max_lock = */ "772"
		},
		/* .cpuminfreq = */ {
			/* .apollo = */ "800000",
			/* .atlas = */ "1200000"
		},
		/* .cpumaxfreq = */ {
			/* .apollo = */ "1704000",
			/* .atlas = */ "2304000"
		},
		/* .cpuonline = */ {
			/* .apollo = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "1",
				/* .core4 = */ "1"
			},
			/* .atlas = */ {
				/* .core1 = */ "1",
				/* .core2 = */ "1",
				/* .core3 = */ "1",
				/* .core4 = */ "1"
			}
		},
		/* .cpugov = */ {
			/* .apollo = */ {
				/* .above_hispeed_delay = */ "19000",
				/* .boost               = */ "1",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "80000",
				/* .go_hispeed_load     = */ "75",
				/* .hispeed_freq        = */ "1704000",
				/* .target_loads        = */ "75 1170000:85"
			},
			/* .atlas = */ {
				/* .above_hispeed_delay = */ "59000 1400000:79000 1800000:19000",
				/* .boost               = */ "1",
				/* .boostpulse          = */ "0",
				/* .boostpulse_duration = */ "160000",
				/* .go_hispeed_load     = */ "75",
				/* .hispeed_freq        = */ "2304000",
				/* .target_loads        = */ "70 1400000:80 1800000:90"
			}
		}
	}

};

#endif // EXYNOS5_POWER_HAL_PROFILES_INCLUDED