object Form1: TForm1
  Left = 272
  Top = 125
  Width = 437
  Height = 307
  Caption = 'Net Application for Windows'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object TabbedNotebook1: TTabbedNotebook
    Left = 0
    Top = 0
    Width = 429
    Height = 251
    Align = alClient
    TabFont.Charset = DEFAULT_CHARSET
    TabFont.Color = clBtnText
    TabFont.Height = -11
    TabFont.Name = 'MS Sans Serif'
    TabFont.Style = []
    TabOrder = 0
    object TTabPage
      Left = 4
      Top = 24
      Caption = #1052#1080#1085#1080#1084#1072#1082#1089#1085#1072#1103' '#1079#1072#1076#1072#1095#1072' '#1086' '#1087#1091#1090#1080
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 421
        Height = 223
        Align = alClient
        UseDockManager = False
        FullRepaint = False
        Locked = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        object GroupBox1: TGroupBox
          Left = 16
          Top = 112
          Width = 393
          Height = 105
          Caption = 'Min/Max'
          TabOrder = 0
          object Button2: TButton
            Left = 8
            Top = 16
            Width = 113
            Height = 25
            Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
            TabOrder = 0
            OnClick = Button2Click
          end
          object Edit1: TEdit
            Left = 128
            Top = 16
            Width = 257
            Height = 21
            ReadOnly = True
            TabOrder = 1
          end
          object RadioGroup1: TRadioGroup
            Left = 24
            Top = 56
            Width = 257
            Height = 41
            Caption = #1058#1080#1087' '#1079#1072#1076#1072#1095#1080
            TabOrder = 2
          end
          object RadioButton1: TRadioButton
            Left = 48
            Top = 72
            Width = 57
            Height = 17
            Caption = 'MIN'
            Checked = True
            TabOrder = 3
            TabStop = True
          end
          object RadioButton2: TRadioButton
            Left = 120
            Top = 72
            Width = 57
            Height = 17
            Caption = 'MAX'
            TabOrder = 4
          end
          object Button3: TButton
            Left = 312
            Top = 56
            Width = 73
            Height = 41
            Caption = #1056#1077#1096#1077#1085#1080#1077'...'
            TabOrder = 5
            OnClick = Button3Click
          end
        end
        object GroupBox2: TGroupBox
          Left = 232
          Top = 8
          Width = 177
          Height = 97
          Caption = #1057#1086#1079#1076#1072#1090#1100' '#1090#1072#1073#1083#1080#1094#1091' '#1074#1088#1091#1095#1085#1091#1102' . . .'
          TabOrder = 1
          object Label1: TLabel
            Left = 8
            Top = 20
            Width = 107
            Height = 13
            Caption = #1063#1080#1089#1083#1086' '#1074#1077#1088#1096#1080#1085' '#1075#1088#1072#1092#1072
          end
          object Button4: TButton
            Left = 8
            Top = 56
            Width = 161
            Height = 33
            Caption = #1057#1086#1079#1076#1072#1090#1100' '#1096#1072#1073#1083#1086#1085
            TabOrder = 0
            OnClick = Button4Click
          end
          object SpinEdit1: TSpinEdit
            Left = 128
            Top = 16
            Width = 41
            Height = 22
            MaxValue = 30
            MinValue = 1
            TabOrder = 1
            Value = 1
          end
        end
        object BitBtn1: TBitBtn
          Left = 56
          Top = 40
          Width = 129
          Height = 49
          Cursor = crHandPoint
          Caption = #1057#1086#1079#1076#1072#1090#1100
          TabOrder = 2
          OnClick = BitBtn1Click
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00337000000000
            73333337777777773F333308888888880333337F3F3F3FFF7F33330808089998
            0333337F737377737F333308888888880333337F3F3F3F3F7F33330808080808
            0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
            0333337F737373737F333308888888880333337F3F3F3F3F7F33330808080808
            0333337F737373737F333308888888880333337F3FFFFFFF7F33330800000008
            0333337F7777777F7F333308000E0E080333337F7FFFFF7F7F33330800000008
            0333337F777777737F333308888888880333337F333333337F33330888888888
            03333373FFFFFFFF733333700000000073333337777777773333}
          Layout = blGlyphBottom
          NumGlyphs = 2
        end
        object StaticText1: TStaticText
          Left = 16
          Top = 16
          Width = 199
          Height = 17
          Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099' '#1080#1079' '#1096#1072#1073#1083#1086#1085#1072' (10x10)'
          TabOrder = 3
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 344
    Top = 65528
    object A1: TMenuItem
      Caption = '&'#1060#1072#1081#1083
      object N1: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N1Click
      end
    end
    object N2: TMenuItem
      Caption = '&'#1052#1077#1090#1086#1076#1099
      object N5: TMenuItem
        Caption = '&2. '#1057#1086#1079#1076#1072#1085#1080#1077' '#1058#1072#1073#1083#1080#1094#1099
        OnClick = N5Click
      end
    end
    object N3: TMenuItem
      Caption = '&'#1057#1087#1088#1072#1074#1082#1072
      object N8: TMenuItem
        Caption = '&'#1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077' .....'
        OnClick = N8Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 376
    Top = 65528
  end
  object SaveDialog1: TSaveDialog
    Left = 312
    Top = 65528
  end
end
