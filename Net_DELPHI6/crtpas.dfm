object Form3: TForm3
  Left = 202
  Top = 179
  Width = 764
  Height = 417
  Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099' . . . .'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF88
    8888888888FFF888888888888FFFFF87CCCCCCCCC8FFF872222222228FFFFF87
    CCCCCCCCC8FFF872222222228FFFFF87CCCCCCCCC8FFF872222222228FFFFF87
    CCCCCCCCC8FFF872222222228FFFFF87CCCCCCCCC8FFF872222222228FFFFF87
    CCCCCCCCC8FFF872222222228FFFFF87CCCCCCCCC8FFF872222222228FFFFF87
    CCCCCCCCC8FFF872222222228FFFFF87CCCCCCCCC8FFF872222222228FFFFF87
    7777777778FFF877777777778FFFFF888888888888FFF888888888888FFFFFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    FFFFFFFFFFFF888888888888888FFF888888888888FF8AAAAAAAAAAAA48FFF87
    9999999998FF813333333333348FFF879999999998FF813BBBBBBBBB348FFF87
    9999999998FF813BBDBBBBBB348FFF879999999998FF813BBDBBBBBB348FFF87
    9999999998FF813BBDBBBBBB348FFF879999999998FF813BBDDDDBBB348FFF87
    9999999998FF813BBDBBDBBB348FFF879999999998FF813BBDBBDBBB348FFF87
    9999999998FF813BBDDDDBBB348FFF877777777778FF813BBBBBBBBB348FFF88
    8888888888FF813333333333348FFFFFFFFFFFFFFFFF817777777777778FFFFF
    FFFFFFFFFFFF888888888888888FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 144
    Top = 48
    Width = 143
    Height = 13
    Caption = #1060#1086#1088#1084#1072#1090' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 352
    Top = 32
    Width = 11
    Height = 37
    Caption = '.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 88
    Top = 16
    Width = 158
    Height = 20
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1087#1072#1088#1072#1084#1077#1090#1088' n'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 424
    Top = 8
    Width = 28
    Height = 13
    Caption = 'NULL'
    Visible = False
  end
  object Edit1: TEdit
    Left = 256
    Top = 16
    Width = 73
    Height = 21
    TabOrder = 0
    Text = '0'
    OnChange = Button1Click
  end
  object Button1: TButton
    Left = 336
    Top = 8
    Width = 73
    Height = 33
    Caption = #1057#1086#1079#1076#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 0
    Top = 8
    Width = 81
    Height = 33
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 496
    Top = 8
    Width = 145
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083' . . '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object CheckBox1: TCheckBox
    Left = 0
    Top = 48
    Width = 121
    Height = 17
    Caption = #1090#1086#1083#1100#1082#1086' '#1095#1090#1077#1085#1080#1077
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 4
    OnClick = CheckBox1Click
  end
  object StringGrid1: TStringGrid
    Left = 0
    Top = 70
    Width = 738
    Height = 378
    Align = alBottom
    ColCount = 11
    RowCount = 11
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goTabs, goAlwaysShowEditor]
    TabOrder = 5
    ColWidths = (
      64
      64
      67
      64
      64
      64
      64
      64
      64
      64
      64)
  end
  object SpinEdit1: TSpinEdit
    Left = 296
    Top = 48
    Width = 57
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 20
    MinValue = 0
    ParentFont = False
    TabOrder = 6
    Value = 7
  end
  object SpinEdit2: TSpinEdit
    Left = 368
    Top = 48
    Width = 57
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxValue = 20
    MinValue = 0
    ParentFont = False
    TabOrder = 7
    Value = 2
  end
  object CheckBox2: TCheckBox
    Left = 472
    Top = 48
    Width = 201
    Height = 17
    Caption = #1086#1090#1082#1088#1099#1090#1100' '#1087#1086#1089#1083#1077' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' ('#1079#1072#1087#1080#1089#1080')'
    TabOrder = 8
  end
  object BitBtn1: TBitBtn
    Left = 648
    Top = 8
    Width = 73
    Height = 33
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 9
    OnClick = BitBtn1Click
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333333333333333333333333333FFF33FF333FFF339993370733
      999333777FF37FF377733339993000399933333777F777F77733333399970799
      93333333777F7377733333333999399933333333377737773333333333990993
      3333333333737F73333333333331013333333333333777FF3333333333910193
      333333333337773FF3333333399000993333333337377737FF33333399900099
      93333333773777377FF333399930003999333337773777F777FF339993370733
      9993337773337333777333333333333333333333333333333333333333333333
      3333333333333333333333333333333333333333333333333333}
    NumGlyphs = 2
  end
  object SaveDialog1: TSaveDialog
    Left = 456
    Top = 8
  end
end
