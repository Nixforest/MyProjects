﻿<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="TestPage.aspx.cs" Inherits="RealEstateMarket.TestPage" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
<asp:GridView ID="listNationX" runat="server" AutoGenerateColumns="true" AutoGenerateDeleteButton="true"
     AutoGenerateEditButton="true"></asp:GridView>
     <table style="width: 60%">
        <tr>
            <td style="width: 280px">
                <asp:Label ID="lblName" runat="server" Text="Name"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txbName" runat="server" Enabled="true"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td style="width: 280px">
                <asp:Label ID="lblCode" runat="server" Text="Nation Code"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txbCode" runat="server"></asp:TextBox>
            </td>
        </tr>
    </table>
    <asp:Button ID="Insert" runat="server" Text="Insert" OnClick="btnInsert_Click"/>
</asp:Content>
