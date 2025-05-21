# AIHT_UNIT-1

## Mood-based Music Recommendation using NLP

## Team Members

| Name         | Roll Number |
| ------------ | ----------- |
| Ayush Arora  | 2022UCA1822 |
| Aayush Bagga | 2022UCA1806 |
| Saaz Gupta   | 2022UCA1860 |

---

### Short Description

This project implements a mood-based music recommendation system using sentiment analysis of user input. The model leverages an LSTM-based deep learning architecture trained on a cleaned, tokenized, and one-hot encoded dataset of tweets. After classifying text into positive, negative, or neutral sentiment, the system recommends music that aligns with the detected emotion. The trained model is optimized using TensorFlow Lite for deployment on an embedded system (ESP32), displaying recommendations on a 20x4 LCD. This integration demonstrates real-time natural language understanding and music personalization on resource-constrained IoT hardware.

---

### Shortcomings

1. **Limited Dataset Context**: The model uses a generic sentiment dataset (tweets), which may not directly represent music-related emotions or user preferences.
2. **Simplified Sentiment Mapping**: Mapping sentiments (positive/negative/neutral) to specific music choices might oversimplify complex user emotions or contexts.
3. **Embedded Output Constraints**: The LCD-based output restricts rich recommendation presentation (e.g., album art, song previews), affecting user experience.

---

### Future Extensions

1. **Use Domain-Specific Datasets**: Incorporate user reviews or feedback from music platforms (e.g., Spotify or YouTube comments) to build a domain-aware sentiment model.
2. **Integrate Multimodal Inputs**: Combine text, voice, and facial expressions for a more holistic emotion detection and music recommendation engine.
3. **Enhance Output Interface**: Replace the LCD with a mobile/web dashboard for displaying richer media content like album covers, audio previews, and playlist controls.

[Project Report (Google Docs)](https://docs.google.com/document/d/11nHCWvqMKL-_JNvWQ2UFADc0I4EKkoSAPQggzxWVBUQ/edit?usp=sharing)

[Demo Video](https://youtu.be/c372G6jbmL4)
