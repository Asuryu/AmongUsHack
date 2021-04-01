const fs = require("node:fs")

window.onload = function() {

    $("#slider").on("input change", function(){
        $("#opacity").html("Opacity: <span>" + parseFloat($(this).val()).toFixed(2) + "</span>")
        var color = "rgba(17, 17, 17, " + parseFloat($(this).val()).toFixed(2) + ")"
        $("body").css({"background-color": color})
    })

    $(".tp_btn").on("click", function(){
        console.log($(this).attr("id"))

    })
}