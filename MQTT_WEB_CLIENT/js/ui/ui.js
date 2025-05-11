const medias = [
    {
      off: { type: "image", src: "medias/pimpi-off.png" },
      on:  { type: "image", src: "medias/pimpi-on.jpeg" }
    },
    //{
      //off: { type: "image", src: "medias/souley-on.jpeg" },
      //on:  { type: "video", src: "medias/pere-bou-xar.webm" }
    //}
];

const switchContainer = document.getElementById("switchContainer");
const mediaContainer = document.getElementById("media-container");
const switchToggle = document.getElementById("switchToggle");

let isOn = false;
let mediaIndex = 0;

const onReceivingMessage = ({ stateValue }) => {
    const shouldBeOn = stateValue === "1";
    if (shouldBeOn !== isOn) toggleSwitch();
};

const clearMediaContainer = () => mediaContainer.innerHTML = "";

const renderMedia = (media) => {
    clearMediaContainer();

    if (media.type === "image") {
        const img = document.createElement("img");
        img.src = media.src;
        img.alt = "media";
        //img.addEventListener("load", () => console.log("Image chargée"));
        //img.addEventListener("error", () => console.error("Erreur chargement image"));
        mediaContainer.appendChild(img);

    } else if (media.type === "video") {
        const video = document.createElement("video");
        video.src = media.src;
        video.autoplay = true;
        //video.controls = true;
        video.addEventListener("ended", toggleSwitch);
        video.addEventListener("error", () => console.error("Erreur chargement vidéo"));
        mediaContainer.appendChild(video);
    }
};

const toggleSwitch = () => {
    isOn = !isOn;

    const mediaState = medias[mediaIndex % medias.length];
    const currentMedia = isOn ? mediaState.on : mediaState.off;

    renderMedia(currentMedia);

    switchContainer.classList.toggle("on", isOn);
    switchContainer.classList.toggle("off", !isOn);
    document.body.style.backgroundColor = isOn ? "white" : "black";

    notifyAll(isOn ? "1" : "0");

    if (isOn) mediaIndex++;
};

document.addEventListener("keydown", (e) => {
    if (e.code === "Space") {
        e.preventDefault();
        toggleSwitch();
    }
});

switchToggle.addEventListener("click", toggleSwitch);