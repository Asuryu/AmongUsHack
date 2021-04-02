const fs = require("fs")
const $ = require("jquery")
const remote = require("electron").remote
var win = remote.getCurrentWindow()

window.onload = function() {

    $("#slider").on("input change", function(){
        $("#opacity").html("Opacity: <span>" + parseFloat($(this).val()).toFixed(2) + "</span>")
        var color = "rgba(17, 17, 17, " + parseFloat($(this).val()).toFixed(2) + ")"
        $("body").css({"background-color": color})
    })

    $(".tp_btn").on("click", function(){
        win.blur()
        console.log($(this).attr("id"))
        fs.readFile('./data.json', 'utf8', (err, jsonString) => {
            var json = JSON.parse(jsonString)
            json.location = parseInt($(this).attr("id"))
            json.state = true
            fs.writeFile('./data.json', JSON.stringify(json), "utf8", function(err)  {

            })
        })
    })
}