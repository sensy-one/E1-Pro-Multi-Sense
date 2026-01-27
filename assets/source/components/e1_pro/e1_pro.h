#pragma once

#include "esphome.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"
#include <cmath>
#include <vector>

namespace esphome {
namespace e1_pro {

class LD2460 : public Component, public uart::UARTDevice {
 public:
  LD2460();

  void set_exclusion_zone_points_count(number::Number *count) { exclusion_zone_points_count = count; }
  void set_exclusion_zone_p1_x(number::Number *p) { exclusion_zone_points[0][0] = p; }
  void set_exclusion_zone_p1_y(number::Number *p) { exclusion_zone_points[0][1] = p; }
  void set_exclusion_zone_p2_x(number::Number *p) { exclusion_zone_points[1][0] = p; }
  void set_exclusion_zone_p2_y(number::Number *p) { exclusion_zone_points[1][1] = p; }
  void set_exclusion_zone_p3_x(number::Number *p) { exclusion_zone_points[2][0] = p; }
  void set_exclusion_zone_p3_y(number::Number *p) { exclusion_zone_points[2][1] = p; }
  void set_exclusion_zone_p4_x(number::Number *p) { exclusion_zone_points[3][0] = p; }
  void set_exclusion_zone_p4_y(number::Number *p) { exclusion_zone_points[3][1] = p; }
  void set_exclusion_zone_p5_x(number::Number *p) { exclusion_zone_points[4][0] = p; }
  void set_exclusion_zone_p5_y(number::Number *p) { exclusion_zone_points[4][1] = p; }
  void set_exclusion_zone_p6_x(number::Number *p) { exclusion_zone_points[5][0] = p; }
  void set_exclusion_zone_p6_y(number::Number *p) { exclusion_zone_points[5][1] = p; }
  void set_exclusion_zone_p7_x(number::Number *p) { exclusion_zone_points[6][0] = p; }
  void set_exclusion_zone_p7_y(number::Number *p) { exclusion_zone_points[6][1] = p; }
  void set_exclusion_zone_p8_x(number::Number *p) { exclusion_zone_points[7][0] = p; }
  void set_exclusion_zone_p8_y(number::Number *p) { exclusion_zone_points[7][1] = p; }

  void set_installation_method_select(select::Select *s) { install_mode_select_ = s; }
  void set_installation_angle_select(select::Select *s) { install_angle_select_ = s; }
  void set_installation_height_select(select::Select *s) { install_height_select_ = s; }
  void set_sensitivity_select(select::Select *s) { sensitivity_select_ = s; }
  void set_side_range_select(number::Number *s) { side_range_select_ = s; }
  void set_top_range_select(number::Number *s) { top_range_select_ = s; }

  void send_restart();
  void send_factory_reset();
  void send_set_installation_mode(bool top);
  void send_set_installation_params(float height_m, float angle_deg);
  void send_set_detection_range(float distance_m, float angle_start_deg, float angle_end_deg);
  void send_set_sensitivity(uint8_t value);

  void send_query_installation_mode();
  void send_query_installation_params();
  void send_query_detection_range();
  void send_query_sensitivity();
  void query_all_settings();

  void setup() override;
  void loop() override;

 protected:
  void parse_frame(const uint8_t *b, uint16_t len);
  void parse_command_frame_(const uint8_t *b, uint16_t len);
  void send_frame_(uint8_t function, const std::vector<uint8_t> &data_content);
  bool is_in_exclusion_zone(float x, float y);

  struct Track {
    float  x{0}, y{0}, angle{0}, dist{0};
  } tracks_[5];

  void publish_zero_(int t);
  void publish_track_(int t, const Track &tr);
  void update_track_(int t, bool meas_valid,
                     float x, float y, float angle, float dist);

 public:
  sensor::Sensor *target1_x, *target1_y, *target1_angle, *target1_distance;
  sensor::Sensor *target2_x, *target2_y, *target2_angle, *target2_distance;
  sensor::Sensor *target3_x, *target3_y, *target3_angle, *target3_distance;
  sensor::Sensor *target4_x, *target4_y, *target4_angle, *target4_distance;
  sensor::Sensor *target5_x, *target5_y, *target5_angle, *target5_distance;

  number::Number *exclusion_zone_points_count{nullptr};
  number::Number *exclusion_zone_points[8][2]{};

  select::Select *install_mode_select_{nullptr};
  select::Select *install_angle_select_{nullptr};
  select::Select *install_height_select_{nullptr};
  select::Select *sensitivity_select_{nullptr};
  number::Number *side_range_select_{nullptr};
  number::Number *top_range_select_{nullptr};

  static constexpr int kMaxFrame = 96;
  uint8_t rx_buf_[kMaxFrame]{};
  int header_pos_{0};
  int idx_{0};
  uint16_t expected_len_{0};
  uint8_t func_{0};
  bool target_frame_{false};
  enum class RxState { SYNC, READ_HEADER, READ_FUNC, READ_LEN1, READ_LEN2, READ_REST };
  RxState rx_state_{RxState::SYNC};
  uint8_t current_mode_{0x00};
  float pending_range_cm_{0.0f};
  bool pending_range_valid_{false};
  float pending_height_m_{0.0f};
  float pending_angle_deg_{0.0f};
  bool pending_params_valid_{false};
  uint32_t query_generation_{0};
};

inline LD2460::LD2460() : Component(), uart::UARTDevice() {
  target1_x        = new sensor::Sensor(); target1_y        = new sensor::Sensor();
  target1_angle    = new sensor::Sensor(); target1_distance = new sensor::Sensor();
  target2_x        = new sensor::Sensor(); target2_y        = new sensor::Sensor();
  target2_angle    = new sensor::Sensor(); target2_distance = new sensor::Sensor();
  target3_x        = new sensor::Sensor(); target3_y        = new sensor::Sensor();
  target3_angle    = new sensor::Sensor(); target3_distance = new sensor::Sensor();
  target4_x        = new sensor::Sensor(); target4_y        = new sensor::Sensor();
  target4_angle    = new sensor::Sensor(); target4_distance = new sensor::Sensor();
  target5_x        = new sensor::Sensor(); target5_y        = new sensor::Sensor();
  target5_angle    = new sensor::Sensor(); target5_distance = new sensor::Sensor();
}

inline void LD2460::send_frame_(uint8_t function, const std::vector<uint8_t> &data_content) {
  const uint8_t header[4] = {0xFD, 0xFC, 0xFB, 0xFA};
  const uint8_t footer[4] = {0x04, 0x03, 0x02, 0x01};
  std::vector<uint8_t> frame;
  uint16_t total_len = 4 + 1 + 2 + data_content.size() + 4;
  frame.reserve(total_len);
  frame.insert(frame.end(), header, header + 4);
  frame.push_back(function);
  frame.push_back(total_len & 0xFF);
  frame.push_back((total_len >> 8) & 0xFF);
  frame.insert(frame.end(), data_content.begin(), data_content.end());
  frame.insert(frame.end(), footer, footer + 4);
  this->write_array(frame.data(), frame.size());
}

inline void LD2460::send_restart() { send_frame_(0x0D, {0x01}); }
inline void LD2460::send_factory_reset() { send_frame_(0x10, {0x01}); }

inline void LD2460::send_set_installation_mode(bool top) {
  uint8_t mode = static_cast<uint8_t>(top ? 0x02 : 0x01);
  send_frame_(0x09, {mode});
}

inline void LD2460::send_set_installation_params(float height_m, float angle_deg) {
  uint16_t height_val = static_cast<uint16_t>(std::round(height_m * 100.0f));
  uint16_t angle_val = static_cast<uint16_t>(std::round(angle_deg * 100.0f));
  send_frame_(0x07, {
    (uint8_t)(height_val & 0xFF), (uint8_t)(height_val >> 8),
    (uint8_t)(angle_val & 0xFF), (uint8_t)(angle_val >> 8)
  });
}

inline void LD2460::send_set_detection_range(float distance_m, float angle_start_deg, float angle_end_deg) {
  if (current_mode_ == 0x01) {
    if (angle_start_deg >= 0.0f || angle_end_deg <= 0.0f) return;
  } else if (current_mode_ == 0x02) {
    if (angle_start_deg < 0.0f) return;
  } else {
    return;
  }
  uint8_t dist_val = static_cast<uint8_t>(std::round(distance_m * 10.0f));
  int16_t start_val = static_cast<int16_t>(std::round(angle_start_deg * 10.0f));
  int16_t end_val = static_cast<int16_t>(std::round(angle_end_deg * 10.0f));
  uint16_t start_u = static_cast<uint16_t>(start_val);
  uint16_t end_u = static_cast<uint16_t>(end_val);
  send_frame_(0x11, {
    dist_val,
    (uint8_t)(start_u & 0xFF), (uint8_t)(start_u >> 8),
    (uint8_t)(end_u & 0xFF), (uint8_t)(end_u >> 8)
  });
}

inline void LD2460::send_set_sensitivity(uint8_t value) { send_frame_(0x13, {value}); }
inline void LD2460::send_query_installation_mode() { send_frame_(0x0A, {0x01}); }
inline void LD2460::send_query_installation_params() { send_frame_(0x08, {0x01}); }
inline void LD2460::send_query_detection_range() { send_frame_(0x12, {0x01}); }
inline void LD2460::send_query_sensitivity() { send_frame_(0x14, {0x01}); }

inline void LD2460::query_all_settings() {
  const uint32_t gen = ++query_generation_;
  current_mode_ = 0x00;
  pending_range_valid_ = false;
  pending_params_valid_ = false;

  this->set_timeout(0, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_installation_mode();
  });
  this->set_timeout(50, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_installation_params();
  });
  this->set_timeout(100, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_sensitivity();
  });
  this->set_timeout(200, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_detection_range();
  });

  this->set_timeout(500, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_installation_mode();
  });
  this->set_timeout(550, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_installation_params();
  });
  this->set_timeout(600, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_sensitivity();
  });
  this->set_timeout(650, [this, gen]() {
    if (gen != query_generation_) return;
    send_query_detection_range();
  });
}

inline void LD2460::setup() {
}

inline void LD2460::loop() {
  static constexpr uint8_t TARGET_HEADER[4] = {0xF4, 0xF3, 0xF2, 0xF1};
  static constexpr uint8_t TARGET_TAIL[4] = {0xF8, 0xF7, 0xF6, 0xF5};
  static constexpr uint8_t CMD_HEADER[4] = {0xFD, 0xFC, 0xFB, 0xFA};
  static constexpr uint8_t CMD_TAIL[4] = {0x04, 0x03, 0x02, 0x01};

  while (available()) {
    int c = read();
    if (c < 0) break;
    uint8_t b = static_cast<uint8_t>(c);

    switch (rx_state_) {
      case RxState::SYNC:
        if (b == TARGET_HEADER[0] || b == CMD_HEADER[0]) {
          target_frame_ = (b == TARGET_HEADER[0]);
          rx_buf_[0] = b;
          header_pos_ = 1;
          rx_state_ = RxState::READ_HEADER;
        }
        break;

      case RxState::READ_HEADER: {
        const uint8_t *header = target_frame_ ? TARGET_HEADER : CMD_HEADER;
        if (b == header[header_pos_]) {
          rx_buf_[header_pos_++] = b;
          if (header_pos_ == 4) {
            idx_ = 4;
            rx_state_ = RxState::READ_FUNC;
          }
        } else if (b == TARGET_HEADER[0] || b == CMD_HEADER[0]) {
          target_frame_ = (b == TARGET_HEADER[0]);
          rx_buf_[0] = b;
          header_pos_ = 1;
        } else {
          rx_state_ = RxState::SYNC;
          header_pos_ = 0;
        }
        break;
      }

      case RxState::READ_FUNC:
        func_ = b;
        rx_buf_[idx_++] = b;
        rx_state_ = RxState::READ_LEN1;
        break;

      case RxState::READ_LEN1:
        rx_buf_[idx_++] = b;
        expected_len_ = b;
        rx_state_ = RxState::READ_LEN2;
        break;

      case RxState::READ_LEN2: {
        rx_buf_[idx_++] = b;
        expected_len_ |= static_cast<uint16_t>(b) << 8;
        if (expected_len_ < 11 || expected_len_ > kMaxFrame) {
          rx_state_ = RxState::SYNC;
          header_pos_ = 0;
          idx_ = 0;
          expected_len_ = 0;
          break;
        }
        rx_state_ = RxState::READ_REST;
        break;
      }

      case RxState::READ_REST:
        rx_buf_[idx_++] = b;
        if (idx_ >= expected_len_) {
          bool tail_ok = true;
          const uint8_t *tail = target_frame_ ? TARGET_TAIL : CMD_TAIL;
          for (int i = 0; i < 4; ++i) {
            if (rx_buf_[expected_len_ - 4 + i] != tail[i]) {
              tail_ok = false;
              break;
            }
          }
          if (tail_ok) {
            if (target_frame_ && func_ == 0x04) {
              parse_frame(rx_buf_, expected_len_);
            } else if (!target_frame_) {
              parse_command_frame_(rx_buf_, expected_len_);
            }
          }
          rx_state_ = RxState::SYNC;
          header_pos_ = 0;
          idx_ = 0;
          expected_len_ = 0;
        }
        break;
    }
  }
}

inline void LD2460::parse_command_frame_(const uint8_t *b, uint16_t len) {
  if (len < 11) return;
  uint8_t func = b[4];
  uint16_t payload_len = len - 11;
  const uint8_t *data = &b[7];

  if (func == 0x0A) {
    if (payload_len < 1) return;
    uint8_t mode = data[0];
    if (mode != 0x01 && mode != 0x02) return;
    current_mode_ = mode;
    if (install_mode_select_) {
      install_mode_select_->publish_state(mode == 0x01 ? "Side" : "Top");
    }
    if (mode == 0x01) {
      if (top_range_select_) top_range_select_->publish_state(0.0f);
    } else if (mode == 0x02) {
      if (install_angle_select_) install_angle_select_->publish_state("0");
      if (install_height_select_) install_height_select_->publish_state("0");
      if (side_range_select_) side_range_select_->publish_state(0.0f);
      pending_params_valid_ = false;
    }
    if (pending_params_valid_ && mode == 0x01) {
      pending_params_valid_ = false;
      char buf[8];
      snprintf(buf, sizeof(buf), "%.1f", pending_height_m_);
      if (install_height_select_) install_height_select_->publish_state(buf);
      snprintf(buf, sizeof(buf), "%.0f", pending_angle_deg_);
      if (install_angle_select_) install_angle_select_->publish_state(buf);
    }
    if (pending_range_valid_) {
      pending_range_valid_ = false;
      if (current_mode_ == 0x01) {
        if (side_range_select_) side_range_select_->publish_state(pending_range_cm_);
      } else if (current_mode_ == 0x02) {
        if (top_range_select_) top_range_select_->publish_state(pending_range_cm_);
      }
    }
    const uint32_t gen = query_generation_;
    if (mode == 0x01) {
      this->set_timeout(120, [this, gen]() {
        if (gen != query_generation_) return;
        send_query_installation_params();
      });
    }
    this->set_timeout(180, [this, gen]() {
      if (gen != query_generation_) return;
      send_query_detection_range();
    });
    return;
  }

  if (func == 0x08) {
    if (payload_len < 4) return;
    uint16_t height_raw = static_cast<uint16_t>(data[0] | (data[1] << 8));
    uint16_t angle_raw = static_cast<uint16_t>(data[2] | (data[3] << 8));

    float height_m = height_raw / 100.0f;
    float angle_deg = angle_raw / 100.0f;
    if (current_mode_ == 0x00) {
      pending_height_m_ = height_m;
      pending_angle_deg_ = angle_deg;
      pending_params_valid_ = true;
      return;
    }
    if (current_mode_ != 0x01) return;

    char buf[8];
    snprintf(buf, sizeof(buf), "%.1f", height_m);
    if (install_height_select_) install_height_select_->publish_state(buf);

    snprintf(buf, sizeof(buf), "%.0f", angle_deg);
    if (install_angle_select_) install_angle_select_->publish_state(buf);
    return;
  }

  if (func == 0x12) {
    if (payload_len < 5) return;
    float dist_cm = data[0] * 10.0f;

    if (current_mode_ == 0x01) {
      if (side_range_select_) side_range_select_->publish_state(dist_cm);
    } else if (current_mode_ == 0x02) {
      if (top_range_select_) top_range_select_->publish_state(dist_cm);
    } else {
      pending_range_cm_ = dist_cm;
      pending_range_valid_ = true;
    }
    return;
  }

  if (func == 0x14) {
    if (payload_len < 1) return;
    uint8_t val = data[0];
    const char *level = (val == 0x01 ? "High" : (val == 0x02 ? "Medium" : "Low"));
    if (sensitivity_select_) sensitivity_select_->publish_state(level);
    return;
  }
}

inline bool LD2460::is_in_exclusion_zone(float x, float y) {
  if (!exclusion_zone_points_count) return false;
  int n = (int) exclusion_zone_points_count->state;
  if (n < 3) return false;
  if (n > 8) n = 8;
  static int cached_n = -1;
  static float xs[8], ys[8], inv_dy[8], minx=0, maxx=0, miny=0, maxy=0;
  bool changed = (cached_n != n);
  float txs[8], tys[8];
  for (int i = 0; i < n; ++i) {
    txs[i] = exclusion_zone_points[i][0] ? exclusion_zone_points[i][0]->state : 0.0f;
    tys[i] = exclusion_zone_points[i][1] ? exclusion_zone_points[i][1]->state : 0.0f;
    if (!changed && (txs[i] != xs[i] || tys[i] != ys[i])) changed = true;
  }
  if (changed) {
    cached_n = n; minx=maxx=txs[0]; miny=maxy=tys[0];
    for (int i=0; i<n; ++i) {
      xs[i]=txs[i]; ys[i]=tys[i];
      if (xs[i]<minx) minx=xs[i]; if (xs[i]>maxx) maxx=xs[i];
      if (ys[i]<miny) miny=ys[i]; if (ys[i]>maxy) maxy=ys[i];
    }
    for (int i=0, j=n-1; i<n; j=i++) {
      float dy = ys[j]-ys[i];
      inv_dy[i] = (std::fabs(dy) < 1e-6f) ? 0.0f : 1.0f/dy;
    }
  }
  if (x<minx || x>maxx || y<miny || y>maxy) return false;
  bool inside = false;
  for (int i=0, j=n-1; i<n; j=i++) {
    if (((ys[i]>y) != (ys[j]>y)) && (x < (xs[j]-xs[i]) * (y-ys[i]) * inv_dy[i] + xs[i])) inside = !inside;
  }
  return inside;
}

inline void LD2460::publish_zero_(int t) {
  sensor::Sensor* xs[5]={target1_x,target2_x,target3_x,target4_x,target5_x};
  sensor::Sensor* ys[5]={target1_y,target2_y,target3_y,target4_y,target5_y};
  sensor::Sensor* ang[5]={target1_angle,target2_angle,target3_angle,target4_angle,target5_angle};
  sensor::Sensor* ds[5]={target1_distance,target2_distance,target3_distance,target4_distance,target5_distance};
  if(xs[t]) xs[t]->publish_state(0.0f); if(ys[t]) ys[t]->publish_state(0.0f);
  if(ang[t]) ang[t]->publish_state(0.0f); if(ds[t]) ds[t]->publish_state(0.0f);
}

inline void LD2460::publish_track_(int t, const Track &tr) {
  sensor::Sensor* xs[5]={target1_x,target2_x,target3_x,target4_x,target5_x};
  sensor::Sensor* ys[5]={target1_y,target2_y,target3_y,target4_y,target5_y};
  sensor::Sensor* ang[5]={target1_angle,target2_angle,target3_angle,target4_angle,target5_angle};
  sensor::Sensor* ds[5]={target1_distance,target2_distance,target3_distance,target4_distance,target5_distance};
  if(xs[t]) xs[t]->publish_state(tr.x); if(ys[t]) ys[t]->publish_state(tr.y);
  if(ang[t]) ang[t]->publish_state(tr.angle); if(ds[t]) ds[t]->publish_state(tr.dist);
}

inline void LD2460::update_track_(int t, bool meas_valid, float x, float y, float angle, float dist) {
  Track &tr = tracks_[t];
  if (meas_valid) { tr.x=x; tr.y=y; tr.angle=angle; tr.dist=dist; publish_track_(t, tr); return; }
  tr = Track{}; publish_zero_(t);
}

inline void LD2460::parse_frame(const uint8_t *b, uint16_t len) {
  if (len < 11) return;
  if (b[0] != 0xF4 || b[1] != 0xF3 || b[2] != 0xF2 || b[3] != 0xF1) return;
  if (b[4] != 0x04) return;
  uint16_t payload_len = len - 11;
  if ((payload_len % 4) != 0) return;
  int n = payload_len / 4;
  if (n > 5) n = 5;

  static constexpr float kPi = 3.14159265358979323846f;

  for (int t = 0; t < 5; ++t) {
    if (t >= n) {
      update_track_(t, false, 0.0f, 0.0f, 0.0f, 0.0f);
      continue;
    }

    int base = 7 + t * 4;
    int16_t x_raw = (int16_t) (uint16_t(b[base]) | (uint16_t(b[base + 1]) << 8));
    int16_t y_raw = (int16_t) (uint16_t(b[base + 2]) | (uint16_t(b[base + 3]) << 8));

    const bool top_mode = (current_mode_ == 0x02);

    float x_m = float(x_raw) * 0.1f;
    float y_m = float(y_raw) * 0.1f;

    if (!top_mode && y_m < 0.0f) y_m = 0.0f;
    if (top_mode) x_m = -x_m;

    float dist_m = std::hypot(x_m, y_m);

    float angle = (dist_m > 0.0f) ? (std::atan2(x_m, y_m) * 180.0f / kPi) : 0.0f;

    if (top_mode) {
      if (angle < 0.0f) angle += 360.0f;
    } else {
    }

    float x_cm = x_m * 100.0f;
    float y_cm = y_m * 100.0f;
    float dist_cm = dist_m * 100.0f;

    bool valid = (dist_cm > 0.0f) && !is_in_exclusion_zone(x_cm, y_cm);
    update_track_(t, valid, x_cm, y_cm, angle, dist_cm);
  }
}

}
}