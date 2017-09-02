/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __APISTATE_H__
#define __APISTATE_H__


#include <vector>


#include "api/NetworkState.h"
#include "jansson.h"
#include "workers/GpuThread.h"
#include "nvidia/Health.h"


class Hashrate;


class ApiState
{
public:
    ApiState();
    ~ApiState();

    const char *get(const char *url, size_t *size) const;
    void setHealth(const std::vector<Health> &health);
    void tick(const Hashrate *hashrate);
    void tick(const NetworkState &results);

private:
    const char *finalize(json_t *reply, size_t *size) const;
    void genId();
    void getConnection(json_t *reply) const;
    void getHashrate(json_t *reply) const;
    void getHealth(json_t *reply) const;
    void getIdentify(json_t *reply) const;
    void getMiner(json_t *reply) const;
    void getResults(json_t *reply) const;

    char m_id[17];
    char m_workerId[128];
    double *m_hashrate;
    double m_highestHashrate;
    double m_totalHashrate[3];
    int m_threads;
    mutable char m_buf[4096];
    NetworkState m_network;
    std::vector<GpuThread> m_gpuThreads;
    std::vector<Health> m_health;
};

#endif /* __APISTATE_H__ */