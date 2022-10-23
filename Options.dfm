object OptionsForm: TOptionsForm
  Left = 297
  Top = 180
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 350
  ClientWidth = 346
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Info: TLabel
    Left = 8
    Top = 296
    Width = 209
    Height = 49
    AutoSize = False
    Caption = 'Info->Caption'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object PageControl: TPageControl
    Left = 8
    Top = 8
    Width = 329
    Height = 281
    ActivePage = TabSheetGeneral
    Align = alCustom
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabIndex = 0
    TabOrder = 0
    object TabSheetGeneral: TTabSheet
      Caption = #1054#1073#1097#1080#1077
      object GroupBoxRandom: TGroupBox
        Left = 8
        Top = 136
        Width = 305
        Height = 65
        Caption = #1044#1080#1072#1087#1072#1079#1086#1085' '#1089#1083#1091#1095#1072#1081#1085#1099#1093' '#1095#1080#1089#1077#1083
        TabOrder = 2
        object RandomFrom: TAdvSpinEdit
          Left = 32
          Top = 24
          Width = 57
          Height = 26
          AllowNullValue = False
          Value = 2
          FloatValue = 2
          HexValue = 0
          Enabled = True
          IncrementFloat = 0.1
          IncrementFloatPage = 1
          LabelCaption = #1054#1090
          LabelPosition = lpLeftCenter
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -15
          LabelFont.Name = 'MS Sans Serif'
          LabelFont.Style = []
          MaxValue = 9
          TabOrder = 0
          Visible = True
          Version = '1.4.4.4'
          OnChange = RandomFromChange
        end
        object RandomTo: TAdvSpinEdit
          Left = 128
          Top = 24
          Width = 57
          Height = 26
          AllowNullValue = False
          Value = 10
          FloatValue = 10
          HexValue = 0
          Enabled = True
          IncrementFloat = 0.1
          IncrementFloatPage = 1
          LabelCaption = #1044#1086
          LabelPosition = lpLeftCenter
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -15
          LabelFont.Name = 'MS Sans Serif'
          LabelFont.Style = []
          MaxValue = 32000
          MinValue = 3
          TabOrder = 1
          Visible = True
          Version = '1.4.4.4'
          OnChange = RandomToChange
        end
      end
      object GroupBoxReport: TGroupBox
        Left = 8
        Top = 12
        Width = 305
        Height = 81
        Caption = #1059#1089#1082#1086#1088#1077#1085#1080#1077' '#1088#1072#1073#1086#1090#1099' '#1072#1083#1075#1086#1088#1080#1090#1084#1086#1074
        TabOrder = 0
        object NoOut: TCheckBox
          Left = 8
          Top = 24
          Width = 216
          Height = 17
          Caption = #1054#1090#1082#1083#1102#1095#1080#1090#1100' '#1074#1099#1074#1086#1076' '#1076#1072#1085#1085#1099#1093' '
          TabOrder = 0
          OnClick = NoOutClick
        end
        object Debug: TCheckBox
          Left = 8
          Top = 51
          Width = 216
          Height = 17
          Caption = #1042#1099#1074#1086#1076#1080#1090#1100' '#1087#1086#1076#1088#1086#1073#1085#1099#1081' '#1086#1090#1095#1077#1090
          TabOrder = 1
        end
      end
      object OpenCheck: TCheckBox
        Left = 8
        Top = 107
        Width = 305
        Height = 17
        BiDiMode = bdLeftToRight
        Caption = #1055#1088#1086#1074#1077#1088#1082#1072' '#1082#1086#1088#1088#1077#1082#1090#1085#1086#1089#1090#1080' '#1074#1093#1086#1076#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
        Checked = True
        ParentBiDiMode = False
        State = cbChecked
        TabOrder = 1
      end
    end
    object TabSheetMMVG: TTabSheet
      Caption = #1052#1086#1076#1080#1092#1080#1082#1072#1094#1080#1103' '#1052#1042#1043
      ImageIndex = 1
      object MVGModify: TRadioGroup
        Left = 8
        Top = 40
        Width = 305
        Height = 169
        Caption = #1052#1077#1090#1086#1076' '#1088#1072#1089#1095#1077#1090#1072' '#1082#1088#1080#1090#1077#1088#1080#1103' '#1086#1087#1090#1080#1084#1072#1083#1100#1085#1086#1089#1090#1080
        ItemIndex = 0
        Items.Strings = (
          #1057#1090#1072#1085#1076#1072#1088#1090#1085#1099#1081' '#1088#1072#1089#1095#1077#1090
          #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1081' '#1085#1072' '#1087#1086#1089#1083#1077#1076#1085#1077#1084' '#1089#1090#1072#1085#1082#1077
          #1050#1072#1082' '#1091' '#1055#1077#1090#1088#1086#1074#1072'-'#1057#1086#1082#1086#1083#1080#1094#1080#1085#1072
          #1052#1080#1085#1080#1084#1080#1079#1072#1094#1080#1103' '#1087#1088#1077#1076#1087#1086#1083#1086#1075#1072#1077#1084#1086#1075#1086' '#1087#1088#1086#1089#1090#1086#1103
          #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1087#1088#1086#1080#1079#1074#1086#1076#1089#1090#1074' '#1094#1080#1082#1083#1072)
        TabOrder = 1
      end
      object MvgIdleAll: TCheckBox
        Left = 8
        Top = 12
        Width = 305
        Height = 17
        Caption = #1059#1073#1088#1072#1090#1100' '#1087#1088#1086#1089#1090#1086#1080'  '#1086#1073#1086#1088#1091#1076#1086#1074#1072#1085#1080#1103
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
    end
    object TabSheetGant: TTabSheet
      Caption = #1044#1080#1072#1075#1088#1072#1084#1084#1072' '#1043#1072#1085#1090#1072
      ImageIndex = 2
      object LabelBR: TLabel
        Left = 8
        Top = 136
        Width = 57
        Height = 16
        Caption = #1071#1088#1082#1086#1089#1090#1100':'
      end
      object LabelBI: TLabel
        Left = 8
        Top = 200
        Width = 187
        Height = 16
        Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1084#1077#1078#1076#1091' '#1073#1083#1086#1082#1072#1084#1080' :'
      end
      object ColorOptions: TRadioGroup
        Left = 8
        Top = 40
        Width = 305
        Height = 81
        Caption = #1047#1072#1082#1088#1072#1096#1080#1074#1072#1085#1080#1077' '#1073#1083#1086#1082#1086#1074
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 1
        Items.Strings = (
          #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1086#1076#1080#1085' '#1094#1074#1077#1090
          #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1089#1083#1091#1095#1072#1081#1085#1099#1077' '#1094#1074#1077#1090#1072)
        ParentFont = False
        TabOrder = 1
        OnClick = ColorOptionsClick
      end
      object WorkTimeOut: TCheckBox
        Left = 8
        Top = 12
        Width = 305
        Height = 17
        Caption = #1042#1099#1074#1086#1076#1080#1090#1100' '#1076#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1080' '#1086#1073#1088#1072#1073#1086#1090#1082#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object HeightScaling: TCheckBox
        Left = 8
        Top = 168
        Width = 249
        Height = 17
        Caption = #1052#1072#1089#1096#1090#1072#1073#1080#1088#1086#1074#1072#1090#1100' '#1074#1099#1089#1086#1090#1091
        TabOrder = 4
        OnClick = HeightScalingClick
      end
      object Contrast: TCheckBox
        Left = 142
        Top = 136
        Width = 177
        Height = 17
        Caption = #1059#1089#1080#1083#1080#1090#1100' '#1082#1086#1085#1090#1088#1072#1089#1090#1085#1086#1089#1090#1100
        TabOrder = 3
      end
      object SpinBI: TAdvSpinEdit
        Left = 200
        Top = 196
        Width = 65
        Height = 26
        AllowNullValue = False
        Value = 10
        FloatValue = 10
        HexValue = 0
        Enabled = True
        IncrementFloat = 0.1
        IncrementFloatPage = 1
        LabelFont.Charset = DEFAULT_CHARSET
        LabelFont.Color = clWindowText
        LabelFont.Height = -11
        LabelFont.Name = 'MS Sans Serif'
        LabelFont.Style = []
        MaxValue = 30
        TabOrder = 5
        Visible = True
        Version = '1.4.4.4'
      end
      object SpinBrightness: TAdvSpinEdit
        Left = 72
        Top = 132
        Width = 57
        Height = 26
        AllowNullValue = False
        Value = 10
        FloatValue = 10
        HexValue = 0
        Enabled = True
        IncrementFloat = 0.1
        IncrementFloatPage = 1
        LabelFont.Charset = DEFAULT_CHARSET
        LabelFont.Color = clWindowText
        LabelFont.Height = -11
        LabelFont.Name = 'MS Sans Serif'
        LabelFont.Style = []
        MaxValue = 250
        TabOrder = 2
        Visible = True
        Version = '1.4.4.4'
        OnChange = SpinBrightnessChange
      end
    end
    object TabSheetOptim: TTabSheet
      Caption = #1050#1088#1080#1090#1077#1088#1080#1080' '#1086#1087#1090#1080#1084#1080#1079#1072#1094#1080#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImageIndex = 3
      ParentFont = False
      object Crit4: TCheckBox
        Left = 8
        Top = 112
        Width = 281
        Height = 17
        Caption = #1052#1080#1085'. '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1077#1088#1077#1085#1072#1083#1072#1076#1086#1082
        TabOrder = 0
        OnClick = Crit2Click
      end
      object Crit3: TCheckBox
        Left = 8
        Top = 80
        Width = 305
        Height = 17
        Caption = #1052#1080#1085'. '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1084#1086#1075#1086' '#1087#1072#1088#1082#1072' '#1089#1090#1072#1085#1082#1086#1074
        TabOrder = 1
        OnClick = Crit2Click
      end
      object Crit1: TCheckBox
        Left = 8
        Top = 16
        Width = 305
        Height = 17
        Caption = #1052#1080#1085'. '#1076#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1080' '#1087#1088#1086#1080#1079#1074#1086#1076#1089#1090#1074'. '#1094#1080#1082#1083#1072
        Checked = True
        State = cbChecked
        TabOrder = 2
        OnClick = Crit1Click
      end
      object Crit2: TCheckBox
        Left = 8
        Top = 48
        Width = 257
        Height = 17
        Caption = #1052#1080#1085'. '#1074#1088#1077#1084#1103' '#1087#1088#1086#1089#1090#1086#1077#1074' '#1086#1073#1086#1088#1091#1076#1086#1074#1072#1085#1080#1103
        TabOrder = 3
        OnClick = Crit2Click
      end
      object Crit5: TCheckBox
        Left = 8
        Top = 144
        Width = 281
        Height = 17
        Caption = #1052#1072#1082#1089'. '#1079#1072#1075#1088#1091#1079#1082#1080' '#1086#1073#1086#1088#1091#1076#1086#1074#1072#1085#1080#1103
        TabOrder = 4
        OnClick = Crit2Click
      end
      object Crit6: TCheckBox
        Left = 8
        Top = 176
        Width = 313
        Height = 17
        Caption = #1052#1080#1085'. '#1082#1086#1083'-'#1074#1072' '#1085#1077#1079#1072#1074#1077#1088#1096#1077#1085#1085#1099#1093' '#1086#1087#1077#1088#1072#1094#1080#1081
        TabOrder = 5
        OnClick = Crit2Click
      end
    end
  end
  object BitBtnOK: TBitBtn
    Left = 232
    Top = 296
    Width = 48
    Height = 48
    Hint = #1055#1088#1080#1085#1103#1090#1100
    ModalResult = 1
    TabOrder = 1
    OnClick = BitBtnOKClick
    Glyph.Data = {
      36180000424D3618000000000000360000002800000040000000200000000100
      18000000000000180000120B0000120B00000000000000000000FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00DFDF
      DFE7E7E7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00E6E6
      E6ECECECFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00BFC3C12E9D
      5E469869DBDBDBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D0D0D0ABAB
      ABA6A6A6E3E3E3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00B1BAB51EA35535D7
      7F2ED37936985DCFD1CFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00C7C7C7B0B0B0E9E9
      E9E5E5E5A5A5A5DBDBDBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00A1AFA612A44D41D684ABF5
      CEBAF7D742D582289650C1C5C2FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00BDBDBDB1B1B1E9E9E9FEFE
      FEFEFEFEE7E7E7A2A2A2D1D1D1FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF008FA4970AA54642D28289F0B775F1
      AD96F9C7C9FAE44ED4861C9A49B3BAB6FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00B3B3B3B1B1B1E3E3E3FEFEFEFEFE
      FEFDFDFDFCFCFCE6E6E6A3A3A3C8C8C8FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF009FABA3089F3F2EC77076ECAA57EA936FEF
      A787F5BCA7FDD6CAF9E433C76F209247C3C6C4FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00BBBBBBACACACD8D8D8FEFEFEFDFDFDFCFC
      FCFBFBFBFAFAFAF9F9F9CDCDCD9B9B9BD2D2D2FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF0097A69D10994228C36A50E38D37E3784CE78A66ED
      9F7BF2B18BF6BF9FFBCEAAF3CD36C46E249047B9BFBBFFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00B7B7B7A6A6A6D3D3D3F8F8F8F2F2F2FCFCFCFBFB
      FBFAFAFAF9F9F9F8F8F8F7F7F7C9C9C99A9A9ACCCCCCFFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00839B8B06983922C2662FDD7410DA5828DE6B41E48056E9
      9167EDA175F1AC7AF1B181F5B790EFBB37C36E168F3CA7B1AAFFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00ACACACA6A6A6D1D1D1EEEEEEE7E7E7EAEAEAF4F4F4F9F9
      F9F8F8F8F7F7F7F6F6F6F5F5F5F4F4F4CCCCCC9C9C9CC0C0C0FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF0072937C0097321BBF5F1ED76500D24305D54D1BDB6030E07142E5
      8151E88E5CEB9761EB9B5FEB9A5CEC976FEBA436C16C0E8F3697A69BFFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00A4A4A4A4A4A4CDCDCDE5E5E5DDDDDDE1E1E1E8E8E8EBEBEBF3F3
      F3F6F6F6F5F5F5F5F5F5F4F4F4F4F4F4F4F4F4D1D1D19C9C9CB6B6B6FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00608A6C01963012BC5811D05700CA3D00CE4400D34809D7511CDC602CDF
      6E39E27A42E48147E58446E5843FE47F35E37649E48830BE66068C2E859B8BFF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF009C9C9CA3A3A3CACACADDDDDDD5D5D5D9D9D9DEDEDEE3E3E3E8E8E8ECEC
      ECEEEEEEEEEEEEF4F4F4F4F4F4F0F0F0F3F3F3F8F8F8CECECE999999ACACACFF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      6E8D7700912908B14C0ACC5100C23700C73E00CC4200CF4500D34708D75016DA
      5C22DD662ADE6D2EE0702FE0712ADE6D21DC6511DA5830DF761FB15404872595
      A298FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      9F9F9F9E9E9EBEBEBED8D8D8CCCCCCD2D2D2D7D7D7DADADADEDEDEE4E4E4E8E8
      E8EBEBEBEBEBEBECECECECECECEBEBEBEAEAEAE7E7E7EFEFEFBFBFBF959595B3
      B3B3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF006A8B72
      00882400AB4102C34600BC3300C03800C43A00C83C00CC4304D1480AD54F18D9
      5B20DB6324DC6624DC661EDC6214D95A09D75100D44700D3441CD56317AD4D0C
      82298D9D91FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF009D9D9D
      979797B7B7B7CFCFCFC6C6C6CACACACFCFCFD3D3D3D8D8D8DDDDDDE1E1E1E7E7
      E7E9E9E9EAEAEAEBEBEBEAEAEAE6E6E6E4E4E4DFDFDFDEDEDEE3E3E3BABABA90
      9090AFAFAFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF0093A697008821
      00A63900BA3A00B42B00B72D01BD3615C6492ACF5C3AD56B46DA754DDD7C34DB
      6C3EDE744FE1814AE07D49E07C41DE7734DB6B22D75E0BCF4B00CB3C0DCE530F
      AB46047F207A917FFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00B5B5B5969696
      B2B2B2C4C4C4BEBEBEC1C1C1C8C8C8D2D2D2DDDDDDE5E5E5EBEBEBEFEFEFEBEB
      EBEFEFEFF4F4F4F2F2F2F2F2F2EFEFEFEAEAEAE5E5E5DBDBDBD6D6D6DADADAB8
      B8B88E8E8EA4A4A4FFFF00FFFF00FFFF00FFFF00FFFF00FFFF007A9B8100A733
      00B12F00AB2103B22D27C04E4BCE6E5BD57E5FD88260DA8562DC8837D86907CB
      440DD14B48DE7A62E18C5CE0875CDF875EDF885FDE8758DB803ED46C14C84804
      C74606A83E017D1968876DFFFF00FFFF00FFFF00FFFF00FFFF00ABABABB2B2B2
      BBBBBBB5B5B5BDBDBDCDCDCDDFDFDFE8E8E8ECECECEEEEEEF0F0F0E8E8E8D6D6
      D6DDDDDDF0F0F0F6F6F6F4F4F4F3F3F3F3F3F3F2F2F2EEEEEEE4E4E4D4D4D4D2
      D2D2B5B5B58C8C8C9B9B9BFFFF00FFFF00FFFF00FFFF00FFFF0081A88A00B227
      00A51F1FB43E59CB7370D4896FD6896CD7896DD98C70DB8E36D46514CA49BBCE
      C0ADC6B414CC4C4DDC7B72E1956CE0906CDF906CDE8F6DDD8F71DD916BDA8B2D
      C85700C03A00A436007A15547C59FFFF00FFFF00FFFF00FFFF00B4B4B4BCBCBC
      B0B0B0BFBFBFDCDCDCE9E9E9EBEBEBECECECEFEFEFF1F1F1E2E2E2D3D3D3D5D5
      D5CFCFCFD7D7D7EEEEEEF8F8F8F6F6F6F5F5F5F4F4F4F3F3F3F4F4F4F0F0F0D5
      D5D5CBCBCBB0B0B08A8A8A919191FFFF00FFFF00FFFF00FFFF00D3D8D316A329
      24B44080D39180D5937BD6907BD7917DDA9482DC9A39D0630EC03CC7D4CAFFFF
      00FFFF00B5CDBB08CE4158DC8084E2A17BE0997BDF987BDE977BDD977EDC977F
      DB9738C55A00B62F009C2F00740E4C7750FFFF00FFFF00FFFF00DFDFDFAEAEAE
      C0C0C0EBEBEBECECECEDEDEDEEEEEEF2F2F2F4F4F4DFDFDFC9C9C9DBDBDBFFFF
      00FFFF00D4D4D4D9D9D9EFEFEFFCFCFCF8F8F8F7F7F7F6F6F6F5F5F5F4F4F4F3
      F3F3D2D2D2C0C0C0A9A9A98585858C8C8CFFFF00FFFF00FFFF00FFFF00BDCCBF
      1FAB3658C96E8FD99F89D89A8ADA9D8EDCA148CF6A12BC3DB1C6B6FFFF00FFFF
      00FFFF00FFFF00A1C3AA13C74665DD8790E3A888E1A187DF9F87DE9F87DD9E89
      DD9F87DA9C3CC15900AF2C008E21006C085C7C5DFFFF00FFFF00FFFF00D4D4D4
      B5B5B5DADADAF4F4F4F1F1F1F3F3F3F6F6F6DFDFDFC5C5C5CFCFCFFFFF00FFFF
      00FFFF00FFFF00CBCBCBD1D1D1F2F2F2F8F8F8F4F4F4F4F4F4F4F4F4F7F7F7F7
      F7F7F3F3F3CFCFCFBABABA9B9B9B7E7E7E929292FFFF00FFFF00FFFF00FFFF00
      C9D2CA23A23754C86AA2DFAF9DDEAC44C9621CB33DC3D2C6FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00B5CABA1BC14765DB85A1E5B49AE2AC98E1AB98E0AA98
      DFA99ADFAA9CDEAA52C36800A7230088180068044C724CFFFF00FFFF00FFFF00
      DADADAADADADD8D8D8FDFDFDFCFCFCD8D8D8BDBDBDD9D9D9FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00D2D2D2CBCBCBEFEFEFF4F4F4F4F4F4F5F5F5F5F5F5F6
      F6F6F7F7F7F8F8F8D3D3D3B1B1B19595957A7A7A888888FFFF00FFFF00FFFF00
      FFFF00D9DDD932A3434FC6653FC25A2CAB42D3D9D4FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00C7D4C922B44462D67FB1E7BEABE5B8A8E4B6A8
      E2B5A8E1B4AAE1B5B0E2B963C574019F1B008310006A028B9D8BFFFF00FFFF00
      FFFF00E3E3E3ADADADD6D6D6D0D0D0B5B5B5E0E0E0FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00DBDBDBBDBDBDE9E9E9F5F5F5F5F5F5F6F6F6F7
      F7F7F8F8F8F9F9F9FAFAFAD7D7D7AAAAAA9191917C7C7CAEAEAEFFFF00FFFF00
      FFFF00FFFF00E7E9E742A44F3EAD4FE3E6E3FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00D7DCD730AF4A5BD075BEEAC8BCE8C5B8
      E7C2B9E6C2B9E5C1BAE6C2C2E7C77AC985099A1A00870D7C957DFFFF00FFFF00
      FFFF00FFFF00EDEDEDAEAEAEB6B6B6EBEBEBFFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00E2E2E2B8B8B8E2E2E2F6F6F6F7F7F7F8
      F8F8F9F9F9FAFAFAFBFBFBFCFCFCDFDFDFA5A5A5949494A7A7A7FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00E5E8E52AAB3E5ACC71D2EFD8CB
      ECD1C8EACEC8EACDC8E9CDC9E9CDD6EEDA92D199069B117EA081FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00ECECECB5B5B5DDDDDDF8F8F8F9
      F9F9FAFAFAFBFBFBFCFCFCFDFDFDFDFDFDEBEBEBA6A6A6AFAFAFFFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D5DBD52AA43C6FD080DE
      F3E2DAF1DED5EED8D5EED8DAF0DDDCF0DF6CC2731A931EC7D0C7FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00E2E2E2AEAEAEE4E4E4FA
      FAFAFBFBFBFCFCFCFDFDFDFDFDFDFEFEFED5D5D59F9F9FD8D8D8FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00E1E4E13AA14565
      C973EAF6ECECF7EDEDF8EEE6F4E85BBA61268D26CDD3CDFFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00E9E9E9ABABABDB
      DBDBFCFCFCFDFDFDFDFDFDFEFEFECBCBCB9A9A9ADBDBDBFFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00EDEEED4C
      9A4D56BF61F6FCF7F1F9F14CB453369136DDE0DDFFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00F2F2F2A6
      A6A6CECECEFDFDFDFEFEFEC2C2C29E9E9EE6E6E6FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF005E9D5E49B45041AC48489048EBECEBFFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00A9A9A9C2C2C2BABABA9E9E9EF0F0F0FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF005A975A469846F1F1F1FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00A4A4A4A4A4A4F4F4F4FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00}
    NumGlyphs = 2
  end
  object BitBtnCancel: TBitBtn
    Left = 288
    Top = 296
    Width = 48
    Height = 48
    Hint = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    TabOrder = 2
    OnClick = BitBtnCancelClick
    Glyph.Data = {
      360C0000424D360C000000000000360000002800000020000000200000000100
      180000000000000C0000120B0000120B00000000000000000000FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00CFCFCFD1D1D1FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00CF
      CFCFD3D3D3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00C6C3EA6056C87671AF999999B7B7B7FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00DEDCF26057C266
      5FB29E9DA0C3C3C3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00BDB9E83527CE3527D03325CF6962B1999999B5B5
      B5FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00DCDAF14033CB3528D133
      25CF544ABD9E9DA0C3C3C3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00BDB9E83527CE3629D2423ADF443BDA4639D36963B29999
      99B7B7B7FFFF00FFFF00FFFF00FFFF00FFFF00DAD8F14A3ECE4438D5473FE33E
      34DA3325CF544ABD9E9DA0C3C3C3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00BDB9E73526CB3426CF3F34DB433AE0473FE45349DD594DD56A63
      B1999999B7B7B7FFFF00FFFF00FFFF00DAD8F15245CD5A50D84D45E74942E645
      3DE23C30D73324CC544ABB9E9DA0C3C3C3FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00BDB9E73828C83324CB3B2FD63F34DB4339DF463EE34A43E7625AE16C61
      D86A63B0999999B7B7B7FFFF00D9D6F05A4DCE7166DD514CE94C45E94841E545
      3CE14137DE392DD33323C95449B89E9DA0C3C3C3FFFF00FFFF00FFFF00FFFF00
      BDB9E7483ACB4A3DCF4032D33A2ED63E33DA4138DE453DE24941E64C46E9716A
      E57F74DB6B64B0999999A19EB76257CF867EE25550EC4D47EA4A43E7473FE443
      3BE04036DD3D32D93729D03322C65449B79E9DA0C3C3C3FFFF00FFFF00C5C0EE
      5042CB584CD15348D54F44D7493ED83E33D94036DD433BE0473FE44A43E74D47
      EA7F79E88F86DE635AB4695ECE9B93E65853EB4E48EB4B45E84841E5453DE242
      39DF3F34DB3B30D8382CD43325CB3321C35449B59E9DA0D3D3D3FFFF00584ACD
      665BD36156D95B50D8574BD85449D95146DB443ADC4138DE443CE14740E44A43
      E74C46E9837DEBB4B0EC9E98EA5953EA4D47EA4B44E84841E5463EE3433AE040
      36DD3D32D93A2ED6362AD33325CF3324CA3321C1665EACCFCFCFD9D5F36355CE
      6F63D7695FDB6359DA5D52D8594ED9574DDB544ADC4B41DD4238DE443CE1473F
      E44941E54A43E74B44E84B44E84A44E74942E64840E5463DE2433AE04137DD3E
      33DA3B2FD7382BD43527D13325CF3224CC3221C06054B9FFFF00FFFF008C82DA
      6B5ECF7065D76B60DC655ADA5F54D95C52DB594FDC564DDE5148DE433ADE433A
      E0453DE2463EE3473FE4473FE4473FE3463DE2443CE14239DF4037DD3E33DA3B
      30D8392CD53629D23325CF3224CC3220BF402EBBDEDBEFFFFF00FFFF00FFFF00
      897ED76D60CE7368D76D63DC675DDB6258DA5F55DB5B52DD594FDD534ADE4239
      DC4138DE4239DF433AE0433AE0433AE04239DF4137DD3F35DC3D33DA3B30D839
      2DD53629D23326CF3325CC3220BC402EB8DCD9EFFFFF00FFFF00FFFF00FFFF00
      FFFF00897ED67163CD7A70D96F65DD6A5FDB655ADB6157DC5E54DC5A50DD534A
      DD4137DA3F34DB3F35DC3F35DC3F35DC3E34DB3D33DA3C31D83A2ED6382CD436
      29D23426D03527CC3623BB402DB7DAD7EEFFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00877CD37C6FCF8177DB7268DD6C62DC675DDB6258DC5F55DB5B51
      DC554ADB3F34D73B30D83C30D83B30D83B2FD73A2ED6382CD5372AD33528D133
      25CF3629CD4332BE3E2BB4DAD7EDFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00877AD28579D1877DDD746BDE6F65DD695FDB6459DB5F55
      DA5B50DA544AD93D30D5382BD4382BD4372AD33629D23528D13426D03325CF38
      2ACD503EC14432B4D9D6ECFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00867AD08F83D38077DE776DDF7167DD6B61DC665B
      DB5F54D95A4FD85348D73A2CD13426D03326CF3325CF3325CF3325CF3325CF52
      43C44433B1A19DB3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00DAD7EC796AC98D84DE7E75E0786FDF7369DE6D63
      DC675DDB6257DA5C51D85448D63729CF3325CF3325CF3325CF3325CF3325CF52
      41BE5D50A5999999B7B7B7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00DCD9ED6655BB9C92D88C84E3867DE28077E17B71DF756B
      DE6F65DD6A5FDB645ADA5F54D95246D63325CF3325CF3325CF3325CF3325CF3F
      2EC23B25AE685DA0999999B7B7B7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00DCD9EC6A59BB9D93D89992E5938CE58E86E48880E3837AE17D74
      E0776EDF7268DD6C62DC675CDB6156D94B3FD43325CF3325CF3325CF3325CF33
      25CF3320BA331CA9685DA0999999B7B7B7FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00DCD9EC6E5EBCABA2DCA7A0E8A19AE89B94E7968FE69089E58B83E3857D
      E27F77E17A71DF746BDE6F65DD695FDB6359DA4336D23325CF3325CF3325CF33
      25CF3325CF331FB8331BA6685C9E999999B5B5B5FFFF00FFFF00FFFF00FFFF00
      DCD9EC7767BDBDB5E3B4AFEBAFA9ECA9A3EAA39DE99E97E89891E6938BE58D85
      E4877FE28279E17C73E0776DDF7167DD6B61DC645ADA3B2DD03325CF3325CF33
      25CF3325CF3325CF3422B8361EA5685C9E999999B7B7B7FFFF00FFFF00E2DFF2
      8475C3CEC9EAC3BEEFBCB8EFB7B2EEB1ACECABA6EBA6A0EAA09AE89B94E7958E
      E68F88E48981E3837BE27E75E07970DF736ADE6E64DC6055D93527CF3325CF33
      25CF3325CF3325CF3325CF3F2DBC442DA9695C9C999999D1D1D1FFFF008D7FC8
      DDDAF0D0CCF3C9C5F2C3BFF1BEB9EFB9B4EEB3AEEDAEA8EBA7A1EAA29BE99C95
      E7978FE69189E58B83E3867DE28077E17B71DF756BDE6F65DD5448D63325CF33
      25CF3325CF3325CF3325CF3325CF4938BF533EAE776E9ECFCFCFCFC9E8CAC4E6
      E0DEF5D7D4F5D1CEF4CBC8F2C6C2F1C0BCF0BBB6EFB5B0EDAFAAECAAA4EBA49E
      E99F98E89A93E69F97E2938BE28880E3837AE17D74E0776EDF7167DD3D30D133
      25CF3325CF3325CF3325CF3325CF3527CE6857BD6959ACFFFF00FFFF008D7FC9
      EAE8F5E2E0F7D9D6F6D3D0F4CECAF3C8C4F2C3BEF0BDB8EFB7B2EEB2ACECACA6
      EBABA5E9C3BCE59A8DCFB3AADBA39BE28B83E3857DE27F77E17A71DF6257DA33
      25CF3325CF3325CF3325CF3628CE6E60C86452B5C6C1DFFFFF00FFFF00F4F2FA
      9082CAEEECF7E5E3F8DBD9F6D6D3F5D0CDF4CBC7F2C5C1F1BFBBF0BAB5EEB8B4
      EDD2CDEC887AC3DAD7EA8D7FC9BCB4DFA9A2E58D85E4877FE28279E17C73E046
      39D33325CF3325CF3729CF7D71CE7160BBBDB6DBFFFF00FFFF00FFFF00FFFF00
      F4F2FA9385CCF2F0F9E8E6F8DEDBF7D8D5F5D3CFF4CDC9F3C7C4F2C6C2F0E0DC
      F29185C8DCD8EBFFFF00FFFF008E81C9C7C0E5AFA9E88F88E48A82E3847CE271
      67DD3325CF372ACF8C82D67B6BC0BCB5DAFFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00F5F4FA9689CDF5F4FAEAE9F9E0DEF7DBD8F6D5D2F5D3D0F4EAE8F69B90
      CDDCD8EBFFFF00FFFF00FFFF00FFFF009285CBD0CBE9B5AFEA928AE58B83E386
      7DE2554AD69B92DC8778C5BCB5DAFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00F5F4FA9A8DCFF8F7FBEDECFAE3E1F8E0DEF7F3F1FAA499D1DCD8
      EBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF009486CDDAD6EDBAB5EC938CE591
      8AE5CAC5EE9386CABCB5DBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00F5F4FA9D91D1FAFAFDF1F0FBF9F8FDAEA4D6DCD8EBFFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00978ACEE4E2F2C2BDEFDA
      D7F4BAB2DEBDB6DBFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00F5F4FA9F93D1F1F0F8B2A9DAE2DFF1FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF009A8ECFDDD8EEBA
      B1DEC5BEE3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D1CBE9FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D9D4EDEF
      EDF7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00}
  end
end
