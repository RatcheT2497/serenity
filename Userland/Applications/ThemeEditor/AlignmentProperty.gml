@ThemeEditor::AlignmentProperty {
    layout: @GUI::HorizontalBoxLayout {
        spacing: 4
    }
    preferred_height: "fit"

    @GUI::Label {
        name: "name"
        text: "Some alignment"
        text_alignment: "CenterLeft"
        fixed_width: 200
    }

    @GUI::ComboBox {
        name: "combo_box"
        only_allow_values_from_model: true
    }
}
