const int channel = 0;
const int tap_tempo_pin = 0;
const int tap_tempo_active = LOW;
const int tap_tempo_cc = 114;
const int tap_tempo_value = 0;

// TODO...
//const int tap_lfo_pin = 2;

const long debounce_ms = 50;

long tap_tempo_last_ms = 0;
bool tap_tempo_state = !tap_tempo_active;

void setup() {
  Serial1.begin(31250);
  pinMode(tap_tempo_pin, INPUT_PULLUP);
}

void loop() {
  long time = millis();
  int tap_tempo_pin_state = digitalRead(tap_tempo_pin);

  if ((tap_tempo_pin_state != tap_tempo_state)
       && (time - tap_tempo_last_ms >= debounce_ms)) {
    if (tap_tempo_pin_state == tap_tempo_active) {
      tx_cc(channel, tap_tempo_cc, tap_tempo_value);
    }
    tap_tempo_last_ms = time;
    tap_tempo_state = !tap_tempo_state;
  }
}

// channel: 0-15
// cc: 0-119
// value: 0-127
void tx_cc(int channel, int cc, int value) {
  Serial1.write(0b10110000 | (channel & 0b1111));
  Serial1.write(cc & 0b1111111);
  Serial1.write(value & 0b1111111);
}
