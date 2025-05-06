// Constants
const Configuration = {
    brokerUrl : 'broker.emqx.io',
    port : 8083,
    topic : '@lord-nighteyes/led/1/management',
    clientId : 'webClientId_' + Math.random().toString(16).substring(2, 8),
}

const GetOptions = client => ({
    timeout: 5,
    keepAliveInterval: 60,
    onSuccess: () => {
        client.subscribe(Configuration.topic, {
            onSuccess: () => console.log(`Abonné au topic ${Configuration.topic} !`),
            onFailure: error => console.error('Erreur lors de l’abonnement au topic :', error),
        });
    },
    onFailure: error => console.error('Erreur de connexion au broker MQTT :', error)
});


const mqttClient = new Paho.MQTT.Client(Configuration.brokerUrl, Configuration.port, Configuration.clientId);

mqttClient.connect(GetOptions(mqttClient));

mqttClient.onMessageArrived = message => onReceivingMessage({stateValue: message.payloadString});

mqttClient.onConnectionLost = (responseObject) => {
    if (responseObject.errorCode !== 0)
        console.error('Connexion perdue :', responseObject.errorMessage);
};

const sendMessage = ({message, topic}) => {
    const mqttMessage = new Paho.MQTT.Message(message);
    mqttMessage.destinationName = topic;
    mqttClient.send(mqttMessage);
}

const notifyAll = message => sendMessage({message, topic: Configuration.topic});