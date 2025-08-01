// Upload
if (document.getElementById('uploadForm')) {
    document.getElementById('uploadForm').addEventListener('submit', async function(e) {
        e.preventDefault();
        const file = this.file.files[0];
        document.getElementById('successMsg').textContent = '';
        document.getElementById('errorMsg').textContent = '';
        const fd = new FormData();
        fd.append('file', file);
        try {
            const res = await fetch('/upload', { method: 'POST', body: fd });
            if (!res.ok) throw new Error();
            const {fileid, filename} = await res.json();
            document.getElementById('successMsg').innerHTML = `Uploaded! <a target="_blank" href="/download/${fileid}">${filename}</a>`;
        } catch { document.getElementById('errorMsg').textContent = 'Upload failed.'; }
    });
}

// Login
if (document.getElementById('loginForm')) {
    document.getElementById('loginForm').addEventListener('submit', async function(e) {
        e.preventDefault();
        document.getElementById('successMsg').textContent = '';
        document.getElementById('errorMsg').textContent = '';
        const data = {
            username: this.username.value,
            password: this.password.value
        };
        try {
            const res = await fetch('/login', {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify(data)
            });
            if (!res.ok) throw new Error();
            document.getElementById('successMsg').textContent = 'Login successful!';
        } catch { document.getElementById('errorMsg').textContent = 'Login failed.'; }
    });
}

// Register
if (document.getElementById('registerForm')) {
    document.getElementById('registerForm').addEventListener('submit', async function(e) {
        e.preventDefault();
        document.getElementById('successMsg').textContent = '';
        document.getElementById('errorMsg').textContent = '';
        const data = {
            username: this.username.value,
            password: this.password.value
        };
        try {
            const res = await fetch('/register', {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify(data)
            });
            if (!res.ok) throw new Error();
            document.getElementById('successMsg').textContent = 'Registration successful!';
        } catch { document.getElementById('errorMsg').textContent = 'Registration failed.'; }
    });
}

// Download
if (document.getElementById('downloadForm')) {
    document.getElementById('downloadForm').addEventListener('submit', function(e) {
        e.preventDefault();
        const fileid = this.fileid.value.trim();
        if (fileid) {
            window.open(`/download/${fileid}`, "_blank");
        } else {
            document.getElementById('errorMsg').textContent = 'Please enter a file ID.';
        }
    });
}

// File list
if (document.getElementById('fileList')) {
    (async function(){
        try {
            const res = await fetch('/files');
            if (!res.ok) throw new Error();
            const files = await res.json();
            let html = '';
            files.forEach(f => {
                html += `<div><a class="file-link" href="/download/${f.fileid}" target="_blank">${f.filename}</a> (${f.size} bytes)</div>`;
            });
            document.getElementById('fileList').innerHTML = html.length ? html : 'No files.';
        } catch {
            document.getElementById('fileList').innerHTML = 'Could not load files.';
        }
    })();
}
