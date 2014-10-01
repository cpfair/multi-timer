var MultiTimer = (function () {

  function start(event) {
    console.log(JSON.stringify(event));
  }

  return {
    start: start
  };

}());

Pebble.addEventListener('ready', MultiTimer.start);