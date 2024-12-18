#pragma once

const char* wifi_controls_html = R"(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Flappy Buuurd</title>
    <style>
        html {
            height: 100%;
        }
        body {
            margin: 0;
            padding: 2rem;
            box-sizing: border-box;
            width: 100vw;
            height: 100%;
            display: flex;
            flex-direction: column;
            align-items: center;
            font-family: sans-serif;
        }
        h1 {
            margin: 0.5rem;
        }
        #flap-button {
            width: max(80vw, 100px);
            flex-grow: 1;
        }

    </style>
</head>

<body>
    <h1>Flappy Buuurd</h1>
    <button id="flap-button">Fliiiiegen</button>
    <script>
        window.addEventListener("load", () => {
            const flapButton = document.getElementById("flap-button");
            flapButton.addEventListener("click", async () => {
                flapButton.setAttribute("disabled", "disabled");
                try {
                    await fetch("/flap");
                } catch {
                    // Ignore errors
                }
                flapButton.removeAttribute("disabled");
            });
        });
    </script>
</body>

</html>)";