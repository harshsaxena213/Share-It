       // Page navigation
        function showPage(pageName) {
            // Hide all pages
            const pages = ['welcomePage', 'loginPage', 'registerPage', 'uploadPage', 'filesPage', 'downloadPage','deletePage'];
            pages.forEach(page => {
                const element = document.getElementById(page);
                if (element) {
                    element.style.display = 'none';
                }
            });

            // Show selected page
            const targetPage = document.getElementById(pageName + 'Page');
            if (targetPage) {
                targetPage.style.display = 'block';
                targetPage.style.animation = 'fadeInUp 0.8s ease-out';
            }
        }

        // Show message
        function showMessage(elementId, message, type) {
            const element = document.getElementById(elementId);
            element.innerHTML = `<div class="message ${type}">${message}</div>`;
            setTimeout(() => {
                element.innerHTML = '';
            }, 5000);
        }

        // Show loading
        function showLoading(elementId, show) {
            const element = document.getElementById(elementId);
            element.style.display = show ? 'block' : 'none';
        }

        // File upload drag and drop
        const fileInput = document.getElementById('fileInput');
        const fileUploadLabel = document.querySelector('.file-upload-label');

        if (fileUploadLabel) {
            fileUploadLabel.addEventListener('dragover', (e) => {
                e.preventDefault();
                fileUploadLabel.style.background = 'rgba(255, 255, 255, 0.3)';
                fileUploadLabel.style.borderColor = 'var(--accent)';
            });

            fileUploadLabel.addEventListener('dragleave', () => {
                fileUploadLabel.style.background = 'rgba(255, 255, 255, 0.1)';
                fileUploadLabel.style.borderColor = 'rgba(255, 255, 255, 0.5)';
            });

            fileUploadLabel.addEventListener('drop', (e) => {
                e.preventDefault();
                const files = e.dataTransfer.files;
                if (files.length > 0) {
                    fileInput.files = files;
                    updateFileLabel(files[0].name);
                }
                fileUploadLabel.style.background = 'rgba(255, 255, 255, 0.1)';
                fileUploadLabel.style.borderColor = 'rgba(255, 255, 255, 0.5)';
            });
        }

        if (fileInput) {
            fileInput.addEventListener('change', (e) => {
                if (e.target.files.length > 0) {
                    updateFileLabel(e.target.files[0].name);
                }
            });
        }

        function updateFileLabel(filename) {
            const textElement = document.querySelector('.file-upload-text');
            const subtextElement = document.querySelector('.file-upload-subtext');
            if (textElement && subtextElement) {
                textElement.textContent = filename;
                subtextElement.textContent = 'Click to change file';
            }
        }

        // Form handlers (you'll need to connect these to your backend)
        document.getElementById('loginForm')?.addEventListener('submit', async (e) => {
            e.preventDefault();
            showLoading('loginLoading', true);
        
        });

        document.getElementById('registerForm')?.addEventListener('submit', async (e) => {
            e.preventDefault();
            showLoading('registerLoading', true);
            

        });

        // document.getElementById('uploadForm')?.addEventListener('submit', async (e) => {
        //     e.preventDefault();
        //     showLoading('uploadLoading', true);
            
        // });

        document.getElementById('downloadForm')?.addEventListener('submit', async (e) => {
            e.preventDefault();
            showLoading('downloadLoading', true);
            
            // Simulate download

        });

        document.getElementById('deleteForm')?.addEventListener('submit', async (e) => {
            e.preventDefault();
            showLoading('deleteit', true);
            
            // Simulate download

        });

        // Navigation click handlers
        document.addEventListener('DOMContentLoaded', () => {
            // Get current page from URL or default to welcome
            const currentPage = window.location.pathname.substring(1) || 'welcome';
            showPage(currentPage);
        });

        // Handle navigation clicks
        document.querySelectorAll('.nav-links a').forEach(link => {
            link.addEventListener('click', (e) => {
                e.preventDefault();
                const page = link.getAttribute('href').substring(1) || 'welcome';
                showPage(page);
                history.pushState(null, '', `/${page}`);
            });
        });

        // Handle browser back/forward
        window.addEventListener('popstate', () => {
            const currentPage = window.location.pathname.substring(1) || 'welcome';
            showPage(currentPage);
        });