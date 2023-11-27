# ESP Para o segundo problema do PBL de Sistemas Digitais
<p>
  Código da ESP segue o protocolo descrito abaixo. Ela fica no aguardo por uma solicitação de dois Bytes contendo o número da requisição desejada e o endereço do sensor, que no caso o único sensor inserido e um sensor DHT11 no endereço 0x00, e retorna uma resposta de 2 Bytes seguindo as tabelas a baixo.
</p>
<h1>Tabela de solicitação da orangePi</h1>
<table>
  
  <tr>
    <td>
      <b>Ação</b>
    </td>
    <td>
      <b>Primeiro Envio</b>
    </td>
    <td>
      <b>Segundo Envio</b>
    </td>
  </tr>
  
  <tr>
    <td>
      Solicita a situação atual do sensor
    </td>
    <td>
      0x01
    </td>
    <td>
      Endereço
    </td>
  </tr>
  
  <tr>
    <td>
      Solicita a medida da temperatura atual
    </td>
    <td>
      0x02
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Solicita a medida da umidade atual
    </td>
    <td>
      0x03
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Ativa sensoriamento contínuo da temperatura
    </td>
    <td>
      0x04
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Ativa sensoriamento contínuo da umidade
    </td>
    <td>
      0x04
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Desativa sensoriamento contínuo da temperatura
    </td>
    <td>
      0x05
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Desativa sensoriamento contínuo da umidade
    </td>
    <td>
      0x06
    </td>
    <td>
      Endereço
    </td>
  </tr>
</table>

<h1>Tabela de resposta da ESP</h1>

<table>
  <tr>
    <td>
      <b>Resposta</b>
    </td>
    <td>
      <b>Primeiro Envio</b>
    </td>
    <td>
      <b>Segundo Envio</b>
    </td>
  </tr>

  <tr>
    <td>
      Sensor com problema
    </td>
    <td>
      0x1F
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Sensor inexistente
    </td>
    <td>
      0x2F
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Requisição inexistente
    </td>
    <td>
      0x3F
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Sensor funcionando normalmente
    </td>
    <td>
      0x07
    </td>
    <td>
      Endereço
    </td>
  </tr>

  <tr>
    <td>
      Medida de umidade
    </td>
    <td>
      Umidade (%)
    </td>
    <td>
      0x08
    </td>
  </tr>

  <tr>
    <td>
      Medida de temperatura
    </td>
    <td>
      Temperatura (ºC)
    </td>
    <td>
      0x09
    </td>
  </tr>

  <tr>
    <td>
      Confirmação de desativação de sensoriamento contínuo de temperatura
    </td>
    <td>
      Temperatura (ºC)
    </td>
    <td>
      0x0A
    </td>
  </tr>

  <tr>
    <td>
      Confirmação de desativação de sensoriamento contínuo de umidade
    </td>
    <td>
      Umidade (%)
    </td>
    <td>
      0x0B
    </td>
  </tr>
</table>
