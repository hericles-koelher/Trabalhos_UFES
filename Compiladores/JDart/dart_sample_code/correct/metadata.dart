@JsonSerializable(explicitToJson: true, fieldRename: FieldRename.snake)
class Forecast extends Equatable {
  final String cityName;
  final List<Weather> days;

  @override
  List<Object> get props => [cityName, days];

  Forecast(this.cityName, this.days);

  factory Forecast.fromJson(Map<String, dynamic> json) =>
      _$ForecastFromJson(json);

  Map<String, dynamic> toJson() => _$ForecastToJson(this);
}