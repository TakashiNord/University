object Form5: TForm5
  Left = 271
  Top = 240
  Width = 696
  Height = 480
  Caption = #1057#1086#1079#1076#1072#1085#1080#1077' '#1090#1072#1073#1083#1080#1094#1099' '#1087#1091#1090#1077#1081' '#1043#1088#1072#1092#1072' . . .'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 17
    Top = 0
    Width = 433
    Height = 33
    Style = bsRaised
  end
  object Label1: TLabel
    Left = 8
    Top = 40
    Width = 176
    Height = 16
    Caption = #1060#1086#1088#1084#1072#1090' '#1087#1088#1077#1076#1089#1090#1072#1074#1083#1077#1085#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 248
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
  object BitBtn2: TBitBtn
    Left = 456
    Top = 0
    Width = 97
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100'....'
    TabOrder = 0
    OnClick = BitBtn2Click
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      33333333333FFFFFFFFF333333000000000033333377777777773333330FFFFF
      FFF03333337F333333373333330FFFFFFFF03333337F3FF3FFF73333330F00F0
      00F03333F37F773777373330330FFFFFFFF03337FF7F3F3FF3F73339030F0800
      F0F033377F7F737737373339900FFFFFFFF03FF7777F3FF3FFF70999990F00F0
      00007777777F7737777709999990FFF0FF0377777777FF37F3730999999908F0
      F033777777777337F73309999990FFF0033377777777FFF77333099999000000
      3333777777777777333333399033333333333337773333333333333903333333
      3333333773333333333333303333333333333337333333333333}
    NumGlyphs = 2
  end
  object BitBtn1: TBitBtn
    Left = 560
    Top = 0
    Width = 89
    Height = 33
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 1
    OnClick = BitBtn1Click
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333FFFFF3333333333999993333333333F77777FFF333333999999999
      33333337777FF377FF3333993370739993333377FF373F377FF3399993000339
      993337777F777F3377F3393999707333993337F77737333337FF993399933333
      399377F3777FF333377F993339903333399377F33737FF33377F993333707333
      399377F333377FF3377F993333101933399377F333777FFF377F993333000993
      399377FF3377737FF7733993330009993933373FF3777377F7F3399933000399
      99333773FF777F777733339993707339933333773FF7FFF77333333999999999
      3333333777333777333333333999993333333333377777333333}
    NumGlyphs = 2
  end
  object Edit1: TEdit
    Left = 32
    Top = 8
    Width = 401
    Height = 21
    BevelInner = bvSpace
    BevelKind = bkFlat
    ReadOnly = True
    TabOrder = 2
    Text = #1060#1072#1081#1083': '
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 72
    Width = 673
    Height = 369
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goTabs, goAlwaysShowEditor]
    TabOrder = 3
    ColWidths = (
      64
      64
      64
      64
      64)
  end
  object SpinEdit1: TSpinEdit
    Left = 184
    Top = 40
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
    TabOrder = 4
    Value = 7
  end
  object SpinEdit2: TSpinEdit
    Left = 264
    Top = 40
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
    TabOrder = 5
    Value = 2
  end
  object SaveDialog1: TSaveDialog
    Left = 656
  end
end
