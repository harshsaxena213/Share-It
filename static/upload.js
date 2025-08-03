document.getElementById('uploadForm').addEventListener('submit', function(e) {
    e.preventDefault();  // Stop normal form submit

    const input = document.querySelector('input[type="file"]');
    const file = input.files[0];
    if (!file) {
        alert('Please select a file first');
        return;
    }

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "/upload_data");
    xhr.setRequestHeader("X-Filename", file.name);
    xhr.onload = () => {
        if (xhr.status === 200) {
            alert("Upload successful");
            document.getElementById('successMsg').alert = "Upload successful!";
            document.getElementById('errorMsg').textContent = "";
        } else {
            alert("Upload failed");
            document.getElementById('errorMsg').textContent = "Upload failed!";
            document.getElementById('successMsg').textContent = "";
        }
    };
    xhr.onerror = () => {
        document.getElementById('errorMsg').textContent = "Upload error!";
        document.getElementById('successMsg').textContent = "";
    };
    xhr.send(file);
});
