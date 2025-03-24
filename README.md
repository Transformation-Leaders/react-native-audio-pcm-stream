# react-native-audio-pcm-stream

Streame PCM-Audiodaten in Echtzeit für React Native - ideal für Spracherkennung und Live-Transkription mit OpenAI Modellen wie "gpt-4o-transcribe".

Diese Bibliothek sendet kontinuierlich Audio-Daten als base64-kodierte PCM-Chunks und ist optimiert für:
- Live Spracherkennung und Transkription
- OpenAI Speech-to-Text API Integration
- Echtzeit-Audio-Verarbeitung
- Reduzierte Speichernutzung (keine Audiodateien nötig)

## Installation

```bash
# Via npm
npm install @transformation-leaders/react-native-audio-pcm-stream

# Oder über GitHub
npm install https://github.com/Transformation-Leaders/react-native-audio-pcm-stream.git

# iOS: Dependencies installieren
cd ios && pod install
```

## Mikrofonberechtigungen hinzufügen

### iOS
Füge folgende Zeilen zu deiner `ios/[DEIN_APP_NAME]/Info.plist` hinzu:
```xml
<key>NSMicrophoneUsageDescription</key>
<string>Wir benötigen Zugriff auf dein Mikrofon für Audioaufnahmen.</string>
```

### Android
Füge folgende Zeile zu deiner `android/app/src/main/AndroidManifest.xml` hinzu:
```xml
<uses-permission android:name="android.permission.RECORD_AUDIO" />
```

## Grundlegende Verwendung

```javascript
import AudioStreamPCM from '@transformation-leaders/react-native-audio-pcm-stream';

// Konfigurationsoptionen
const options = {
  sampleRate: 16000,  // 16kHz für Spracherkennung (OpenAI empfiehlt 16kHz)
  channels: 1,        // Mono-Audio
  bitsPerSample: 16,  // 16-bit PCM
  audioSource: 6,     // Android: VOICE_RECOGNITION
  bufferSize: 4096    // Größere Puffer für stabilere Aufnahmen
};

// Initialisieren
AudioStreamPCM.init(options);

// Event-Listener für Audiodaten
AudioStreamPCM.on('data', (data) => {
  // Base64-kodierte PCM-Audiodaten
  console.log(`Audio-Chunk empfangen: ${data.length} Bytes`);
  
  // Hier können die Daten an OpenAI oder andere Dienste gesendet werden
});

// Error-Event-Listener (NEU)
AudioStreamPCM.on('error', (errorMessage) => {
  console.error('Audio-Aufnahme-Fehler:', errorMessage);
  // Fehlerbehandlung, z.B. für verweigerte Berechtigungen
});

// Starte die Aufnahme
AudioStreamPCM.start();

// Später, um die Aufnahme zu beenden
AudioStreamPCM.stop();
```

## Integration mit OpenAI Transkriptionsmodellen

Diese Bibliothek ist ideal für die Integration mit OpenAI's Echtzeit-Transkriptionsmodellen wie "gpt-4o-transcribe" oder "whisper-1".

## Neue Funktionen

### Error-Events
Die Bibliothek sendet jetzt `error`-Events für verschiedene Fehlerszenarien:
- Verweigerte Mikrofonberechtigungen
- Probleme bei der Initialisierung des Audiosystems
- Fehler während der Aufnahme

```javascript
AudioStreamPCM.on('error', (errorMessage) => {
  console.error('Audio-Aufnahme-Fehler:', errorMessage);
  // Hier entsprechende UI-Hinweise oder Berechtigungsanfragen anzeigen
});
```

### Verbesserte Logs
Die iOS-Implementierung enthält jetzt detaillierte Logs, die bei der Fehlersuche helfen:
- Protokolliert erhaltene Audiodaten-Größe
- Zeigt Fehler bei der Audio-Session-Konfiguration
- Benachrichtigt bei leeren Audio-Puffern

### Optimierungen für OpenAI Transkription
- Verbesserte Pufferverwaltung für kontinuierliche Audiostreams
- Automatisches Base64-Encoding im korrekten Format für OpenAI API
- Optimierte Probenahmerate von 16kHz für beste Spracherkennungsergebnisse

## API-Referenz

### Methoden

#### `init(options)`
Initialisiert den Audio-Stream mit angegebenen Optionen.

**Parameter:**
- `options` (Object):
  - `sampleRate` (Number): Abtastrate in Hz (Standard: 44100)
  - `channels` (Number): Anzahl der Kanäle (1 oder 2, Standard: 1)
  - `bitsPerSample` (Number): Bits pro Sample (8 oder 16, Standard: 16)
  - `bufferSize` (Number): Puffergröße (Standard: 2048)
  - `audioSource` (Number): Nur Android - Audio-Quelle (Standard: 6 für VOICE_RECOGNITION)

#### `start()`
Startet die Audio-Aufnahme. Fordert automatisch Mikrofonberechtigungen an.

#### `stop()`
Stoppt die Audio-Aufnahme und gibt Ressourcen frei.

### Events

#### `data`
Wird ausgelöst, wenn neue Audio-Daten verfügbar sind.
- Callback erhält base64-kodierte PCM-Audiodaten als String.

#### `error`
Wird ausgelöst, wenn ein Fehler auftritt.
- Callback erhält eine Fehlermeldung als String.

## Tipps zur Optimierung

### Für OpenAI Whisper/Transkription
- Verwende 16kHz Abtastrate für optimale Ergebnisse mit OpenAI's Modellen
- Mono-Audio (1 Kanal) ist ausreichend für Spracherkennung
- Eine Puffergröße von 4096 bietet gute Balance zwischen Latenz und Stabilität

### Für ressourcenschonende Verwendung
- Höre ordnungsgemäß auf alle Events, um Speicherlecks zu vermeiden
- Stoppe die Aufnahme, wenn sie nicht benötigt wird
- Entferne Event-Listener in useEffect-Cleanup-Funktionen

## Fehlerbehebung

### Kein Audio-Stream auf iOS
- Stelle sicher, dass `NSMicrophoneUsageDescription` in der Info.plist vorhanden ist
- Prüfe, ob Mikrofon-Berechtigungen vom Benutzer gewährt wurden
- Achte auf 'error'-Events für genaue Diagnose

### Probleme auf Android
- Überprüfe die RECORD_AUDIO-Berechtigung im Manifest
- Bei älteren Android-Versionen könnte eine explizite Berechtigungsanfrage nötig sein

## Lizenz
MIT
