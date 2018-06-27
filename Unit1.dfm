object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = 'Form1'
  ClientHeight = 357
  ClientWidth = 415
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblPath: TLabel
    Left = 271
    Top = 84
    Width = 86
    Height = 13
    Caption = #1055#1091#1090#1100' '#1076#1086' '#1088#1072#1079#1076#1077#1083#1072
  end
  object lblBegin: TLabel
    Left = 271
    Top = 210
    Width = 101
    Height = 13
    Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1081' '#1082#1083#1072#1089#1090#1077#1088
    Enabled = False
  end
  object lblEnd: TLabel
    Left = 271
    Top = 256
    Width = 95
    Height = 13
    Caption = #1050#1086#1085#1077#1095#1085#1099#1081' '#1082#1083#1072#1089#1090#1077#1088
    Enabled = False
  end
  object lblFsType: TLabel
    Left = 271
    Top = 130
    Width = 116
    Height = 13
    Caption = #1058#1080#1087' '#1092#1072#1081#1083#1086#1074#1086#1081' '#1089#1080#1089#1090#1077#1084#1099
  end
  object Label1: TLabel
    Left = 283
    Top = 302
    Width = 89
    Height = 13
    Caption = #1058#1077#1082#1091#1097#1080#1081' '#1082#1083#1072#1089#1090#1077#1088
  end
  object StatusLabel: TLabel
    Left = 312
    Top = 321
    Width = 45
    Height = 13
    Caption = '0'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 257
    Height = 341
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages, toFullVertGridLines]
    TreeOptions.SelectionOptions = [toFullRowSelect]
    OnGetText = VirtualStringTree1GetText
    Columns = <
      item
        Position = 0
        Width = 90
        WideText = #1050#1083#1072#1089#1090#1077#1088
      end
      item
        Position = 1
        Width = 68
        WideText = #1057#1080#1075#1085#1072#1090#1091#1088#1072
      end
      item
        Position = 2
        Width = 95
        WideText = #1056#1072#1089#1096#1080#1088#1077#1085#1080#1077
      end>
  end
  object btnSearch: TButton
    Left = 271
    Top = 8
    Width = 128
    Height = 30
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 1
    OnClick = btnSearchClick
  end
  object btnStop: TButton
    Left = 271
    Top = 48
    Width = 129
    Height = 30
    Caption = #1057#1090#1086#1087
    TabOrder = 2
    OnClick = btnStopClick
  end
  object editPath: TEdit
    Left = 271
    Top = 103
    Width = 128
    Height = 21
    TabOrder = 3
    Text = '\\.\E:'
  end
  object editBegin: TEdit
    Left = 271
    Top = 229
    Width = 129
    Height = 21
    Enabled = False
    NumbersOnly = True
    TabOrder = 4
    Text = '0'
  end
  object editEnd: TEdit
    Left = 271
    Top = 275
    Width = 129
    Height = 21
    Enabled = False
    NumbersOnly = True
    TabOrder = 5
    Text = '10000'
  end
  object chbRange: TCheckBox
    Left = 271
    Top = 176
    Width = 129
    Height = 28
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1091
    TabOrder = 6
    OnClick = chbRangeClick
  end
  object cbFsType: TComboBox
    Left = 271
    Top = 149
    Width = 128
    Height = 21
    TabOrder = 7
    Items.Strings = (
      'NTFS'
      'FAT32')
  end
end
