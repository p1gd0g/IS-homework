//uploaded to https://github.com/p1gd0g/IS-homework
//golang
package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/sha1"
	"fmt"
	"io"
	"math/big"
)

func main() {
	params := new(dsa.Parameters)                              //params为参数，new为params生成空间
	dsa.GenerateParameters(params, rand.Reader, dsa.L1024N160) //随机设置参数

	fmt.Println("参数为:")
	fmt.Print("P:")
	fmt.Println(params.P)
	fmt.Print("Q:")
	fmt.Println(params.Q)
	fmt.Print("G:")
	fmt.Println(params.G)

	privatekey := new(dsa.PrivateKey)         //privatekey为私钥，new为privatekey生成空间
	privatekey.PublicKey.Parameters = *params //参数的导入
	dsa.GenerateKey(privatekey, rand.Reader)  //随机生成私钥

	fmt.Println("私钥为：") //输出私钥
	fmt.Println(privatekey.X)

	publickey := privatekey.PublicKey //生成公钥
	fmt.Println("公钥为：")               //输出公钥
	fmt.Println(publickey.Y)

	h := sha1.New()    //h为hash值，生成空间
	r := big.NewInt(0) //生成大数空间
	s := big.NewInt(0) //生成大数空间

	m := "ShenzhenUniversity"
	io.WriteString(h, m) //输入消息

	fmt.Println("消息为：") //输出消息
	fmt.Println(m)

	signhash := h.Sum(nil)                                //将消息进行hash计算，将hash值存入signhash
	r, s, _ = dsa.Sign(rand.Reader, privatekey, signhash) //进行签名

	signature := r.Bytes()                      //将r的值转为byte类型
	signature = append(signature, s.Bytes()...) //将s的值转为byte类型，与r级联

	fmt.Println("签名为：") //输出签名
	fmt.Println(signature)

	verifystatus := dsa.Verify(&publickey, signhash, r, s) //验证
	fmt.Println(verifystatus)
}
