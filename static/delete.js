const xhr = new XMLHttpRequest();

xhr.open("POST", "/delete_data");

xhr.onload = () => {
    if (xhr.status === 200) {
        alert("Upload successful");
        document.getElementById('successMsg').textContent = "Upload successful!";
        document.getElementById('errorMsg').textContent = "";
    } else {
        alert("No File For That File Id Please Check Again In My Files");
        document.getElementById('errorMsg').textContent = "Upload failed!";
        document.getElementById('successMsg').textContent = "";
    }
};

xhr.onerror = () => {
    document.getElementById('errorMsg').textContent = "Error Please Contact Moderator !";
    document.getElementById('successMsg').textContent = "";
};

xhr.send(file);
