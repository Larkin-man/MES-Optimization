object EnterDataForm: TEnterDataForm
  Left = 513
  Top = 223
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1079#1072#1087#1080#1089#1080
  ClientHeight = 106
  ClientWidth = 263
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Field1: TLabeledEdit
    Left = 16
    Top = 24
    Width = 113
    Height = 24
    EditLabel.Width = 84
    EditLabel.Height = 16
    EditLabel.Caption = #1050#1086#1083'-'#1074#1086' '#1089#1090#1088#1086#1082
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = []
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 0
    OnChange = Field1Change
    OnExit = Field1Exit
  end
  object Field2: TLabeledEdit
    Left = 16
    Top = 72
    Width = 113
    Height = 24
    EditLabel.Width = 109
    EditLabel.Height = 16
    EditLabel.Caption = #1050#1086#1083'-'#1074#1086' '#1089#1090#1086#1083#1073#1094#1086#1074
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = []
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 1
    OnChange = Field2Change
    OnClick = Field2Click
    OnExit = Field2Exit
  end
  object BitBtnCancel: TBitBtn
    Left = 208
    Top = 28
    Width = 48
    Height = 48
    Hint = #1054#1090#1084#1077#1085#1080#1090#1100
    ModalResult = 2
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = BitBtnCancelClick
    Glyph.Data = {
      360C0000424D360C000000000000360000002800000020000000200000000100
      180000000000000C0000120B0000120B00000000000000000000FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00CBCBF2BDBDF0BBBBEFC1C1F1DFDFF5FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D7D7F48383E03E3E
      D51616D40404DA0000E00000E60000E70E0EE52A2AE16262E2B7B7EEFFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00D3D3F35252CF0404BE0000C60000
      D00000D90000E10202E90202F00000F40000F20000EB0000E20000D72A2AD4A5
      A5E9FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF008585DB0606B20000B60000BF0404C90404
      D20202DA0000E30000EC0000F50000FA0000F70202EE0606E60202DC0000D300
      00C84444D0E1E1F7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF005050C50000A50202AE0202B70202C00000C90000
      D10202D61212DE2C2CE53E3EEA2C2CEE1616EC0000E80000E40000DD0000D302
      02CA0000C11616BFC3C3EFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF004242BC00009B0404A50000AD0202B70000BF1616CA6E6E
      DFC1C1F0EFEFF9FFFF00FFFF00FFFF00E0E0FFBFBFF17A7AE60C0CD60000D300
      00C90202C10000B70C0CB6C1C1EEFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF005C5CC400009204049D0000A40000AC0202B86A6AD8E9E9F9FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00B9B9EE0404D50000D200
      00C80000BF0202B80000AD1616B2DBDBF6FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF009B9BDE00008D02029100009B0000A30C0CB3ABABE8FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00BDBDEF0808D90000D90000CF00
      00C70000BE0000B50202AE0000A34444C0FFFF00FFFF00FFFF00FFFF00FFFF00
      E9E9FB1A1A9A0000850000910000990606A9BFBFEEFFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00CDCDF21212DB0000DD0000D40000CD00
      00C40000BC0000B30000AB0202A300009C9D9DE0FFFF00FFFF00FFFF00FFFF00
      8181CF00008002028800008F00009C9999E1FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00DDDDF61E1EDB0000DF0202D70000D10000CA00
      00C20000BA0000B10000A90000A10000962828ADFFFF00FFFF00FFFF00FFFF00
      22229900007A02028700008E4646BDFFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF002C2CDA0000DD0202D80000D30000CD0000C602
      02C00000B63636C51E1EB500009E020296000092AFAFE6FFFF00FFFF00C1C1EB
      00007C00007A000083000093C1C1EDFFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF003838D70000D80202D60000D30000CF0000C90202C300
      00BB2828C2FFFF007A7AD500009D06069600008A5C5CC0FFFF00FFFF007E7EC9
      00007304047C0000823A3AB1FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF004A4AD70000D10202D20000D00000CE0000CA0202C50000BE1E
      1EC2DBDBF5FFFF00C5C5EF00009E0000910000872424A1F7F7FFFFFF005252AF
      00006F06067B0000828181D2FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF005C5CD70000C90202CB0000CC0000CB0000C80000C50000C01212C0CF
      CFF2FFFF00FFFF00FFFF001A1AA800008E00008508088DD7D7F4FFFF0034349C
      00006C040477000084B5B5E7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      006C6CD80000C00202C40000C50000C60000C50000C30000BF0A0ABEBFBFEEFF
      FF00FFFF00FFFF00FFFF003838B400008B020283000083BBBBE9FFFF002A2A96
      00006B020273000084C9C9EFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF008383
      DC0000B80202BC0000BE0000C00000C00000C00000BD0202BCAFAFEAFFFF00FF
      FF00FFFF00FFFF00FFFF004242B700008802028000007FB1B1E5FFFF002A2A96
      00006A020271000082CBCBF0FFFF00FFFF00FFFF00FFFF00FFFF009393E00000
      B00202B30000B60000B90000BA0000BB0202BB0000B89B9BE4FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF003A3AB100008502027D00007DB3B3E6FFFF003C3CA2
      00006A02026E00007EBFBFEBFFFF00FFFF00FFFF00FFFF00A5A5E50000A80000
      A90000AE0000B10000B30000B50202B50000B58B8BDFFFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF001C1CA000008100007900007CC1C1EBFFFF005A5AB5
      00006C04046E0000779797D9FFFF00FFFF00FFFF00B9B9EB0606A300009F0000
      A50000A80000AB0000AE0202AF0000B07676D8FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00CBCBF100008C00007D0000750E0E85E1E1F9FFFF009393D4
      00007004046D0000705454B6FFFF00FFFF00C7C7F00E0EA000009400009B0000
      9F0000A30000A60202A90000AA6464D1FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF007E7ED000008304047C00007130309BFFFF00FFFF00D5D5F4
      02027900006A00006B0E0E89E9E9FBDDDDF616169E00008A0000920000960000
      9A00009E0202A10000A35252C9FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00EBEBFC1A1A9C00007B0404790000707272C3FFFF00FFFF00FFFF00
      3A3AA300006A02026D0000716060C33434A800008002028900008D0000910000
      9502029900009B4040BFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF007C7CD0000081020279000070000077C7C7EFFFFF00FFFF00FFFF00
      A9A9E100007302026B00006C00007800007900007D00008300008800008C0202
      910000923232B5FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00BBBBEB04048B00007802027600006C4444A9FFFF00FFFF00FFFF00FFFF00
      FFFF003A3AA300006A02026D00006D00007400007A00007E0000830202880000
      892424AAE3E3F9FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00CF
      CFF316169800007900007600006D000078C1C1ECFFFF00FFFF00FFFF00FFFF00
      FFFF00CBCBF006067E00006800006D00006F00007500007A00007E00007F1616
      9CD3D3F4FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00B1B1E70E
      0E9300007900007602027100006F6E6EC3FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF009797D900007502026A00006D0000700000750000770E0E93CDCD
      F3FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00DBDBF75A5ABE00008500
      007700007602027100006C3C3CA6FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF008383CE00007402026902026E00007000007310108D6262
      BEA1A1DEC9C9EFD9D9F5D9D9F5C1C1EC9999DA4848B30A0A8D00007B00007600
      007602027000006C3232A0E9E9FCFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF009191D602027B00006902026C0202700000710000
      7600007D00008206068806068800008300007F00007900007602027702027400
      006C0000714848AEEDEDFDFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00C5C5ED2E2E9D00007200006A00006B0606
      7204047302027400007400007402027604047606067702027200006D00006E0C
      0C838B8BD2FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF009D9DDB2E2E9B0000760000
      6E00006C00006C00006D00006D00006E00006D00006F0000741414896E6EC2DF
      DFF7FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00C9C9EF8383
      CC4E4EAD30309A1C1C8C1A1A8B2626934040A46A6ABEADADE2EFEFFDFFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00E0E0FFE0E0FFFFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00}
  end
  object BitBtnOk: TBitBtn
    Left = 152
    Top = 28
    Width = 48
    Height = 48
    Hint = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = BitBtnOkClick
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
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 227
    Top = 75
  end
end
