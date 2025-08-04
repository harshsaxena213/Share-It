# 📁 Share-It: Secure File Sharing Platform

A modern, secure, minimalist **file storage and sharing web application** built with a **Crow C++ backend** and a sleek frontend UI crafted using **Perplexity AI** and **Claude**.  
Data storage with **SQLite** and password security using salted SHA-256 hashes.

[![Watch Demo Video](https://img.shields.io/badge/Watch-Demo-blue)](https://project.harshishere.in.net/player.html?video=Share-It%20.mp4)
---

## 🚀 Features

- 💡 **Modern UI** developed with Perplexity & Claude for a smooth frontend experience  
- 🔐 **User Authentication:** Secure registration & login with salted SHA-256 password hashes  
- ⬆️ **File Upload:** Drag & drop or click to upload your files  
- 📥 **File Download:** Secure file access and downloads for logged-in users  
- 📂 **User File Management:** View and manage your personal uploaded files  
- ⚡ **Fast & Lightweight:** Powered by Crow C++ HTTP server, ensuring high performance  
- 🎨 Stylish animations, glassmorphism, neon UI elements for an appealing look  
- 🗑️ File Delete: Easily delete unwanted files securely
---

## 🛠️ Tech Stack

| Layer           | Technologies / Libraries                             |
|-----------------|----------------------------------------------------|
| Backend/API     | C++20, Crow HTTP server                             |
| Database        | SQLite3                                            |
| Security        | OpenSSL (SHA-256 with salt)                        |
| Frontend UI     | HTML5, CSS (glassmorphism, gradients, animations) |
| JavaScript      | Vanilla JS + modern APIs                            |
| UI Prototyping  | Perplexity AI, Claude                              |
| Templating      | Crow::Mustache                                     |

---

## 📁 Project Structure
```
.
├── main.cpp 
├── include/
│ ├── login.h 
│ ├── register.h
│ ├── upload.h
│ ├── download.h 
│ └── files.h
│ └── delete.h
├── static/ 
│ ├── styles.css 
│ ├── main.js 
│ └── upload.js 
├── templates/
├── uploads/ 
├── db.sqlite 
└── file.sqlite 

```


---

## 🚀 Getting Started

### Prerequisites

- **C++20** compatible compiler (g++ or clang++)  
- **Crow** HTTP server headers  
- **OpenSSL** for SHA-256 hashing  
- **SQLite3** library  
- Optional: **Node.js / npm** (for frontend customization)

### Build & Run

```
g++ main.cpp -o filevault -std=c++20 -lcrow -lsqlite3 -lssl -lcrypto 
```

Access the application at http://localhost:8080

---

## 🔐 Security Notes

- Passwords hashed with SHA-256 and salted with username  
- Sessions to maintain user authentication state  
- Files accessible only by owners  
- Input and output are properly sanitized for security  

---

## 💡 UI & UX

- Responsive design with elegant glassmorphic cards  
- Smooth fade and slide animations  
- Drag & drop file uploader with progress indicators  
- Neon accent colors highlight interactions  

---

## ❤️ Credits

- UI prototyping and design help from **Perplexity AI** and **Claude**  
- Backend powered by the **Crow C++ framework**  
- Emoji icons from open sources  

---

## 🤝 Contributing

Pull requests, bug reports, and feature requests are welcome! Please open issues for ideas and improvements.

---

## ☕ License

MIT License — free for personal and commercial uses.

---

Enjoy secure, stylish, and lightning-fast file sharing!  
Made with ❤️ using C++, Perplexity, and Claude.

