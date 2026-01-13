#pragma once

#define  LGFX_USE_V1

#include <LovyanGFX.hpp>

class LGFX :  public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9341  _panel_instance;
  lgfx::Bus_SPI        _bus_instance;
  lgfx::Touch_XPT2046  _touch_instance;
public:
  LGFX(void)
  { // Configure bus control settings.

      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode    = 0;
      cfg.freq_write  = 40000000;  // 80000000 
      cfg.freq_read   = 16000000;
      cfg.spi_3wire   = true;
      cfg.use_lock    = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 14;            // SPI SCLK
      cfg.pin_mosi = 13;            // SPI MOSI
      cfg.pin_miso = 12;            // SPI MISO    (-1 = disable)
      cfg.pin_dc   =  2;            // SPI D/C A0  (-1 = disable)
      
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    { // Set display panel controls.

      auto cfg = _panel_instance.config();

      cfg.pin_cs           =    15;  // CS    (-1 = disable)
      cfg.pin_rst          =    -1;  // RST   (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSY  (-1 = disable)

      cfg.panel_width      =   240;
      cfg.panel_height     =   320;
      cfg.offset_x         =     0;
      cfg.offset_y         =     0;
      cfg.offset_rotation  =     2;
      cfg.dummy_read_pixel =     8;
      cfg.dummy_read_bits  =     1;
      cfg.readable         =  true;
      cfg.invert           = false;
      cfg.rgb_order        = false;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       =  true;

      _panel_instance.config(cfg);
    }
    { // Configure settings for touch screen control.  (delete if not necessary)

      auto cfg = _touch_instance.config();

      cfg.x_min      =   0;    // numbers doesn't work
      cfg.x_max      = 127;
      cfg.y_min      =   0;
      cfg.y_max      = 159;
    //cfg.pin_int    =  -1;
      cfg.bus_shared = true;
      cfg.offset_rotation = 0;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
    }
    setPanel(&_panel_instance); // Sets the panel to use.
  }
};