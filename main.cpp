/*
 * alsa_test_tool - Simple test tool for alsa devices
 *
 *   copyright 2018   Pascal Huerst <pascal.huerst@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <string>
#include <iostream>
#include <iomanip>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

extern "C" {

#include <alsa/asoundlib.h>

static const unsigned int rates[] = { 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000, 96000 };
static const snd_pcm_format_t formatList[] = {
    SND_PCM_FORMAT_S8,
    SND_PCM_FORMAT_U8,
    SND_PCM_FORMAT_S16,
    SND_PCM_FORMAT_U16,
    SND_PCM_FORMAT_S24,
    SND_PCM_FORMAT_U24,
    SND_PCM_FORMAT_S32,
    SND_PCM_FORMAT_U32
};

static const std::string formatListStrings[] = {
    "SND_PCM_FORMAT_S8",
    "SND_PCM_FORMAT_U8",
    "SND_PCM_FORMAT_S16",
    "SND_PCM_FORMAT_U16",
    "SND_PCM_FORMAT_S24",
    "SND_PCM_FORMAT_U24",
    "SND_PCM_FORMAT_S32",
    "SND_PCM_FORMAT_U32"
};

int main(int argc, char **argv)
{
    if (argc != 2) {

        std::cout << "usage: \n"
                  << "  " << argv[0] << "interface such as: default | hw:0,2 \n"
                  << std::endl;

        exit(EXIT_FAILURE);
    }

    snd_pcm_t *pcm = nullptr;
    snd_pcm_hw_params_t *hw_params = nullptr;

    int ret = 0;

    ret = snd_pcm_hw_params_malloc(&hw_params);
    if (ret < 0) {
        std::cerr << "snd_pcm_hw_params_malloc" << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = snd_pcm_open(&pcm, argv[1], SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC);
    if (ret < 0) {
        std::cerr << "snd_pcm_open" << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = snd_pcm_hw_params_any(pcm, hw_params);
    if (ret < 0) {
        std::cerr << "snd_pcm_hw_params_any" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Supported Samplerates: ";

    for (unsigned int i=0; i<ARRAY_SIZE(rates); ++i) {
        if (!snd_pcm_hw_params_test_rate(pcm, hw_params, rates[i], 0))
            std::cout << std::setw(5) << rates[i] << "  ";
    }
    std::cout << std::endl;

    std::cout << "Supported Formats: ";

    for (unsigned int i=0; i<ARRAY_SIZE(formatList); ++i) {
        if (!snd_pcm_hw_params_test_format(pcm, hw_params, formatList[i]))
            std::cout << formatListStrings[i] << "  ";
    }
    std::cout << std::endl;

    return 0;
}

}
